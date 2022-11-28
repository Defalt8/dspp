@ECHO OFF

@REM ctest
@REM ctest <config>
@REM

SET CONFIG=Release
SET BUILD_DIR=./out/build

IF NOT "%CMAKE_BUILD_DIR%"==""  SET BUILD_DIR=%CMAKE_BUILD_DIR%
IF NOT "%1"==""                 SET CONFIG=%1

cd "%BUILD_DIR%"
ctest -C "%CONFIG%"
