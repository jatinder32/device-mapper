KERNELDIR=/lib/modules/$(shell uname -r)/build
INSTALL_DIR=modules
INCLUDE=include/
SUBD := $(shell pwd)
SRC=src/

obj-m += SBD.o
SBD-objs += $(SRC)sbd.o
obj-m +=SBD_API.o
SBD_API-objs +=$(SRC)sbd_api.o 

all: default 

default:
	$(MAKE) -C  $(KERNELDIR) SUBDIRS=$(SUBD) modules
	@rm -rf ${INSTALL_DIR}
	@mkdir ${INSTALL_DIR}
	@mv -f *.ko *.o *.mod.c .*.cmd ${INSTALL_DIR}



clean:
	rm -rf ${INSTALL_DIR}

