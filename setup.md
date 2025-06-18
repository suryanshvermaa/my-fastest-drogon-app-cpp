```
conan profile detect
conan install . --output-folder=dependencies --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```