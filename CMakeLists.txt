cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.8.32 LANGUAGES CXX )

set( DS_HEADER_FILES
	include/ds/macros
	include/ds/common
	include/ds/traits/allocator
	include/ds/traits/iterator
	include/ds/allocator
	include/ds/fixed
	include/ds/unique
	include/ds/persistent
	include/ds/shared
	include/ds/tuple
	include/ds/variant
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
