# Ninebot Max G3 Tools
A set of scripts changing the SN and unlocking the Region of Ninebot MAX G3.


🛠️ Ninebot Max G3 Unlock & Cruise Control Activation Guide

⚠️ Disclaimer: Modifying your scooter’s firmware may void your warranty and violate local laws. Proceed at your own risk. You are responsible for ensuring compliance with road and traffic regulations in your country.

🔧 What You Need
Ninebot Max G3 (with stock dashboard)

ST-Link V2 programmer

Dupont cables (female-Male)

Windows or linux/mac PC (i tested it only on windows)

g3Scripts latest (ST-Link firmware tools)

Small screwdriver set (Torx or Allen and philips)

Time and patience

📋 Instructions
1. Unbind Scooter from Ninebot App
Before flashing, go into the Ninebot app and remove your G3 from your account.

2. Remove Dashboard
Power off your scooter completely.

Use a screwdriver to remove the dashboard panel.

Carefully disconnect the cable from the dashboard.

3. Connect ST-Link to the VCU
Open the deck of the scooter to access the VCU (Vehicle Control Unit).

Identify the SWD connection pads:

SWDIO

SWCLK

GND

3.3V (power, required for ST-Link)

Connect the ST-Link V2 programmer using Dupont wires:

ST-Link SWDIO → VCU SWDIO

ST-Link SWCLK → VCU SWCLK

ST-Link GND → VCU GND

(required) ST-Link 3.3V → VCU 3.3V

IMPORTANT : the C45 Cpacitor on the board needs to be shorted during the whole read and write process.

4. Backup Original Firmware
Connect the ST-Link to your PC.

Download and extract the Max G3 latest script package.

Run the following batch files in order:

dump_ram.bat

dump_memory.bat

This will generate:

RAM_G3_dumped.bin

MEMORY_G3.bin

Back these up safely. You’ll need them to restore your scooter.

5. Change Region for Speed Unlock
Run change_sn.bat

Choose the region code:

C = USA (40 km/h)

B = Germany (20 km/h)


A new file MEMORY_G3_modded.bin will be created.

6. Flash the Modified Firmware
Run flash_memory_modded.bat

Wait for it to erase and write the memory. This takes a few seconds.

7. Reassemble and Rebind
Disconnect the ST-Link.

Reconnect and reinstall the dashboard.

Open the Ninebot app and rebind your G3.

((if you get the error that the serial number is bound to another account you need to manually edit the dump using a hex editor and change to another serial number.

You should now see an increased speed limit and cruise control option.

🔁 Restore to Stock (If Needed)
If you want to return to the original firmware:

Disconnect from the app.

Connect ST-Link to the VCU.

Run flash_memory_og.bat

Reassemble and rebind.

🚀 Using Cruise Control
To activate cruise control while riding:

Reach your desired speed.

Hold the mode button for 3+ seconds until you hear a beep.

Release the throttle. The scooter will maintain speed.

❗ Troubleshooting
Nothing happens when running scripts → Check ST-Link drivers.

Error during flash → Check wire connections and power.

Speed didn’t change → Make sure you selected C region and rebooted the scooter.

App won’t bind → Reset Bluetooth and scooter before trying again.

This process is for advanced users and may require several attempts if connections are unstable. If you need community support, look for Ninebot Max G3 modding forums or Telegram groups related to G30/G3 firmware.

Based on:
## ScooterTeam 2025 FTW
https://github.com/scooterteam

https://github.com/scooterteam/ZT3Tools
