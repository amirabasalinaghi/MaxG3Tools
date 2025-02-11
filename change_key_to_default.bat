@echo off
IF NOT EXIST MEMORY_ZT3Pro_modded.bin (
	IF EXIST MEMORY_ZT3Pro.bin (
		copy MEMORY_ZT3Pro.bin MEMORY_ZT3Pro_modded.bin
	) ELSE (
		echo MEMORY_ZT3Pro.bin missing.
	)
)
IF EXIST MEMORY_ZT3Pro_modded.bin (
	zt3tool.exe MEMORY_ZT3Pro_modded.bin key
)
pause
