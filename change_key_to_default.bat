@echo off
IF NOT EXIST MEMORY_G3_modded.bin (
	IF EXIST MEMORY_G3.bin (
		copy MEMORY_G3.bin MEMORY_G3_modded.bin
	) ELSE (
		echo MEMORY_G3.bin missing.
	)
)
IF EXIST MEMORY_G3_modded.bin (
	G3tool.exe MEMORY_G3_modded.bin key
)
pause
