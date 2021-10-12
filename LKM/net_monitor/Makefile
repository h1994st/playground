ifndef NET_DEV_NAME
	override NET_DEV_NAME = \"eno1\"
endif

obj-m := net_monitor.o

MY_CFLAGS += -g -DDEBUG -DNET_DEV_NAME=${NET_DEV_NAME}

ccflags-y := $(MY_CFLAGS)

LINUX_DIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(LINUX_DIR) M=$(PWD) clean
