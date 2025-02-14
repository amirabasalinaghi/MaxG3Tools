@echo off
Setlocal EnableDelayedExpansion

IF NOT EXIST MEMORY_ZT3Pro_modded.bin (
	IF EXIST MEMORY_ZT3Pro.bin (
		copy MEMORY_ZT3Pro.bin MEMORY_ZT3Pro_modded.bin
	) ELSE (
		echo MEMORY_ZT3Pro.bin missing.
	)
)
IF EXIST MEMORY_ZT3Pro_modded.bin (
	echo E - Europe
	echo Z - China
	echo U - USA
	echo D - Germany
	echo A - Asia
	set /p userchoice="Choose a new region of the scooter: "
	zt3tool.exe MEMORY_ZT3Pro_modded.bin changeregion !userchoice!
)
pause
