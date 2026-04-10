SRC_DIR = src
BUILD_DIR = build
INC_DIR = includes

PROG = umcxray_reader
TARGET = $(BUILD_DIR)/$(PROG)

CC = gcc
CFLAGS = -O2 -Wall -Wextra -I$(INC_DIR)
LIBS = -lnvpair

include objs.mk

all: $(TARGET)

$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(CC) $(LIBS) -o $@ $(OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run:
	pfexec ./$(TARGET)

