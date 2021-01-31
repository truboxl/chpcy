CC ?= $(uname -m)-linux-android-clang

PREFIX ?= /usr/local

all: test-libprocessgroup chpcy-libprocessgroup

test-libprocessgroup:
	${CC} test.c -o test -l processgroup -I platform_system_core/libprocessgroup/include

chpcy-libprocessgroup:
	${CC} chpcy.c -o chpcy -l processgroup -I platform_system_core/libprocessgroup/include

test-libcutils:
	${CC} test.c -o test -l cutils -I platform_system_core/libcutils/include

chpcy-libcutils:
	${CC} chpcy.c -o chpcy -l cutils -I platform_system_core/libcutils/include

clean:
	rm -f test
	rm -f chpcy
	rm -f a.*

install: all
	mkdir -p ${PREFIX}/bin
	install -Dm 0755 chpcy ${PREFIX}/bin

uninstall:
	rm -fr ${PREFIX}/bin/chpcy

help:
	@paste Makefile | sed -e "s|\t.*||g" | sed -e "s|.*?=.*||g" | sed -e "s|:.*||g" | strings | sort
