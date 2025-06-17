# Multi-stage build for Drogon C++ application
FROM ubuntu:22.04 as builder

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV DROGON_VERSION=v1.9.0

# Install system dependencies
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

# Clone and build Drogon
WORKDIR /tmp
RUN git clone https://github.com/drogonframework/drogon.git \
    && cd drogon \
    && git checkout ${DROGON_VERSION} \
    && mkdir build && cd build \
    && cmake .. \
    && make -j$(nproc) \
    && make install \
    && ldconfig

# Set up application directory
WORKDIR /app

# Copy CMakeLists.txt and build the application
COPY CMakeLists.txt .
COPY main.cc .
COPY controllers/ ./controllers/
COPY models/ ./models/
COPY utils/ ./utils/

# Build the application
RUN mkdir build && cd build \
    && cmake .. \
    && make -j$(nproc)

# Runtime stage
FROM ubuntu:22.04 as runtime

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libpq5 \
    libssl3 \
    libjsoncpp25 \
    libboost-system1.74.0 \
    libboost-filesystem1.74.0 \
    libboost-regex1.74.0 \
    libboost-thread1.74.0 \
    libboost-date-time1.74.0 \
    libboost-coroutine1.74.0 \
    libboost-context1.74.0 \
    libboost-asio1.74.0 \
    libboost-beast1.74.0 \
    libuuid1 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -m -u 1000 appuser

# Set up application directory
WORKDIR /app

# Copy configuration files
COPY config.json .
COPY init.sql .

# Copy the built application from builder stage
COPY --from=builder /app/build/my_drogon_app .

# Create uploads directory
RUN mkdir -p uploads/tmp && chown -R appuser:appuser uploads

# Change ownership of application files
RUN chown -R appuser:appuser /app

# Switch to non-root user
USER appuser

# Expose port
EXPOSE 3000

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD curl -f http://localhost:3000/api/v1/User/getUsers || exit 1

# Run the application
CMD ["./my_drogon_app"] 