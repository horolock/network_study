cmake_minimum_required(VERSION 3.5)

project (basic_network)

add_executable(server_win server_win.c)
add_executable(hello_client hello_client.c)

target_link_libraries(server_win ws2_32)
target_link_libraries(hello_client ws2_32)
