obj-m := br_debug.o

MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
CC += ${MY_CFLAGS}

SLAVE_IF ?= enp0s8

LINUX_DIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) modules EXTRA_CFLAGS="$(MY_CFLAGS)"
clean:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) clean
