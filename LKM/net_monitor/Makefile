obj-m := net_monitor.o

MY_CFLAGS += -g -DDEBUG

ccflags-y := $(MY_CFLAGS)

LINUX_DIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) clean
