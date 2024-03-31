COMMON_SRC          := $(wildcard src/*.c)
CFLAGS              := -Wall -Wextra

CC64 				:= gcc
PATCHER64_TARGET	:= ./bin/x86_64/patcher
EXAMPLE64_TARGET	:= ./bin/x86_64/example
EXAMPLE64_BUILD		:= ./build/x86_64/
EXAMPLE64_SRC		:= $(COMMON_SRC)
EXAMPLE64_OBJ		:= $(addprefix ${EXAMPLE64_BUILD}, ${EXAMPLE64_SRC:.c=.o})

CC32				:= gcc -m32
PATCHER32_TARGET	:= ./bin/x86/patcher
EXAMPLE32_TARGET 	:= ./bin/x86/example
EXAMPLE32_BUILD		:= ./build/x86/
EXAMPLE32_SRC		:= $(COMMON_SRC)
EXAMPLE32_OBJ		:= $(addprefix ${EXAMPLE32_BUILD}, ${EXAMPLE32_SRC:.c=.o})

all: $(EXAMPLE32_TARGET) $(EXAMPLE64_TARGET)

$(EXAMPLE64_TARGET): ${EXAMPLE64_OBJ} ${PATCHER64_TARGET}
	mkdir -p $(shell dirname $(EXAMPLE64_TARGET))
	${CC64} ${CFLAGS} ${EXAMPLE64_OBJ} -o ${@}.tmp
	${PATCHER64_TARGET} ${@}.tmp ${@}
	chmod +x ${@}

$(EXAMPLE32_TARGET): ${EXAMPLE32_OBJ} ${PATCHER32_TARGET}
	mkdir -p $(shell dirname $(EXAMPLE32_TARGET))
	${CC32} ${CFLAGS} ${EXAMPLE32_OBJ} -o ${@}.tmp
	${PATCHER32_TARGET} ${@}.tmp ${@}
	chmod +x ${@}

${PATCHER64_TARGET}: patcher.c
	mkdir -p $(shell dirname $(PATCHER64_TARGET))
	${CC64} ${CFLAGS} -DELF64 patcher.c -o $@

${PATCHER32_TARGET}: patcher.c
	mkdir -p $(shell dirname $(PATCHER32_TARGET))
	${CC32} ${CFLAGS} -DELF32 patcher.c -o $@

${EXAMPLE64_BUILD}%.o: %.c
	mkdir -p $(shell dirname $@)
	${CC64} ${CFLAGS} -c $< -o $@

${EXAMPLE32_BUILD}%.o: %.c
	mkdir -p $(shell dirname $@)
	${CC32} ${CFLAGS} -c $< -o $@

.PH0NY:

clean: .PH0NY
	rm -rf build/

fclean: clean .PH0NY
	rm -rf bin/

re: fclean .PH0NY all
