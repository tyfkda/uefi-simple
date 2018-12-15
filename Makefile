CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall -Werror \
         -e EfiMain
IMAGE_DIR = image

.PHONY: all run clean

all: $(IMAGE_DIR)/EFI/BOOT/BOOTX64.EFI

%.efi: %.dll
	objcopy --target=efi-app-x86_64 $< $@

%.dll: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu: OVMF.fd $(IMAGE_DIR)/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -nographic -bios OVMF.fd -drive file=fat:rw:$(IMAGE_DIR),media=disk,format=raw

$(IMAGE_DIR)/EFI/BOOT/BOOTX64.EFI: main.efi
	mkdir -p $(IMAGE_DIR)/EFI/BOOT
	ln -sf ../../../main.efi $(IMAGE_DIR)/EFI/BOOT/BOOTX64.EFI

ZIP_FN = OVMF-X64-r15214.zip
OVMF.fd:
	wget http://downloads.sourceforge.net/project/edk2/OVMF/$(ZIP_FN)
	unzip $(ZIP_FN) $@
	rm $(ZIP_FN)

clean:
	rm -rf main.efi $(IMAGE_DIR)


################################################
# Docker

docker_image ?= uefi-baremetal
tag ?= dev

docker_args ?= -e LOCAL_UID=$(shell id -u) -e LOCAL_GID=$(shell id -g) \
	-v $(shell pwd):$(shell pwd) -w $(shell pwd) \
	-v /etc/localtime:/etc/localtime:ro \

build-docker-image:
	docker build docker/ -t $(docker_image):$(tag)

docker-make:
	@docker run --rm $(docker_args) $(docker_image):$(tag) make $(MAKE_TARGET)

docker-interactive:
	@docker run -it --rm $(docker_args) $(docker_image):$(tag)
