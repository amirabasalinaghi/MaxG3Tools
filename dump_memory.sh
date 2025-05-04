#!/bin/bash

set -e

openocd -s oocd/scripts \
    -f oocd/scripts/interface/stlink.cfg \
    -f oocd/scripts/target/at32.cfg \
    -c "init" \
    -c "dump_image MEMORY_G3.bin 0x08000000 0x0803FFFF" \
    -c "exit"

if [ -f "MEMORY_G3.bin" ]; then
    ./g3tool MEMORY_G3.bin verify
else
    echo "MEMORY_G3.bin missing."
fi

read -p "Press enter to continue..."
