@echo off
Setlocal EnableDelayedExpansion

IF NOT EXIST MEMORY_G3_modded.bin (
	IF EXIST MEMORY_G3.bin (
		copy MEMORY_G3.bin MEMORY_G3_modded.bin
	) ELSE (
		echo MEMORY_G3.bin missing.
	)
)
IF EXIST MEMORY_G3_modded.bin (
	echo C - USA
	echo B - Germany
	set /p userchoice="Choose a new region of the scooter: "
	g3tool.exe MEMORY_G3_modded.bin changeregion !userchoice!
)
pause
