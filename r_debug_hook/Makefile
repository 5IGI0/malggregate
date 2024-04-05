CFLAGS              := -Wall -Wextra
CC64 				:= gcc
EXE_TARGET64		:= ./bin/x86_64/main
LIB_NAME64			:= prompt
LIB_TARGET64		:= ./bin/x86_64/lib${LIB_NAME64}.so

all: $(EXE_TARGET64) .PH0NY

${EXE_TARGET64}: ${LIB_TARGET64} main.c
	mkdir -p $(shell dirname $@)
	${CC64} -o $@ main.c -L$(shell dirname ${LIB_TARGET64}) -l${LIB_NAME64} -lcrypt

${LIB_TARGET64}: libprompt.c
	mkdir -p $(shell dirname $@)
	${CC64} -o $@ $< -shared -fPIC

run: .PH0NY $(EXE_TARGET64)
	LD_LIBRARY_PATH=$(shell pwd)/bin/x86_64/ ./bin/x86_64/main

clean: .PH0NY
	rm -rf bin/

fclean: clean .PH0NY
	rm -rf bin/

re: fclean .PH0NY all

.PH0NY:
