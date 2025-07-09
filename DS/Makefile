CC=gcc
CFLAGS=-Wall -g -lmingw32
DST=DS.exe
SRC:=$(wildcard ./src/**/*.c) $(wildcard ./src/*.c) $(wildcard ./test/**/*.c) $(wildcard ./test/*.c) ./main.c
OBJ:=$(patsubst %.c, %.o, $(SRC))
INCLUDE= -I ./include/

$(DST) : $(OBJ)
	@echo $(OBJ)
	@mkdir -p out
	$(CC) $(OBJ) -o out/$(DST)

run: $(DST)
	./out/$(DST)

%.o : %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) out/$(DST)
	@rm -rf out/