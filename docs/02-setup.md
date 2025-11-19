# Setup (Linux) and Running

This section covers installing prerequisites, building, and running the backend locally and via Docker.

## Prerequisites (Local)
- C++20 compiler (GCC 10+/Clang 10+)
- CMake 3.5+
- PostgreSQL 15+
- Drogon v1.9.0

Install toolchain and libraries:

```bash
sudo apt-get update && sudo apt-get install -y \
  build-essential cmake git libpq-dev libssl-dev zlib1g-dev \
  libjsoncpp-dev libboost-all-dev uuid-dev
```

Install Drogon (v1.9.0):

```bash
DROGON_VERSION=v1.9.0

git clone https://github.com/drogonframework/drogon.git /tmp/drogon \
 && cd /tmp/drogon \
 && git checkout "$DROGON_VERSION" \
 && git submodule update --init --recursive \
 && mkdir build && cd build \
 && cmake .. -DCMAKE_BUILD_TYPE=Release \
 && make -j"$(nproc)" \
 && sudo make install \
 && sudo ldconfig \
 && cd ~ && rm -rf /tmp/drogon
```

## Configure Database
Start PostgreSQL and create the schema:

```bash
# If using docker-compose for DB only
docker compose up -d postgres

# Or use local psql to load schema
psql -h 127.0.0.1 -U postgres -d userdb -f ./init.sql
```

## Configure App
- Ensure `config.json` points to your DB (default: `127.0.0.1:5432`).
- Set `JWT_SECRET` in your environment for signing tokens.

```bash
export JWT_SECRET="your-secret-key"
```

## Build & Run (Local)

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j

# Run the server (listens on port 3001)
./my_drogon_app
```

Test the health endpoint:

```bash
curl -s http://localhost:3001/api/v1/health/
```

## Run with Docker (Backend only)

```bash
# Build production image
docker build -t drogon-app:latest -f Dockerfile .

# Run (configure secret)
docker run --rm -p 3001:3001 -e JWT_SECRET=your-secret-key drogon-app:latest
```

## Use docker-compose (Database)

```bash
# Starts postgres on 5432 and seeds schema from init.sql
docker compose up -d postgres
```

> Next: read [Backend Architecture](./03-backend.md) then try the [API](./04-api.md).
