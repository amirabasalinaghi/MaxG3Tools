#!/bin/bash

set -e

if [ ! -f "MEMORY_G3_modded.bin" ]; then
    if [ -f "MEMORY_G3.bin" ]; then
        cp MEMORY_G3.bin MEMORY_G3_modded.bin
    else
        echo "MEMORY_G3.bin missing."
    fi
fi

if [ -f "MEMORY_G3_modded.bin" ]; then
    ./g3tools MEMORY_G3_modded.bin key
fi

read -p "Press enter to continue..."
