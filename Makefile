CCFLAGS := -Wall -Wextra

BIN := schnell

src_files := $(wildcard *.c)
obj_files := $(patsubst %.c,%.o,$(src_files))

.PHONY: all clean remake debug redebug

all: CCFLAGS += -O2
all: $(BIN)

clean:
	rm -f $(BIN) *.o

debug: CCFLAGS += -DDEBUG -g -O0 -fno-inline
debug: $(BIN)

remake: clean all

redebug: clean debug

$(BIN): $(obj_files)
	$(CC) $(CCFLAGS) -o $@ $^

%.o: %.c *.h
	$(CC) $(CCFLAGS) -c -o $@ $(filter %.c,$^)
