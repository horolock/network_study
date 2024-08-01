cmake_minimum_required(VERSION 3.12)

project(address_data)

add_executable(endian_conv endian_conv.c)

target_link_libraries(endian_conv ws2_32)