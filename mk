
arm-none-eabi-objcopy -O binary cube.axf t.bin

/home/paul/qemu-4.0-arm/bin/qemu-system-arm  -M versatilepb -m 128M -kernel t.bin -serial mon:stdio



 





