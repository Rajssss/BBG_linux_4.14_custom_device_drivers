obj-m := main.o

#vars
ARCH=arm
CROSS_COMPILE=/home/rajssss/dev/bbg/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
KERNEL_DIR=/home/rajssss/dev/bbg/bbg_4.14.108/
HOST_KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build/

cross:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) clean

help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) help

all:
	make -C $(HOST_KERNEL_HEADERS) M=$(PWD) modules