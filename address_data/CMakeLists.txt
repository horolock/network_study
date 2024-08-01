cmake_minimum_required(VERSION 3.12)

project(address_data)

add_executable(inet_address_conv inet_address_conv.c)

target_link_libraries(inet_address_conv ws2_32)