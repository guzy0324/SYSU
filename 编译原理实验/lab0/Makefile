# Variables allow a text string to be defined once and substituted in multiple places later (see section How to Use Variables).

CC := gcc
CCFLAGS :=
EXEC := hello

# In general, a rule looks like this:
#
# targets : dependencies
# 			command
# 			...
#
# or like this:
#
# targets : dependencies : command
# 			command
# 			...

# all is the default rule
all: $(EXEC)

$(EXEC): hello.o
		$(CC) $(CCFLAGS) -o $@ $^
		@echo "Built $@ successfully"

hello.o: hello.s
		$(CC) -c $^

hello.s: hello.i
		$(CC) -S $^

hello.i: hello.c
		$(CC) -E $^ > $@

clean:
		rm -f *.i *.s *.o $(EXEC)
