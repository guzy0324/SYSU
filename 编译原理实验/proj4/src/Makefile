#
# Usage:
#	make 		- compile the files
#	make clean 	- remove the compiled files
#

CC := gcc				# compiler to use
CFLAGS := -Wall -g		# compiling options
LDFLAGS :=

EXEC := codeGen			# name of the executable

# all is the default rule
all: $(EXEC)

# rule to generate the executable
$(EXEC): lex.yy.o y.tab.o proj2.o proj3.o semantic.o proj4.o
	$(CC) -o $@ $^ $(LDFLAGS)

# rule to generate *.o
proj4.o: proj4.c proj4.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
semantic.o: semantic.c proj3.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
proj3.o: proj3.c proj3.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
proj2.o: proj2.c proj2.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
lex.yy.o: lex.yy.c proj2.h y.tab.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to generate *.o
y.tab.o: y.tab.c proj2.h
	$(CC) $(CFLAGS) -o $@ -c $<

# rule to convert *.l into *.c
lex.yy.c: *.l
	lex $<

# rule to convert *.y into *.[c|h]
y.tab.c y.tab.h: *.y
	yacc -d $<

# clean
.PHONY: clean
clean:
	rm -f *.o *.yy.* *.tab.* $(EXEC)
