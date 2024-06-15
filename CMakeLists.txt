cmake_minimum_required(VERSION 3.27)
project(ProjectAAP)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest)

add_subdirectory(${GTEST_DIR})

add_executable(ProjectAAP main.cpp VigenereCipher.cpp SimpleSubCipher.cpp AffinCipher.cpp VigenereCipher.cpp VigenereCipher.h)

target_link_libraries(ProjectAAP gtest gtest_main)

target_include_directories(ProjectAAP PRIVATE ${GTEST_DIR}/googletest/include)

enable_testing()

add_executable(ctest Tests.cpp AffinCipher.cpp AffinCipher.h SimpleSubCipher.cpp SimpleSubCipher.h)  # Переименованный исполняемый файл тестов
target_link_libraries(ctest gtest gtest_main)
target_include_directories(ctest PRIVATE ${GTEST_DIR}/googletest/include)

add_test(NAME ctest COMMAND ctest)
