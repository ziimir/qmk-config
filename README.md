### How To

1. Copy this to qmk_firmware folder
2. run `qmk compile -kb bastardkb/charybdis/4x6/v2/promicro -km ziimir`
3. Flush generated hex file to keyboard with qmk toolbox (`ATmega32U4`)

----

to put blackpill into boot

Use the onboard BOOT0 and NRST button to put the board into bootloader mode:

press and hold the BOOT0 button
press and release NRST (reset) button to power cycle the processor
release BOOT0 button
