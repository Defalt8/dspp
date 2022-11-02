cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.2.1 LANGUAGES CXX )

set( DS_HEADER_FILES
	include/ds/macros
	include/ds/allocator
)

add_library( dspp INTERFACE )
target_include_directories( dspp INTERFACE include )
set_target_properties( dspp PROPERTIES PUBLIC_HEADER "${DS_HEADER_FILES}" )

#################################################################

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} 
	AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/pptest/CMakeLists.txt" )
	add_subdirectory( dep/pptest dspp_pptest )
	add_subdirectory( test dspp_testing )
endif()
