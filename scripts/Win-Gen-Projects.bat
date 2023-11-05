@echo off

pushd %~dp0\..\

for /f %%A in ('cd') do set "CRYSTAL_DIR=%%~fA"
setx CRYSTAL_DIR "%CRYSTAL_DIR%" /M

call vendor\premake\premake5.exe vs2022

popd
PAUSE