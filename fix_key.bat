@echo off

echo You can drag files into the console to specify their location.
set /p olddump="Enter the location of the old dump: "
set /p newdump="Enter the location of the new dump: "
G3tool.exe "%newdump%" fixkey "%olddump%"
pause