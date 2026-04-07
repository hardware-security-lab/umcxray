SRC_DIR = src
BUILD_DIR = build
INC_DIR = ../includes
MODNAME = umcxray
TARGET = $(BUILD_DIR)/$(MODNAME)

CC = gcc
LD = ld

CFLAGS = -m64 -O2 -D_KERNEL -DDEBUG -mcmodel=kernel -I/usr/include/sys -I$(INC_DIR)
LDFLAGS = -r -ztype=kmod

include objs.mk

all: $(TARGET)

$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

ins:
	pfexec modload $(TARGET)

info:
	@printf "\n"
	@modinfo | grep $(MODNAME) || true
	@printf "\n======================================================================================\n\n"
	@tail /var/adm/messages
	@printf "\n"

rem:
	pfexec modunload $(MODNAME)

