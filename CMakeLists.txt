cmake_minimum_required(VERSION 3.5)
project(my_drogon_app)

set(CMAKE_CXX_STANDARD 17)
set(DROGON_ENABLE_ORM ON)

find_package(Drogon REQUIRED)
add_executable(${PROJECT_NAME}
    main.cc
    controllers/api_v1_User.cc
    models/Users.cc
    utils/
)

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
