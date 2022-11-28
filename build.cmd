@ECHO OFF

@REM build
@REM build [target]
@REM build <library-type> <config> [target] ...cmake args
@REM
@REM target: workflow|install|clean|...
@REM library-type: static|shared 
@REM config: Debug|Release|MinSizeRel|RelWithDebInfo
@REM
@REM you can set this variables
@REM     CMAKE_GENERATOR
@REM     CMAKE_BUILD_DIR
@REM     CMAKE_INSTALL_DIR
@REM     CMAKE_SOURCE_DIR
@REM     CMAKE_BUILD_TESTS

SET LIBRARY_TYPE=STATIC
SET CONFIG=Release
SET BUILD_DIR=./out/build
SET INSTALL_DIR=./out/install
SET SOURCE_DIR=.
SET BUILD_TESTS=ON

IF NOT "%CMAKE_BUILD_DIR%"==""        SET BUILD_DIR=%CMAKE_BUILD_DIR%
IF NOT "%CMAKE_INSTALL_DIR%"=="" 	  SET INSTALL_DIR=%CMAKE_INSTALL_DIR%
IF NOT "%CMAKE_SOURCE_DIR%"=="" 	  SET SOURCE_DIR=%CMAKE_SOURCE_DIR%
IF NOT "%CMAKE_BUILD_TESTS%"==""      SET BUILD_TESTS=%CMAKE_BUILD_TESTS%
IF NOT "%1"=="" 					  SET LIBRARY_TYPE=%1
IF NOT "%2"==""                       SET CONFIG=%2

@REM ECHO LIBRARY_TYPE=%LIBRARY_TYPE%
@REM ECHO CONFIG=%CONFIG%
@REM ECHO BUILD_DIR=%BUILD_DIR%
@REM ECHO INSTALL_DIR=%INSTALL_DIR%
@REM ECHO SOURCE_DIR=%SOURCE_DIR%
@REM ECHO BUILD_TESTS=%BUILD_TESTS%

IF NOT "%CMAKE_GENERATOR%"=="" (
    cmake -G "%CMAKE_GENERATOR%" -B "%BUILD_DIR%" -S "%SOURCE_DIR%" -DCMAKE_INSTALL_PREFIX:PATH="%INSTALL_DIR%" -DWORKFLOW_BUILD_TESTS:BOOL=%BUILD_TESTS% -DWORKFLOW_TYPE:STRING=%LIBRARY_TYPE%
) ELSE (
    cmake -B "%BUILD_DIR%" -S "%SOURCE_DIR%" -DCMAKE_INSTALL_PREFIX:PATH="%INSTALL_DIR%" -DWORKFLOW_BUILD_TESTS:BOOL=%BUILD_TESTS% -DWORKFLOW_TYPE:STRING=%LIBRARY_TYPE%
)

IF NOT "%1"=="" (
    IF "%2"=="" (
        cmake --build "%BUILD_DIR%" --config %CONFIG% --target %1
    ) ELSE (
        IF NOT "%3"=="" (
            cmake --build "%BUILD_DIR%" --config %CONFIG% --target %3 %4 %5 %6 %7 %8 %9
        ) ELSE (
            cmake --build "%BUILD_DIR%" --config %CONFIG%
        )
    )
) ELSE (
    cmake --build "%BUILD_DIR%" --config %CONFIG%
)
