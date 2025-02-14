@echo off
openocd -s oocd/scripts -f oocd/scripts/interface/stlink.cfg -f oocd/scripts/target/at32.cfg -c "init" -c "dump_image MEMORY_ZT3Pro.bin 0x08000000 0x0803FFFF" -c "exit"
IF EXIST MEMORY_ZT3Pro.bin (
	zt3tool.exe MEMORY_ZT3Pro_modded.bin verify
) ELSE (
	echo MEMORY_ZT3Pro.bin missing.
)
pause
