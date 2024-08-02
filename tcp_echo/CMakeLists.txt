cmake_minimum_required(VERSION 3.16)

project(tcp_echo)

add_executable(echo_server echo_server.c)
add_executable (echo_client echo_client.c)

target_link_libraries(echo_server ws2_32)
target_link_libraries(echo_client ws2_32)