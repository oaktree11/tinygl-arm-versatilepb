
arm-none-eabi-objcopy -O binary cube.axf t.bin

qemu-system-arm  -M versatilepb -m 128M -kernel t.bin -serial mon:stdio



 





