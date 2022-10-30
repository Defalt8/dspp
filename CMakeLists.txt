cmake_minimum_required( VERSION 3.4 )
project( dspp VERSION 0.1.0 )

set( DS_HEADER_FILES
	include/ds/macros
)

add_library( dspp INTERFACE ${DS_HEADER_FILES} )
target_include_directories( dspp INTERFACE include )

#################################################################

set( DSPP_STANDALONE FALSE )
if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
	set( DSPP_STANDALONE TRUE )
endif()
set( DSPP_TESTING ${DSPP_STANDALONE} CACHE BOOL "" )

if( DSPP_TESTING )
	add_subdirectory( test testing_dspp )
endif()
