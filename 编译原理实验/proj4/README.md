# Syntax Analyzer

## Requirements

- Ubuntu 20.04.2 LTS (Linux version 5.4.0-58-generic x86_64)
- GNU make 4.2.1 Built for x86_64-pc-linux-gnu
- gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 
- flex 2.6.4
- bison (GNU Bison) 3.5.1

## Files Structure

- proj3.pdf: document describing project 3
- lab_8.pdf:  document describing project 3
- grading.pdf: grading sheet of project 3
- src/: source files provided for you to start from
	- lexer.l: For lexical analysis, providing tokens
	- grammar.y: For syntax parsing, providing abstract syntax tree
    - proj2.[h|c]: Tree manipulation routines (mostly unchanged)
    - semantic.c: Primary place to write your codes
	- proj3.[h|c]: Symbol table manipulation routines (mostly unchanged)
	- Makefile: an example makefile to compile your codes
- tests: example MINI-JAVA source files for testing

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
$ .\codeGen < "input_file" -o "executable_program" > "output_file"
```

Validate the correctness of executable_protram.

```
$ spim load "executable_program" [< "input_file"]
```

Clean binary files.

```
$ make clean
```
