cmake_minimum_required(VERSION 3.27)

project(OpenCL-in-Action LANGUAGES C)

add_compile_definitions(CL_TARGET_OPENCL_VERSION=300)

find_package(OpenCL REQUIRED)

add_subdirectory(Ch01/matvec/)
