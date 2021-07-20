# Variables allow a text string to be defined once and substituted in multiple places later (see section How to Use Variables).

LEX := lex
CC := gcc
CCFLAGS := -ll
EXEC := my

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

$(EXEC): lex.yy.c
		$(CC) -o $@ $^ $(CCFLAGS)
		@echo "Built $@ successfully"

lex.yy.c: example.l
		$(LEX) $^

clean:
		rm -f *.c $(EXEC)
