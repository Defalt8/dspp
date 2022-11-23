cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.23.96 LANGUAGES CXX )

set( DS_HEADER_FILES
	include/ds/all
	include/ds/macros
	include/ds/common
	include/ds/sys
	include/ds/file
	include/ds/traits/allocator
	include/ds/traits/iterator
	include/ds/allocator
	include/ds/fixed
	include/ds/fixed_stack
	include/ds/unique
	include/ds/persistent
	include/ds/shared
	include/ds/tuple
	include/ds/variant
	include/ds/string
	include/ds/string_stream
	include/ds/array
	include/ds/list
	include/ds/unordered_list
	include/ds/unordered_map
	include/ds/ordered_list
	include/ds/ordered_map
)
 
add_library( dspp INTERFACE )
target_include_directories( dspp INTERFACE include )
set_target_properties( dspp PROPERTIES PUBLIC_HEADER "${DS_HEADER_FILES}" )

#################################################################

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} 
	AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/pptest/CMakeLists.txt" )
	add_subdirectory( dep/pptest dspp_pptest )
	add_subdirectory( test dspp_testing )
	enable_testing()
endif()
