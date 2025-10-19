#!/usr/bin/env bash
set -euo pipefail

echo "[dev] Starting Drogon backend dev container..."

# Wait for PostgreSQL to be ready
echo "[dev] Waiting for PostgreSQL..."
until PGPASSWORD=postgres psql -h postgres -U postgres -d userdb -c '\q' 2>/dev/null; do
  echo "[dev] PostgreSQL is unavailable - sleeping"
  sleep 2
done
echo "[dev] PostgreSQL is up!"

# Ensure dependencies (jwt-cpp, Bcrypt) exist for CMakeLists.txt add_subdirectory
if [ ! -d "/app/dependencies/jwt-cpp" ] || [ ! -d "/app/dependencies/Bcrypt" ]; then
  echo "[dev] Fetching C++ third-party dependencies into ./dependencies"
  mkdir -p /app/dependencies
  bash /app/dependencies.sh
fi

# Configure and build (Debug for development)
echo "[dev] Building application..."
mkdir -p /app/build
cd /app/build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j"$(nproc)"

echo "[dev] Build complete. Running app..."
cd /app/build
exec ./my_drogon_app
