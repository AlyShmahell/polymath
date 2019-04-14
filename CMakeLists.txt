cmake_minimum_required(VERSION 3.10.2)

project(intf)

include_directories(include)

install(DIRECTORY "include/"
        DESTINATION "/usr/local/include/intf"
        FILES_MATCHING
        PATTERN "*.hpp"
)