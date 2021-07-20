#
# Usage:
#	make 		- compile the files
#	make clean 	- remove the compiled files
#

CC := gcc				# compiler to use
CFLAGS := -Wall -g		# compiling options
LDFLAGS := -ll			# lex lib

EXEC := proj1			# name of the executable
lexcfile := lex.yy.c
lexofile := $(addsuffix .o, $(basename $(lexcfile)))

# all is the default rule
all: $(EXEC)

# rule to generate the executable
$(EXEC): $(lexofile) driver.o
	$(CC) -o $@ $^ $(LDFLAGS)

# rule to generate *.o
driver.o: driver.c token.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
$(lexofile): $(lexcfile) token.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to convert *.l into *.c
$(lexcfile): *.l
	lex $<

# clean
.PHONY: clean
clean:
	rm -f *.o $(lexcfile) $(EXEC)
