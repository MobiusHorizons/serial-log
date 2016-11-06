DEPS_SRC := $(shell ls deps/*/*.c)
DEPS_INC := $(shell ls -d deps/*/ | sed -e 's/^\s*/-I/')


CCFLAGS := $(CCFLAGS) $(DEPS_INC)
ALL: serial-log

serial-log: main.c $(DEPS_SRC)
	cc -o serial-log $(CCFLAGS) main.c $(DEPS_SRC)
