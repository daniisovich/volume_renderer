@echo off

pushd ..
call external\premake\premake5.exe vs2022
popd ..

pause