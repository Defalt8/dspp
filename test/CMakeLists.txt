

link_libraries( dspp pptest )


add_executable( allocator_test allocator/allocator.cpp )
add_test( NAME allocator COMMAND allocator_test )

add_executable( allocator_nt_test allocator/allocator_nt.cpp )
add_test( NAME allocator_nt COMMAND allocator_nt_test )

add_executable( unique_test unique/unique.cpp ) 
add_test( NAME unique COMMAND unique_test )

add_executable( persistent_test persistent/persistent.cpp ) 
add_test( NAME persistent COMMAND persistent_test )

add_executable( shared_test shared/shared.cpp ) 
add_test( NAME shared COMMAND shared_test )

add_executable( fixed_test fixed/fixed.cpp ) 
add_test( NAME fixed COMMAND fixed_test )

add_executable( array_test array/array.cpp ) 
add_test( NAME array COMMAND array_test )

add_executable( string_test string/string.cpp ) 
add_test( NAME string COMMAND string_test )

add_executable( list_1_test list/list_1.cpp ) 
add_test( NAME list_1 COMMAND list_1_test )

add_executable( hash_list_test hash_list/hash_list.cpp ) 
add_test( NAME hash_list COMMAND hash_list_test )

add_executable( tuple_test tuple/tuple.cpp ) 
add_test( NAME tuple COMMAND tuple_test )

add_executable( variant_test variant/variant.cpp ) 
add_test( NAME variant COMMAND variant_test )

enable_testing()
