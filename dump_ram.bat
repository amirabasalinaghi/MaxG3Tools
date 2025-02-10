@echo off
openocd -s oocd/scripts -f oocd/scripts/interface/stlink.cfg -f oocd/scripts/target/at32.cfg -c "init" -c "dump_image RAM_ZT3Pro_dumped.bin 0x20000000 0x7D00" -c "exit"
pause