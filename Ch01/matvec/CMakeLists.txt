add_executable(matvec matvec.c aux.c)
configure_file(matvec.cl ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
