add_executable(matvec matvec.c aux.c)
target_link_libraries(matvec PRIVATE OpenCL::OpenCL)
configure_file(matvec.cl ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
