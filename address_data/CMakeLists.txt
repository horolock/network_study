cmake_minimum_required(VERSION 3.12)

project(address_data)

add_executable(conv_address conv_address.c)

target_link_libraries(conv_address ws2_32)