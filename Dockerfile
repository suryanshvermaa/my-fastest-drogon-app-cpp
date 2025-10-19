## Production Dockerfile (backend only)
## Multi-stage build: compile in builder, run in slim runtime

FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive \
    DROGON_VERSION=v1.9.0

# Build toolchain and Drogon deps
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libpq-dev \
    libssl-dev \
    zlib1g-dev \
    libjsoncpp-dev \
    libboost-all-dev \
    uuid-dev \
 && rm -rf /var/lib/apt/lists/*

# Build Drogon from source (includes Trantor)
RUN git clone https://github.com/drogonframework/drogon.git /tmp/drogon \
 && cd /tmp/drogon \
 && git checkout ${DROGON_VERSION} \
 && git submodule update --init --recursive \
 && mkdir build && cd build \
 && cmake .. -DCMAKE_BUILD_TYPE=Release \
 && make -j"$(nproc)" \
 && make install \
 && ldconfig \
 && rm -rf /tmp/drogon

WORKDIR /app

# Copy project files
COPY CMakeLists.txt /app/CMakeLists.txt
COPY src/ /app/src/
COPY dependencies.sh /app/dependencies.sh
COPY config.docker.json /app/config.json
COPY init.sql /app/init.sql

# Fix line endings and fetch third-party deps expected by CMake add_subdirectory()
RUN sed -i 's/\r$//' /app/dependencies.sh && bash dependencies.sh

# Configure and build (Release)
RUN mkdir -p /app/build \
 && cd /app/build \
 && cmake .. -DCMAKE_BUILD_TYPE=Release \
 && make -j"$(nproc)"

FROM ubuntu:22.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal runtime libraries
RUN apt-get update && apt-get install -y \
  libpq5 \
  libssl3 \
  libuuid1 \
  zlib1g \
  libjsoncpp-dev \
  ca-certificates \
  curl \
 && rm -rf /var/lib/apt/lists/*

# Non-root user
RUN useradd -m -u 1000 appuser

WORKDIR /app

# Copy binary and required files
COPY --from=builder /app/build/my_drogon_app /app/my_drogon_app
COPY --from=builder /app/config.json /app/config.json
COPY --from=builder /app/init.sql /app/init.sql

# Copy Drogon and Trantor shared libraries from builder
COPY --from=builder /usr/local/lib/libdrogon* /usr/local/lib/
COPY --from=builder /usr/local/lib/libtrantor* /usr/local/lib/
RUN ldconfig

# Runtime dir for uploads
RUN mkdir -p /app/uploads/tmp && chown -R appuser:appuser /app

USER appuser

# Port from config.json
EXPOSE 3001

# Healthcheck: basic HTTP reachability (does not fail on 404)
HEALTHCHECK --interval=30s --timeout=5s --start-period=10s --retries=3 \
  CMD curl -sS http://localhost:3001 >/dev/null || exit 1

CMD ["/app/my_drogon_app"]
