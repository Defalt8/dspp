cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.29.112 LANGUAGES CXX )

option( BUILD_TESTS ON )

set( DS_HEADER_FILES
	include/ds/all
	include/ds/macros
	include/ds/common
	include/ds/sys
	include/ds/file
	include/ds/random
	include/ds/memo
	include/ds/allocator
	include/ds/fixed
	include/ds/fixed_stack
	include/ds/unique
	include/ds/persistent
	include/ds/shared
	include/ds/callable
	include/ds/tuple
	include/ds/variant
	include/ds/string
	include/ds/string_stream
	include/ds/array
	include/ds/stack
	include/ds/list
	include/ds/unordered_list
	include/ds/unordered_map
	include/ds/ordered_list
	include/ds/ordered_map
	include/ds/coroutine
)
 
set( DS_TRAITS_HEADER_FILES
	include/ds/traits/allocator
	include/ds/traits/iterable
)
 
set( DS_ALLOCATORS_HEADER_FILES
	include/ds/allocators/new_delete
	include/ds/allocators/base
	include/ds/allocators/memo
	include/ds/allocators/local_forward
	include/ds/allocators/heap_forward
)
 
add_library( dspp INTERFACE )
target_include_directories( dspp INTERFACE include )
install( FILES ${DS_HEADER_FILES}            DESTINATION include/ds )
install( FILES ${DS_TRAITS_HEADER_FILES}     DESTINATION include/ds/traits )
install( FILES ${DS_ALLOCATORS_HEADER_FILES} DESTINATION include/ds/allocators )

#################################################################

if( BUILD_TESTS 
	AND ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}
	AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/pptest/CMakeLists.txt" 
)
	add_subdirectory( dep/pptest dspp_pptest )
	add_subdirectory( test dspp_testing )
	enable_testing()
endif()
