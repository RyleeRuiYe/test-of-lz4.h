obj-m += compresstest.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := 4.10.0

LINUX_KERNEL_PATH := /usr/src/linux-source-$(LINUX_KERNEL)/linux-source-$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
