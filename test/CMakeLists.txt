

link_libraries( dspp pptest )

add_executable( allocator_test allocator/allocator.cpp )
add_test( NAME allocator COMMAND allocator_test )

add_executable( nt_allocator_test allocator/nt_allocator.cpp )
add_test( NAME nt_allocator COMMAND nt_allocator_test )

add_executable( unique_test unique/unique.cpp ) 
add_test( NAME unique COMMAND unique_test )

add_executable( persistent_test persistent/persistent.cpp ) 
add_test( NAME persistent COMMAND persistent_test )

add_executable( shared_test shared/shared.cpp ) 
add_test( NAME shared COMMAND shared_test )

add_executable( fixed_test fixed/fixed.cpp ) 
add_test( NAME fixed COMMAND fixed_test )

add_executable( fixed_stack_test fixed_stack/fixed_stack.cpp ) 
add_test( NAME fixed_stack COMMAND fixed_stack_test )

add_executable( sys_test sys/sys.cpp ) 
add_test( NAME sys COMMAND sys_test )
target_compile_definitions( sys_test PRIVATE WORKING_DIR="${CMAKE_CURRENT_SOURCE_DIR}/_wdir/" )

enable_testing()
