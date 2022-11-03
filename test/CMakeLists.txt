
link_libraries( dspp pptest )

add_executable( ds_allocator_test allocator/allocator.cpp )
add_test( NAME ds_allocator COMMAND ds_allocator_test )

add_executable( ds_allocator_nt_test allocator/allocator_nt.cpp )
add_test( NAME ds_allocator_nt COMMAND ds_allocator_nt_test )

add_executable( ds_fixed_test fixed/fixed.cpp ) 
add_test( NAME ds_fixed COMMAND ds_fixed_test )
