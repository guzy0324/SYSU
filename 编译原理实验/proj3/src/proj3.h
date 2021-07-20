#ifndef _PROJ3_H
#define _PROJ3_H

#include <stdint.h>

#define false 0
#define true 1
#define FALSE 0
#define TRUE 1
#define bool char

#define STACK_SIZE 100
#define ST_SIZE 500
#define ATTR_SIZE 2000

/*
 * error type for error reporting routine 
 */
#define STACK_OVERFLOW 100
#define REDECLARATION 101
#define ST_OVERFLOW 102
#define UNDECLARATION 103
#define ATTR_OVERFLOW 104
#define NOT_USED 105
#define ARGUMENTS_NUM1 106
#define ARGUMENTS_NUM2 107
#define BOUND 108
#define PROCE_MISMATCH 109
#define VAR_VAL 110
#define CONSTANT_VAR 111
#define EXPR_VAR 112
#define CONSTANT_ASSIGN 113
#define INDX_MIS 114
#define FIELD_MIS 115
#define FORW_REDECLARE 116
#define REC_TYPE_MIS 117
#define ARR_TYPE_MIS 118
#define VARIABLE_MIS 119
#define FUNC_MISMATCH 120
#define TYPE_MIS 121
#define NOT_TYPE 122
#define ARR_DIME_MIS 123
#define MULTI_MAIN 124
#define STRING_ASSIGN 125
#define NO_MAIN 126
#define OP_MIS 127
#define ARG_MIS 128
#define RET_MIS 129

/*
 * processing instruction for error reporting routine 
 */
#define CONTINUE 0	     /* print error and return to the caller */
#define ABORT 1		     /* print the fatal error and abort execution */

/*
 * these definitions correspond to the fields of a stack element 
 */
#define MARKER 1
#define NAME 2
#define ST_PTR 3
#define DUMMY 4
#define USED 5

/*
 * the possible attributes for symbol table.  the comment to the right
 * describe the attribute's value.  Notice the small constants are given to
 * the attributes which are common to all the ids, so that we can do some
 * sorting in the link list 
 */
#define NAME_ATTR 1	     /* value: id lexeme pointer, set by InsertEntry */
#define NEST_ATTR 2	     /* value: nesting level, set by InsertEntry */
#define TREE_ATTR 3	     /* value: point back to the subtree */
#define PREDE_ATTR 4	     /* value: is this id predefined? */
#define TYPE_ATTR 6	     /* value: pointer to the type tree for a
			      * varible, constant id or function */
#define VALUE_ATTR 7	     /* value: the value of a constant id (integer,
			      * charater or string pointer) */
#define OFFSET_ATTR 8
	     
#define KIND_ATTR 5	     /* value: see below */

#define DIMEN_ATTR   9
#define ARGNUM_ATTR 10

/*
 * the possible values of attribute kind_attr 
 */
#define CONST 1
#define VAR 2
#define FUNCFORWARD 3
#define FUNC 4
#define REF_ARG 5
#define VALUE_ARG 6
#define FIELD 7
#define TYPEDEF 8
#define PROCFORWARD 9
#define PROCE 10
#define CLASS 11
#define ARR 12


/*********************************data structures**********************/

/*
 * !!!!!!!!! WARNING !!!!!!!!!! all the data structures and variables defined
 * below are private to the symbol table operating routines. Do NOT use them
 * directly unless you really understant the whole symbol table structure. 
 */

/*
 * struct of symbol table stack 
 */
struct
{
  bool marker;		     /* mark the beginning of a block */
  int name;		     /* point to the lexeme of the id */
  int st_ptr;		     /* point to the id's symble table entry */
  bool dummy;		     /* dummy element to indicate a undeclared id */
  bool used;		     /* this id is used? */
} stack[STACK_SIZE];	     /* stack array */

/*
 * struct of element of attribute list 
 */
typedef struct
{
  char attr_num;	     /* attribute number ( < 256 ) */
  uintptr_t attr_val;		     /* attribute value */
  int next_attr;
} attr_type;		     /* define the struct type and the pointer type */

/*
 * procedure declaration 
 */

void STInit();
void error_msg(int, int, int, int);
int InsertEntry(int);
int LookUp(int);
int LookUpHere(int);
int LookUpField(int, int);
void OpenBlock();
void CloseBlock();
int IsAttr(int, int);
uintptr_t GetAttr(int, int);
void SetAttr(int, int, uintptr_t);
void STPrint();
void Push(int, int, int, int);
char *seq_str(int);

#include <string.h>

/* Different modes for convert_ID_to_ST. */
#define DECL_MODE 0 // This mode indicates that the symbol hasn't been declared, so the symbol should be inserted into the symbol table.
#define VAR_MODE 1 // This mode indicates that the symbol is a declared variable, so the symbol should be looked up in the symbol table.
#define FIELD_MODE 2 // This mode indicates that the symbol is a field declared in a class, so the symbol should be looked up in the symbol table.

/* STNode_table has the same size as the symbol table.
It stores unique nodes for all the symbol.
These nodes can be indexed by indices of symbol table. */
tree STNode_table[ST_SIZE];

/* convert_ID_to_ST converts IDNode to STNode and returns the symbol's index in symbol table.
It reports undelared error and multi-declared error. */
int convert_ID_to_ST(tree* node_p, int mode, int st_ptr);

/* type field stores the STNode in the type tree.
dim field stores the dimension of the type tree.
FieldOps in type tree are regarded as REC_TYPE_MIS, since they seem to be meaningless.
TypeDim is helpful for type matching, e.g. type matching for lvalue and rvalue in AssignmentStatement. */
typedef struct TypeDim_struct
{
    tree type;
    int dim;
} TypeDim;

/* MakeTypeDim works as a constructor for TypeDim. */
TypeDim MakeTypeDim(tree type, int dim);
#endif
