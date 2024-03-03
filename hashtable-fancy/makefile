TARGET_EXEC := hashtable

INCLUDE_DIR := ./include
BUILD_DIR := obj
SOURCE_DIR := ./src

CC := gcc
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIR))
CFLAGS := $(INCLUDE_FLAGS) -MMD -MP

SRCS := $(shell find $(SOURCE_DIR) -name '*.c')
OBJS := $(patsubst %.c, %.o, $(SRCS))
DEPS := $(OBJS:.o=.d)


# Final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# Build step for C source files
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
