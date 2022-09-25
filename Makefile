obj-m += kset-example.o
obj-m += kobject-example.o
obj-m += kref-example.o
obj-m += uevent-example.o

KERNELDIR ?=/lib/modules/5.10.102.1-microsoft-standard-WSL2/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules
.PHONY clean:
	rm -rf *.ko *.o Module.* modules.* *.mod *.mod.c
