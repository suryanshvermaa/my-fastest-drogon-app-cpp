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
