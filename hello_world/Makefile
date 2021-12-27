obj-m := main.o

#vars
ARCH=arm
CROSS_COMPILE=~/dev/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
KERNEL_DIR_BBG=~/dev/bbg/bb-4.14.108
KERNEL_DIR_RPI=~/dev/rpi/rpi_5.10.88
HOST_KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build/

bbg:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_BBG) M=$(PWD) modules

rpi:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_RPI) M=$(PWD) modules

host:
	make -C $(HOST_KERNEL_HEADERS) M=$(PWD) modules

clean_bbg:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_BBG) M=$(PWD) clean

clean_rpi:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_RPI) M=$(PWD) clean

clean:
	make -C $(HOST_KERNEL_HEADERS) M=$(PWD) clean

help_bbg:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_BBG) M=$(PWD) help

help_rpi:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_RPI) M=$(PWD) help

help_host:
	make -C $(HOST_KERNEL_HEADERS) M=$(PWD) help

all:
	make -C $(HOST_KERNEL_HEADERS) M=$(PWD) modules