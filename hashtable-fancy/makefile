CC := gcc
INCLUDE_FLAGS := -I include/
CFLAGS := -Wall
EXEC := hashtable

KEEP_OBJECTS := no

ifeq ($(filter --keep-objects=yes, $(MAKEFLAGS)), --keep-objects=yes)
	KEEP_OBJECTS := yes
endif

build/$(EXEC): build/hashtable.o build/hashtable_type_util_charp.o build/hashtable_type_util_charp_java.o build/main.o
	$(CC) build/hashtable.o build/hashtable_type_util_charp.o build/hashtable_type_util_charp_java.o build/main.o \
		-o build/$(EXEC)

build/main.o: src/main.c include/hashtable.h include/hashtable_type_util_charp.h include/hashtable_type_util_charp_java.h | build
	@$(CC) $(INCLUDE_FLAGS) \
		  $(CFLAGS) \
		  -c src/main.c \
		  -o build/main.o \

build/hashtable_type_util_charp.o: src/hashtable_type_util_charp.c include/hashtable_type_util_charp.h | build
	@$(CC) $(INCLUDE_FLAGS) \
		  $(CFLAGS) \
		  -c src/hashtable_type_util_charp.c \
		  -o build/hashtable_type_util_charp.o \

build/hashtable_type_util_charp_java.o: src/hashtable_type_util_charp_java.c include/hashtable_type_util_charp_java.h | build
	@$(CC) $(INCLUDE_FLAGS) \
		  $(CFLAGS) \
		  -c src/hashtable_type_util_charp_java.c \
		  -o build/hashtable_type_util_charp_java.o \

build/hashtable.o: src/hashtable.c include/hashtable.h | build
	@$(CC) $(INCLUDE_FLAGS) \
		  $(CFLAGS) \
		  -c src/hashtable.c \
		  -o build/hashtable.o \

build:
	mkdir -p build

.PHONY: clean
clean: build
	rm -r build

.PHONY: --keep-objects
--keep-objects: KEEP_OBJECTS
	ifeq(KEEP_OBJECTS, no)
		rm -r build/*.o
	endif
