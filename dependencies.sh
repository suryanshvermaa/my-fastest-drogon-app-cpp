# !/bin/bash

echo "Installing dependencies..."
mkdir -p ./dependencies
cd ./dependencies

echo "installing jwt-cpp"
git clone https://github.com/Thalhammer/jwt-cpp.git

echo "installing bcrypt-cpp"
git clone https://github.com/hilch/Bcrypt.cpp.git
# renaming from Bcrypt.cpp to Bcrypt
mv Bcrypt.cpp Bcrypt

echo "installing cpr"
git clone https://github.com/libcpr/cpr.git
sudo apt update
sudo apt install meson ninja-build
sudo apt update
sudo apt install libidn2-dev libpsl-dev
sudo apt install libunistring-dev