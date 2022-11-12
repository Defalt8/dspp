

link_libraries( dspp pptest )


add_executable( allocator_test allocator/allocator.cpp )
add_test( NAME allocator COMMAND allocator_test )

add_executable( allocator_nt_test allocator/allocator_nt.cpp )
add_test( NAME allocator_nt COMMAND allocator_nt_test )

enable_testing()
