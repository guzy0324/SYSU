/* %A%
 * TO USE THIS MODULE YOU HAVE TO DEFINE:
 * =====================================
 *
 * FILE *table   \
 * getstring()    }  as for proj2.c
 * getname()     / 
 *
 * 
 * void 
 * error_msg(error_type, proc_instr, id);
 *   int error_type, proc_instr, id;
 * {
 *    Report an error, the type of which is given by 'error_type'
 *    (see the defined error_type below). 
 *
 *    If 'id' is not zero it is the unique identifying number of the 
 *    identifier for which the error as to be reported.
 *
 *    Proceed according to 'proc_instr' (ABORT / CONTINUE, see below in
 *    the define section).
 * }
 *
 * 
 * AND TO INSERT THE ADEQUATE CODE:
 * ===============================
 *
 * - in STInit() 
 *
 * - in STPrint()  (lines 453 and 457)
 * 
 */


/*
 * there are three arrays for symbol table operation.  "st" is the real
 * symbol table, it carries all the information of an id and will still be
 * used in code generation phase.  The attributes for an id are kept in a
 * linked list pointed by its symbol table entry. It is easy to be extended in
 * the next phase to include more attributes, such like the size and the
 * location of a variable. Below are some sample attributes of an id.  You
 * should design your own. "stack" is a temporary structure in which all the
 * id's in the current scoping context are visible.  "attrarray" is to store
 * all the attributes in symbol table. 
 */

   #include "proj2.h"
   #include "proj3.h" 
   /* #include "token.h" */
   #include <ctype.h>
   #include <stdio.h> 
   #include <stdlib.h> 


/*********************************data structures**********************/

/*
 * !!!!!!!!! WARNING !!!!!!!!!! all the data structures and variables defined
 * below are private to the symbol table operating routines. Do NOT use them
 * directly unless you really understand the whole symbol table structure. 
 */

/*
 * symbol table array 
 */
int st[ST_SIZE];

/*
 * attribute array.  attributes are allocated from this array instead of from
 * dynamically allocated space.  It may easy testing and debugging. 
 */
attr_type attrarray[ATTR_SIZE];

/*
 * global counters 
 */
int stack_top = 0;	     /* stack top counter */
int st_top = 0;		     /* symbol table top counter */
int nesting = 0;	     /* nesting level counter */
int attr_top = 0;	     /* attribute array counter */

extern int yyline;
extern char strg_tbl[];      /* string table in table.c */
char* getstring(int i);
char* getname(int i);        /*return ID name or String, i is the index of the string table, passed through yylval*/

/************************ routines *****************************/


/*
 * STInit():  initialize the symbol table.  put predefined names into it and
 * build trees for those names. this routine is incomplete, please fill in
 * the details 
 */
void
STInit()
{
  int nStrInd, nSymInd;  /* string table index */

  nStrInd = loc_str("system"); /* return string index of string "system" */
  if ( nStrInd != -1 )         /* "system" is stored in string table */
    {
      nSymInd = InsertEntry(nStrInd);
      /* SetAttr(nSymInd, TREE_ATTR, NULL); */
      SetAttr(nSymInd, PREDE_ATTR, true);
      SetAttr(nSymInd, KIND_ATTR, CLASS);

      OpenBlock();

      nStrInd = loc_str("readln");
      if ( nStrInd != -1 )
      {
          nSymInd = InsertEntry(nStrInd);
          // SetAttr(nSymInd, NEST_ATTR, nesting+1);
          SetAttr(nSymInd, ARGNUM_ATTR, 1);
          /* SetAttr(nSymInd, TREE_ATTR, NULL); */
          SetAttr(nSymInd, PREDE_ATTR, true);
          SetAttr(nSymInd, KIND_ATTR, PROCE);
      }

      nStrInd = loc_str("println");
      if ( nStrInd != -1 )
      {
          nSymInd = InsertEntry(nStrInd);
          // SetAttr(nSymInd, NEST_ATTR, nesting+1);
          SetAttr(nSymInd, ARGNUM_ATTR, 1);
          /* SetAttr(nSymInd, TREE_ATTR, NULL); */
          SetAttr(nSymInd, PREDE_ATTR, true);
          SetAttr(nSymInd, KIND_ATTR, PROCE);
      }

      CloseBlock();
    }
}


void error_msg(type, action, id, seq)
int type, action, id, seq;
{
  printf("Semantic Error--line: %d, ", yyline);
  switch (type)
  {
    case STACK_OVERFLOW:
	printf("stack overflow.\n");
	break;
    case REDECLARATION:
	printf("symbol %s: redeclared.\n", getname(id));
	break;
    case ST_OVERFLOW:
	printf("symbol table overflow.\n");
	break;
    case UNDECLARATION:
	printf("symbol %s: undeclared.\n", getname(id));
	break;
    case ATTR_OVERFLOW:
	printf("attribute array overflowed.\n");
	break;
    case BOUND:
	printf("symbol %s: not declared as a constant, can't be used as subrange bound.\n", getname(id));
	break;
    case ARGUMENTS_NUM1:
	printf("routine %s: argument number in definition is different with the previous forward declaration. \n", getname(id));
	break;
    case ARGUMENTS_NUM2:
	printf("routine %s: argument number is different with the previous declaration. \n", getname(id));
	break;
    case FORW_REDECLARE:
	printf("routine %s: forward redeclaration.\n", getname(id));
	break; 
    case PROCE_MISMATCH: 
	printf("symbol %s: can't act as a procedure call.\n", getname(id)); 
	break;
     case FUNC_MISMATCH:
        printf("symbol %s: can't act as a function call.\n", getname(id));
        break;
    case VAR_VAL:
	printf("routine %s: reference/value type of the ", getname(id));
	printf("%s parameter different with previous forward declaration.\n", seq_str(seq));
	break;
    case CONSTANT_VAR:
	printf("routine %s: the ", getname(id));
	printf("%s parameter is a reference argument, can't be a constant.\n", seq_str(seq));
	break;
    case EXPR_VAR:
	printf("routine %s: reference argument of the ", getname(id));
	printf("%s parameter can't be a expression. \n", seq_str(seq));	
	break;
    case CONSTANT_ASSIGN:
	printf("symbol %s: declared to be a constant, can't be assigned a new value.\n", getname(id));
	break;
    case STRING_ASSIGN:
	printf("symbol %s: declared to be an int, can't be assigned a string.\n", getname(id));
	break;
    case ARR_TYPE_MIS:
	if (seq == 0)
	  printf("symbol %s: isn't defined as an array.\n", getname(id));
	else
	{
	  printf("symbol %s: the ", getname(id));
	  printf("%s index isn't defined as an array.\n", seq_str(seq));
	}
	break;
  case ARR_DIME_MIS:
    printf("symbol %s: inappropriate usage of arry element.\n", getname(id));
    break;
    case REC_TYPE_MIS:
          printf("symbol %s: illegal usage of a field name. \n", getname(id));
	break;
    case INDX_MIS:
      printf("symbol %s: has incorrect number of dimensions.\n", getname(id));
      /*printf("%s index has incorrect number of dimensions.\n", seq_str(seq));*/
	break;
    case FIELD_MIS:
	printf("symbol %s: is an undeclared field name.\n", getname(id));
	break;
    case VARIABLE_MIS:
	printf("symbol %s: can't be used as a variable.\n", getname(id));
	break;
    case NOT_TYPE:
        printf("symbol %s: is not declared as a type.\n", getname(id));
        break;
    case TYPE_MIS:
	printf("symbol %s: incorrect type usage.\n", getname(id));
    break;

  case MULTI_MAIN:
    printf("main() method already declared.\n");
    break;

  case NO_MAIN:
    printf("main() method not declared.\n");
    break;

  case OP_MIS:
    printf("operator %d: can't be applied to the type.\n", id);
    break;

  case ARG_MIS:
	printf("routine %s: argument type of the ", getname(id));
	printf("%s parameter different with the previous declaration.\n", seq_str(seq));
    break;

  case RET_MIS:
    printf("symbol %s: method and return value types are mismatched.\n", getname(id));
    break;

    default:
	printf("error type: %d.\n", type);
  }
  if (action == ABORT)
    exit(0);
}

/*
 * InsertEntry():  builds a symbol table entry for id.  the current block is
 * searched for redeclaration error.  the id's name  and nesting level
 * attributes are set by this function.  writing error_msg routine is your
 * work. 
 */
int
InsertEntry(id)
  int id;
{
  /* id is already declared in the current block */
  if (LookUpHere(id))
  {
    error_msg(REDECLARATION, CONTINUE, id, 0);
    return (0);
  }

  if (st_top >= ST_SIZE-1)
    error_msg(ST_OVERFLOW, ABORT, 0 ,0);

  st_top++;
  st[st_top] = 0;
  SetAttr(st_top, NAME_ATTR, id);
  SetAttr(st_top, NEST_ATTR, nesting);
  Push(false, id, st_top, false);
  return (st_top);
}

/*
 * LookUp(): search an id in the stack and return the symbol table entry
 * pointer, if found.  if the id is not in the stack, report error and push a
 * dummy item on the stack so that the same error will not be reported
 * repeatedly 
 */
int
LookUp(id)
  int id;
{
  int i;

  for (i = stack_top; i > 0; i--)
    if (!stack[i].marker && stack[i].name == id)
    {
      stack[i].used = true;
      return (stack[i].st_ptr);
    }

  /* id is undefined, push a dummy element onto stack */
  error_msg(UNDECLARATION, CONTINUE, id, 0);
  Push(false, id, 0, true);
  return 0;
}

/*
 * LookUpHere():  search an id in the stack for the current block.  It
 * returns the symbol table pointer if the id is found.  otherwise, return 0
 * this routine can be used to check if there is a forward declaration
 * for a procedure/function
 */
int
LookUpHere(id)
  int id;
{
  int i;

  for (i = stack_top; !stack[i].marker; i--)
    if (stack[i].name == id && !stack[i].dummy)
      return (stack[i].st_ptr);
  return (0);
}

/*
 * LookUpField(): Return the symbol table entry of record field id. St_ptr
 * indicates where the search starts in the symbol table. Return NullST if none.
 */

int
LookUpField(st_ptr, id)
  int st_ptr;
  int id;
{
  int nesting=GetAttr(st_ptr, NEST_ATTR);
  int i/*, nest*/;
  for(i=st_ptr+1; i<=st_top; i++)
  {
    if(GetAttr(i, NEST_ATTR) <= nesting)
      break;
    if(GetAttr(i, NAME_ATTR) == id)
      return i;
  }
  return (0);
}

/*
 * OpenBlock():  build a mark on the stack to indecate the beginning of a new
 * block. increment nesting level counter.  It is called when reserved words
 * "program", "procedure", "function" or "record" is encountered.  Note:
 * procedure or function name should be inserted into symbol table before
 * calling this routine. 
 */
void
OpenBlock()
{
  nesting++;
  Push(true, 0, 0, false);		 /* push a marker onto stack */
}

/*
 * CloseBlock():  decrement nesting level counter and remove the current
 * block from the stack.  called when exitting from a program, procedure,
 * function or a record definition. each element is checked to see if it is
 * used in the block 
 */
void
CloseBlock()
{
  int i;

  for (i = stack_top; !stack[i].marker; i--)
    if (!stack[i].used && !stack[i].dummy)
    {
      /* error_msg(NOT_USED, CONTINUE, stack[i].name, 0);*/
    }

  nesting--;
  stack_top = i - 1;				 /* trim the stack */
}

/*
 * IsAttr(): return the index to the searched attribute in attrarray if it is
 * in (nonzero).  otherwise, return false. 
 */
int
IsAttr(st_ptr, attr_num)
  int st_ptr, attr_num;

{
  int i;

  i = st[st_ptr];
  while (i)
  {
    if (attrarray[i].attr_num == attr_num)
      return (i);
    if (attrarray[i].attr_num > attr_num)
      break;
    i = attrarray[i].next_attr;
  }
  return (0);
}

/*
 * GetAttr(): return the specified attribute value for a symbol table entry
 * if found.  otherwise, report error.  Note, this error is not the fault of
 * source program but of the compiler writer.  It is printed for testing and
 * debugging. 
 */
uintptr_t
GetAttr(st_ptr, attr_num)
  int st_ptr, attr_num;

{
  int i;

  i = IsAttr(st_ptr, attr_num);
  if (!i)
  {
/*
    printf("DEBUG--The wanted attribute number %d does not exist, id: %s\n", attr_num, getname(GetAttr(st_ptr, NAME_ATTR)));
*/
    // printf("DEBUG--The wanted attribute number %d does not exist\n", attr_num);
    return (0);
  }

  return (attrarray[i].attr_val);
}

/*
 * SetAttr(): set attribute.  if the attribute is already there,  print
 * debugging message. attributes for a symbol table entry are sorted by their
 * attr_num.  
 */
void
SetAttr(st_ptr, attr_num, attr_val)
  int st_ptr, attr_num;
  uintptr_t attr_val;

{
  int *p, next;
  int i;
  if ((i = IsAttr(st_ptr, attr_num)))
  {
/*
    printf("DEBUG--The attribute number %d to be added already exists\n",
            attr_num);
*/
    attrarray[i].attr_val = attr_val;
    return;
  }

  p = &st[st_ptr];
  next = st[st_ptr];

  /* search the link list for the right insert position */
  while (next)
  {
    if (attrarray[next].attr_num < attr_num)
    {
      p = &(attrarray[next].next_attr);
      next = attrarray[next].next_attr;
    }
    else
      break;
  }

  if (attr_top >= ATTR_SIZE-1)
    error_msg(ATTR_OVERFLOW, ABORT,0, 0);

  attr_top++;
  attrarray[attr_top].attr_num = attr_num;
  attrarray[attr_top].attr_val = attr_val;
  attrarray[attr_top].next_attr = next;
  *p = attr_top;
}


extern FILE *table;

char *kind_name[] =
{"constant", "variable","funcforw", "function", "ref_arg", "val_arg", "field",
 "typedef", "procforw",  "procedure", "class", "array"
};

/*
 * STPrint():  print symbol table.  This routine is incomplete, please fill
 * in details. 
 */
void
STPrint()
{
  FILE *table;
  int i, attr_num, attr_ptr/*, type_attr*/;
  uintptr_t attr_val;
  int treeval = 0;
  tree ptrTree;

  table = stdout;
  fprintf(table,
	  "********************************Symbol Table************************************\n\n");
  fprintf(table,
	  "          Name Nest-Level  Tree-Node Predefined        Kind      Type      Value     Offset  Dimension     Argnum\n\n");

  for (i = 1; i <= st_top; i++)
  {
    treeval = 0;
    fprintf(table, "%3d", i);
    for (attr_num = NAME_ATTR; attr_num <= ARGNUM_ATTR; attr_num++)
      if ((attr_ptr = IsAttr(i, attr_num)))
      {
	attr_val = attrarray[attr_ptr].attr_val;
	switch (attr_num)
        {
	case NAME_ATTR:
	   fprintf(table, "%11s", getname(attr_val));
	  break;
	case OFFSET_ATTR:
	case NEST_ATTR:
	  fprintf(table, "%11lu", attr_val);
	  break;
	case TREE_ATTR:
	  fprintf(table, "%11s", "proc-tree");
	  break;
	case TYPE_ATTR:
	  treeval = attr_val;
	  fprintf(table, "%11s", "type-tree");
	  break;
	case PREDE_ATTR:
	  if (attr_val == true)
	    fprintf(table, "%11s", "yes");
	  else 
	    fprintf(table, "%11s", "no");
	  break;
	case KIND_ATTR:
	  fprintf(table, "%11s", kind_name[attr_val - 1]);
	  break;
	case VALUE_ATTR:
	  if (GetAttr(i, KIND_ATTR) == CONST)
	    {
	      ptrTree = (tree)attr_val;
	      switch (NodeKind(ptrTree))
		{
		case NUMNode:
		  fprintf(table, "%11d", IntVal(ptrTree));
		  break;
		case CHARNode:
		  if (isprint(IntVal(ptrTree)))
		    fprintf(table, "%11c", IntVal(ptrTree));
		  break;
		case STRINGNode:
		  fprintf(table, "%11s", getstring(IntVal(ptrTree)));
		  break;
		}
	    }
	  break;
	case DIMEN_ATTR:
	  fprintf(table, "%11lu",attr_val);
	  break;
        case ARGNUM_ATTR:
	  fprintf(table, "%11lu",attr_val);
          break;
        }
      }
      else
	fprintf(table, "%11s", " ");
    fprintf(table, "\n");
    /* if (treeval!=0)
       printtree((tree)treeval, 0);*/
  }
}


/*
 * Push():  push an element onto the stack.  
 */
void
Push(marker, name, st_ptr, dummy)
     int marker,name,st_ptr,dummy;
{

  if (stack_top >= STACK_SIZE-1)
    error_msg(STACK_OVERFLOW, ABORT,0, 0);

  stack_top++;

  stack[stack_top].marker = (bool) marker;
  stack[stack_top].name = name;
  stack[stack_top].st_ptr = st_ptr;
  stack[stack_top].dummy = (bool) dummy;
  stack[stack_top].used = false;

}

char *seq_str(seq)
int seq;
{
  static char s[10];
  switch (seq)
  {
    case 0:
	return("0th");
    case 1:
	return("1st");
    case 2:
	return("2nd");
    case 3:
	return("3rd");
    default:
	sprintf(s, "%dth", seq);
	return(s);
  }
}

int convert_ID_to_ST(tree* node_p, int mode, int st_ptr)
{
    int nSymInd, nStrInd;
    nStrInd = (*node_p)->IntVal;
    switch (mode)
    {
        case DECL_MODE: nSymInd = InsertEntry(nStrInd); break;
        case VAR_MODE: nSymInd = LookUp(nStrInd); break;
        default:
            if ((nSymInd = LookUpField(st_ptr, nStrInd)) == 0)
            {
                error_msg(FIELD_MIS, CONTINUE, nStrInd, 0);
            }
    }
    if (nSymInd != 0)
    {
        if (STNode_table[nSymInd] == NULL)
        {
            STNode_table[nSymInd] = MakeLeaf(STNode, nSymInd);
        }
        *node_p = STNode_table[nSymInd];
        leaf_table[nStrInd + 1] = (int)leaf_table[nStrInd + 1] - 1;
        if ((int)leaf_table[nStrInd + 1] == 0)
        {
            free(leaf_table[nStrInd]);
        }
    }
    return nSymInd;
}

TypeDim MakeTypeDim(tree type, int dim)
{
    TypeDim type_dim;
    type_dim.type = type;
    type_dim.dim = dim;
    return type_dim;
}
