# Syntax Analyzer

## Requirements

- Ubuntu 20.04.1 LTS (Linux version 5.4.0-58-generic x86_64)
- GNU make 4.2.1 Built for x86_64-pc-linux-gnu
- gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 
- flex 2.6.4
- bison (GNU Bison) 3.5.1

## Files Structure

- proj2.pdf: document describing project 2
- project2-qa.pdf: Q&A about project2
- grading.pdf: grading sheet of project 2
- src/: source files provided for you to start from
	- lexer.l: the lex file from your project 1 (remember to update following the instructions in proj2.pdf)
	- grammar.y: the yacc file, where you should mainly write your codes
	- proj2.h: the provided header file (no change needed)
	- proj2.c: the provided source file with the support routines (remember to update following the instructions in proj2.pdf)
	- Makefile: an example makefile to compile your codes
- test_files/: example MINI-JAVA source files for testing
- proj2-supplementary-test-files/: supplementary example MINI-JAVA source files for testing

## How To Build And Run

Enter the directory src.

```
$ cd src
```

Build.

```
$ make
```

Run.

```
$ .\proj2 < "input_file" > "output_file"
```

Clean binary files.

```
$ make clean
```
