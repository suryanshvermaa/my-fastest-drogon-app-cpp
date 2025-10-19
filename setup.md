## Environment Setup
To set up your development environment, follow these steps:

```bash
apt-get update && apt-get install -y \
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
 ```
This command updates the package lists and installs the necessary development tools and libraries required for building and running the project. After installation, it cleans up the package lists to reduce disk space usage.
Make sure to run this command with superuser privileges (e.g., using `sudo`) to ensure all packages are installed correctly.

```bash
git clone https://github.com/drogonframework/drogon.git /tmp/drogon \
 && cd /tmp/drogon \
 && git checkout ${DROGON_VERSION} \
 && git submodule update --init --recursive \
 && mkdir build && cd build \
 && cmake .. -DCMAKE_BUILD_TYPE=Release \
 && make -j"$(nproc)" \
 && make install \
 && ldconfig \
 && rm -rf /tmp/drogon
 ```
This command clones the Drogon framework repository, checks out the specified version, initializes submodules, builds the project in release mode, installs it, and then cleans up the temporary files. Make sure to replace `${DROGON_VERSION}` with the desired version tag or branch name before running the command.