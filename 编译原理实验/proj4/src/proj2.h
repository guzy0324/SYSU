#ifndef _PROJ2_H
#define _PROJ2_H

#
/* proj2.h */
typedef struct treenode
        {       /* syntax tree node struct */
                int NodeKind, NodeOpType, IntVal;
                struct treenode *LeftC, *RightC;
        } ILTree, *tree;

tree Root;

typedef union
{
  int intg;
  tree tptr;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED

#define ProgramOp       100
#define BodyOp          101
#define DeclOp          102
#define CommaOp         103
#define ArrayTypeOp     104
#define TypeIdOp        105
#define BoundOp         106
#define RecompOp        107
#define ToOp            108
#define DownToOp        109
#define ConstantIdOp    110
#define ProceOp         111
#define FuncOp          112
#define HeadOp          113
#define RArgTypeOp      114
#define VArgTypeOp      115
#define StmtOp          116
#define IfElseOp        117
#define LoopOp          118
#define SpecOp          119
#define RoutineCallOp   120
#define AssignOp        121
#define ReturnOp        122
#define AddOp           123
#define SubOp           124
#define MultOp          125
#define DivOp           126
#define LTOp            127
#define GTOp            128
#define EQOp            129
#define NEOp            130
#define LEOp            131
#define GEOp            132
#define AndOp           133
#define OrOp            134
#define UnaryNegOp      135
#define NotOp           136
#define VarOp           137
#define SelectOp        138
#define IndexOp         139
#define FieldOp         140
#define SubrangeOp      141
#define ExitOp          142
#define ClassOp         143
#define MethodOp        144
#define ClassDefOp      145

#define IDNode          200 
#define NUMNode         201
#define CHARNode        202
#define STRINGNode      203
#define DUMMYNode       204
#define EXPRNode        205
#define INTEGERTNode	206
#define CHARTNode	207
#define BOOLEANTNode	208
#define STNode		209

tree NullExp();
tree MakeLeaf(int, int);
tree MakeTree(int, tree, tree);
tree LeftChild(tree);
tree RightChild(tree);
tree MkLeftC(tree, tree);
tree MkRightC(tree, tree);
int IsNull(T);
void SetNode(tree, tree);
void SetNodeOp(tree, int);
void SetLeftTreeOp(tree, int);
void SetRightTreeOp(tree, int);
void SetLeftChild(tree, tree);
void SetRightChild(tree, tree);

#include <stdlib.h>
extern int yycolumn, yyline;
extern int strg_tbl_size;

/* Leaf table contains unique IDNode and StringNode. It can help to reduce the consumption of space when the same ID or string is used for several times in a program.
The length of leaf table is equal to the length of string table.
And indices of strings in string table are also served as indices of leaf nodes in leaf table.
And it also stores the number of reference of that symbol right after the space to store the leaf node pointer.
It is also an array resembling a vector. */
tree* leaf_table;

/* leaf_table_size is the total memory allocated to the string table, and it is equl to string_table_size. */
int leaf_table_size;

/* maintain_leaf_table finds a leaf node in leaf table, and increase the number of reference.
If the function doesn't find the node, it may reallocate the space.
If the allocation is not successful, the function will print the error and return dummy. */
tree maintain_leaf_table(int NodeKind, int IntVal);

/* IntegerT returns a IntegerT node. */
tree IntegerT();

/* A global variable for field type. */
tree FieldTypeGlobal;

/* ATO is short for ArgTypeOp. ATO is like a inherit attribute, which needs to be transmitted by parameters. The stack is used to store parameters during a recursion.
It is also an array resembling a vector. */
int* ATO_stack;

/* ATO_stack_back is the top of the stack. */
int ATO_stack_back;

/* ATO_stack_size is the total memory allocated to the string table. */
int ATO_stack_size;

/* ATO_stack_push pushes an ATO into the stack. */
void ATO_stack_push(int ATO);

int NodeKind(tree T);
int IntVal(tree T);

extern int* index_table;
extern int index_table_length;
extern int loc_index(int leng, char* text);
int loc_str(char* str);


#endif
