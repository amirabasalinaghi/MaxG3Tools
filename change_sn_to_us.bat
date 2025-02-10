@echo off
IF EXIST MEMORY_ZT3Pro.bin (
	copy MEMORY_ZT3Pro.bin MEMORY_ZT3Pro_modded.bin
	zt3tool.exe MEMORY_ZT3Pro_modded.bin
) ELSE (
	echo MEMORY_ZT3Pro.bin missing.
)
pause
