

link_libraries( dspp pptest )


add_executable( allocator_test allocator/allocator.cpp )
add_test( NAME allocator COMMAND allocator_test )

add_executable( allocator_nt_test allocator/allocator_nt.cpp )
add_test( NAME allocator_nt COMMAND allocator_nt_test )

add_executable( fixed_test fixed/fixed.cpp ) 
add_test( NAME fixed COMMAND fixed_test )

add_executable( unique_test unique/unique.cpp ) 
add_test( NAME unique COMMAND unique_test )

add_executable( persistent_test persistent/persistent.cpp ) 
add_test( NAME persistent COMMAND persistent_test )

add_executable( shared_test shared/shared.cpp ) 
add_test( NAME shared COMMAND shared_test )

enable_testing()
