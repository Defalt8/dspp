cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.1.0 )

set( DS_HEADER_FILES
	include/ds/macros
)

add_library( dspp INTERFACE )
target_include_directories( dspp INTERFACE include )
set_target_properties( dspp PROPERTIES PUBLIC_HEADER "${DS_HEADER_FILES}" )

#################################################################

set( DSPP_STANDALONE FALSE )
if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
	set( DSPP_STANDALONE TRUE )
endif()
set( DSPP_TESTING ${DSPP_STANDALONE} CACHE BOOL "" )

if( DSPP_TESTING )
	add_subdirectory( dep/pptest dspp_pptest )
endif()
