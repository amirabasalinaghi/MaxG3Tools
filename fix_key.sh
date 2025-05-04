#!/bin/bash

set -e

echo "You can drag files into the terminal to specify their location."

read -p "Enter the location of the old dump: " olddump
read -p "Enter the location of the new dump: " newdump

./g3tool "$newdump" fixkey "$olddump"

read -p "Press enter to continue..."