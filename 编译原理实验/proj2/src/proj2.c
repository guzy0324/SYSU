/* %A% ********************************************************/
/* 
proj2.c

This file consists of 4 parts
	a. the data structure of a tree node
	b. the tree operation functions, from "CopyTree"
           to "SetRightChild"
	c. the tree printing function

The functions in this file are contributed by Chunmin Qiao and
Aggelos Varvitsiotis.
*/

/*	define syntax tree node and pointer type	*/
#include <stdio.h>
#include "proj2.h"

ILTree dummy = { DUMMYNode, 0, 0, 0, 0 };
ILTree integer = { INTEGERTNode, 0, 0, 0, 0 };


/********************************************************
*	This function return a DUMMYNode to the caller  *
*	Note: All the dummy nodes are corresponding to  *
*	the save memory location.  So any attampt to    *
*	use it for the other purposes will cause        *
*	trouble                                         *
********************************************************/
tree NullExp()
{
	return (&dummy);
}

/***********************************************************
*	This function will create a leafnode with it	   *
*	NodeKind and IntVal to be Kind and N, respectively *
***********************************************************/
tree MakeLeaf(Kind, N)
int Kind, N;
{
tree 	p;

	p = (tree)malloc(sizeof(ILTree));
	p->NodeKind = Kind;     
	p->IntVal = N;
	return (p);
}
	
/***********************************************************
* 	This function create a interior node of NodeOptype *
*	with children to be Left and Right, respectively,  *
***********************************************************/
tree MakeTree(NodeOp, Left, Right)
int NodeOp;
tree Left, Right;
{
tree 	p;

	p = (tree)malloc(sizeof(ILTree));
	p->NodeKind = EXPRNode; 
	p->NodeOpType = NodeOp;
	p->LeftC = Left;
	p->RightC = Right;
	return (p);
}

/*********************************************************
*	This function returns leftchild of the treenode  *
*********************************************************/
tree LeftChild(T)
tree T;
{
	if (NodeKind(T) != EXPRNode)
		return (NullExp());
	return (T->LeftC);
}

/*********************************************************
*	This function returns rightchild of the treenode *
*********************************************************/
tree RightChild(T)
tree T;
{
	if (NodeKind(T) != EXPRNode)
		return (NullExp());
	return (T->RightC);
}

/********************************************************
*	This function makes subtree T1 to be the        *
*	leftmost child of the tree T2, return T2	*
********************************************************/	
tree MkLeftC(T1, T2)
tree T1, T2;
{
tree p,q;

        if (IsNull(T2)) return (T1);
	p = T2;
	q = LeftChild(p);
	/* replace the leftmost DUMMYNode */
	while ( !IsNull(q) )
	{
		p = q;
		q = LeftChild(p);
	}
	p->LeftC = T1;
	return(T2);
}

/********************************************************
*	This function makes subtree T1 to be the        *
*	rightmost child of the tree T2, return T2	*
********************************************************/	
tree MkRightC(T1, T2)
tree T1, T2;
{
tree p,q;

        if (IsNull(T2)) return (T1);
	p = T2;
	q = RightChild(p);
	/* replace the rightmost DUMMYNode */
	while ( !IsNull(q) )
	{
		p = q;
		q = RightChild(p);
	}
	p->RightC = T1;
	return(T2);
}

/********************************************************
*	This function returns NodeOpType of a node	*
********************************************************/
NodeOp(T)
tree T;
{
        if (NodeKind(T) != EXPRNode)
        {
          printf("NodeOP(): This node must be an EXPRNode!\n");
          return(0);
        }
	return (T->NodeOpType);
}

/********************************************************
*	This function returns NodeKind of a node 	*
********************************************************/
NodeKind(T)
tree T;
{
	return (T->NodeKind);
}


/********************************************************
*	This function returns IntVal of a leafnode	*
********************************************************/
IntVal(T)
tree T;
{
	if ( NodeKind(T) == EXPRNode )
        {
		printf("IntVal(): This node must be a leaf node!\n");
                return(-1);
        }
	return (T->IntVal);
}

/********************************************************
* 	This function return true if the node is 	*
*	DUMMYNode, false otherwise.			*
********************************************************/
IsNull(T)
tree T;
{
	return ( NodeKind(T) == DUMMYNode );
}

/********************************************************
*	This function sets the Target Node to be	*
*	Source Node (only for Non Dummy Target Node)	*
********************************************************/
void SetNode(Target, Source)
tree Target, Source;
{
    if ((Target->NodeKind = Source->NodeKind) != EXPRNode)
	{
	Target->IntVal = Source->IntVal;
	Target->LeftC = NullExp();
	Target->RightC = NullExp();
	}
    else
	{
	Target->NodeOpType = Source->NodeOpType;
	Target->LeftC = Source->LeftC;
	Target->RightC = Source->RightC;
	}
}

/********************************************************
*	This function sets the NodeOpType  to be	*
*	to be NewOp (only for Interior EXPRNode)	*
********************************************************/
void SetNodeOp(T, Op)
tree T;
int Op;
{
	if (NodeKind(T) != EXPRNode)
		printf("SetNodeOp(): This node must be an EXPRNode!\n");
	else
		T->NodeOpType = Op;
}

/********************************************************
*	This function sets the tree root and all its	*
*	left subtree root to be a NewOp node, used only *
*	in construct a Record Component subtree.	*
*	Name Changed by Hui-Jung Chang, Oct.30, 1992	*
********************************************************/	
void SetLeftTreeOp(T, Op)
tree T;
int Op;
{
tree 	p;

	p = T;
   	do
	  {
		SetNodeOp(p, Op);
		p = LeftChild(p);
	  }
	while ( !IsNull(p));
}


/********************************************************
*	This function sets the tree root and all its	*
*	right subtree root to be a NewOp node, used	*
*	only in construct a Procedure or function call	*
*	subtree with arguments				*
*	Added by Hui-Jung Chang	, Oct.30, 1992		*
********************************************************/	
void SetRightTreeOp(T, Op)
tree T;
int Op;
{
tree 	p;

	p = T;
   	do
	  {
		SetNodeOp(p, Op);
		p = RightChild(p);
	  }
	while ( !IsNull(p));
}


/****************************************************************
* 	This function sets the LeftChild of T to be NewC	*
****************************************************************/
void SetLeftChild(T, NewC)
tree T, NewC;
{
      if (NodeKind(T) != EXPRNode) 
		printf("SetLeftChild(): This node must be an EXPRNode!\n");
	else
		T->LeftC = NewC;
}
	
/****************************************************************
* 	This function sets the RightChild of T to be NewC	*
****************************************************************/
void SetRightChild(T, NewC)
tree T, NewC;
{
      if (NodeKind(T) != EXPRNode) 
		printf("SetRightChild(): This node must be an EXPRNode!\n");
	else
		T->RightC = NewC;
}

/*****************************************************************/
/*	This is syntax tree printer, "treelst" is the output file
	pointer.

   	call printtree with the root node pointer and the depth level
	(could be 0 if you do not want the root to be indent)

   	writing "getname()" and "getstring()" is your responsibility
	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 */


extern FILE *treelst;

char *opnodenames [] =
   {
    "ProgramOp", "BodyOp", "DeclOp", "CommaOp", "ArrayTypeOp", "TypeIdOp",
    "BoundOp", "RecompOp",
    "ToOp", "DownToOp", "ConstantIdOp", "ProceOp", "FuncOp",
    "HeadOp", "RArgTypeOp", "VargTypeOp", "StmtOp", "IfElseOp",
    "LoopOp", "SpecOp", "RoutineCallOp", "AssignOp", "ReturnOp", 
    "AddOp", "SubOp", "MultOp", "DivOp",
    "LTOp", "GTOp", "EQOp", "NEOp", "LEOp", "GEOp", "AndOp", "OrOp", 
    "UnaryNegOp", "NotOp", "VarOp", "SelectOp", "IndexOp", "FieldOp",
    "SubrangeOp", "ExitOp", "ClassOp", "MethodOp", "ClassDefOp"
  };

static int crosses [162];

void indent (x)
 int x;
{
  register i; 

  for (i = 0; i < x; i++)
  {
    fprintf (treelst,"%s", crosses [i]? "| " : "  ");
  }
  fprintf (treelst,"%s", x ? "+-" : "R-");
  if (x)
    crosses [x] = (crosses [x] + 1) % 2;
}

void zerocrosses ()
{
  register i;
  for (i = 0; i < 162; i++)
    crosses [i] = 0;
}

extern char* strg_tbl;

char* getname(int i)/*return ID name or String, i is the index of the string table, passed through yylval*/
{
  return( strg_tbl+i );/*return string table indexed at i*/
}

char* getstring(int i)
{
  return( strg_tbl+i );/*return string table indexed at i*/
}


void printtree (nd, depth)
  tree nd;
  int depth;
{
  int id, indx;

  if (!depth)
  {
    zerocrosses ();
    fprintf (treelst,"************* SYNTAX TREE PRINTOUT ***********\n\n");
  }
  if (IsNull (nd))
  {
    indent (depth);
    fprintf (treelst,"[DUMMYnode]\n");
    return;
  }
  if (NodeKind (nd) == EXPRNode)
    printtree (RightChild (nd), depth + 1);
  indent (depth); 
  switch (NodeKind (nd))
  {
    case IDNode:    
		    indx = IntVal(nd);
		    if (indx >= 0)
		    {
		      id = indx; /*GetAttr(indx, NAME_ATTR); */
		      fprintf (treelst,"[IDNode,%d,\"%s\"]\n", IntVal(nd),
                                                    getname(id));
		    }
		    else 
		      fprintf (treelst,"[IDNode,%d,\"%s\"]\n", indx, "err");
		    break;

    case STNode:
                    indx = IntVal(nd);
                    if (indx > 0)
                    {
                      id = indx; /* GetAttr(indx, NAME_ATTR); */
                      fprintf (treelst,"[STNode,%d,\"%s\"]\n", IntVal(nd),
                                                    getname(id));
                    }
                    else 
                      fprintf (treelst,"[IDNode,%d,\"%s\"]\n", indx, "err");
                    break;

    case INTEGERTNode:
                      fprintf (treelst,"[INTEGERTNode]\n");
                    break;

    case NUMNode:   fprintf (treelst,"[NUMNode,%d]\n", IntVal (nd));
		    break;

    case CHARNode:  if (isprint (IntVal (nd)))
		      fprintf (treelst,"[CHARNode,%d,\'%c\']\n",
					 IntVal (nd), IntVal (nd));
		    else
		      fprintf (treelst,"[CHARNode,%d,\'\\%o\']\n",
					 IntVal (nd), IntVal (nd));
		    break;

    case STRINGNode:fprintf (treelst,"[STRINGNode,%d,\"%s\"]\n", IntVal (nd),
							getstring(IntVal(nd)));
		    break;

    case EXPRNode:  fprintf (treelst,"[%s]\n", 
					opnodenames [NodeOp(nd) - ProgramOp]);
		    break;

    default:	    fprintf (treelst,"INVALID!!!\n");
		    break;
  }
  if (NodeKind (nd) == EXPRNode)
    printtree (LeftChild (nd), depth + 1);
}

tree maintain_leaf_table(int NodeKind, int IntVal)
{
    if (leaf_table_size == 0)
    {
        leaf_table_size = strg_tbl_size;
        leaf_table = (tree*)malloc(strg_tbl_size * sizeof(tree));
    }
    else if (leaf_table_size < strg_tbl_size)
    {
        leaf_table_size = strg_tbl_size;
        leaf_table = (tree*)realloc(leaf_table, leaf_table_size * sizeof(tree));
    }
    if (leaf_table == NULL)
    {
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
        return NullExp();
    }
    if (leaf_table[IntVal] == NULL)
    {
        leaf_table[IntVal] = MakeLeaf(NodeKind, IntVal);
    }
    return leaf_table[IntVal];
}

tree IntegerT()
{
    return &integer;
}

void ATO_stack_push(int ATO)
{
    if (ATO_stack_size == 0)
    {
        ATO_stack_back = -1;
        ATO_stack_size = 1;
        ATO_stack = (int*)malloc(sizeof(int));
    }
    else if (ATO_stack_size < ATO_stack_back + 2)
    {
        ATO_stack_size *= 2;
        ATO_stack = (int*)realloc(ATO_stack, ATO_stack_size * sizeof(int));
    }
    if (ATO_stack == NULL)
    {
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
        return;
    }
    ATO_stack[++ATO_stack_back] = ATO;
}
