@echo off
openocd -s oocd/scripts -f oocd/scripts/interface/stlink.cfg -f oocd/scripts/target/at32.cfg -c "init" -c "dump_image MEMORY_G3.bin 0x08000000 0x0803FFFF" -c "exit"
IF EXIST MEMORY_G3.bin (
	g3tool.exe MEMORY_G3.bin verify
) ELSE (
	echo MEMORY_G3.bin missing.
)
pause
