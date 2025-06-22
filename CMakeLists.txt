cmake_minimum_required(VERSION 3.5)
project(my_drogon_app)

set(CMAKE_CXX_STANDARD 17)
set(DROGON_ENABLE_ORM ON)

add_subdirectory(dependencies/jwt-cpp)
add_subdirectory(dependencies/Bcrypt)
find_package(Drogon REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cc
    src/controllers/api_v1_User.cc
    src/models/Users.cc
    dependencies/jwt-cpp
    dependencies/Bcrypt
    src/filters/auth.cc
    src/utils/AppError.cc
    src/utils/token.cc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Drogon::Drogon
    PRIVATE jwt-cpp::jwt-cpp
    PRIVATE bcrypt
)
add_compile_options(-Wno-deprecated-declarations)
