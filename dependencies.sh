#!/bin/bash
set -e  # Exit on any error
set -u  # Treat unset variables as errors

echo "Installing dependencies..."

# Create and move into the dependencies directory
mkdir -p ./dependencies
cd ./dependencies || exit 1

echo "Installing jwt-cpp..."
if [ ! -d "jwt-cpp" ]; then
  git clone --depth 1 https://github.com/Thalhammer/jwt-cpp.git
else
  echo "jwt-cpp already exists. Skipping clone."
fi

echo "Installing bcrypt-cpp..."
if [ ! -d "Bcrypt" ]; then
  git clone --depth 1 https://github.com/hilch/Bcrypt.cpp.git
  mv Bcrypt.cpp Bcrypt
else
  echo "Bcrypt already exists. Skipping clone."
fi

echo "All dependencies installed successfully."
