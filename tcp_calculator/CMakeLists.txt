cmake_minimum_required(VERSION 3.16)

project(tcp_calculator)

add_executable(calculator_client calculator_client.c)

target_link_libraries(calculator_client ws2_32)