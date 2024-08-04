cmake_minimum_required(VERSION 3.16)

project(tcp_calculator)

add_executable(calculator_client calculator_client.c)
add_executable(calculator_server calculator_server.c)

target_link_libraries(calculator_client ws2_32)
target_link_libraries(calculator_server ws2_32)