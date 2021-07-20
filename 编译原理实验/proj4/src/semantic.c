#include "proj2.h"
#include "proj3.h"

int nSymInd_var;
TypeDim traverseExpression(tree node);
TypeDim traverseVariable(tree node)
{
    if ((nSymInd_var = convert_ID_to_ST(&node->LeftC, VAR_MODE, 0)) == 0)
    {
        return MakeTypeDim(IntegerT(), 0);
    }
    TypeDim type_dim = MakeTypeDim(GetAttr(nSymInd_var, TYPE_ATTR), GetAttr(nSymInd_var, DIMEN_ATTR));
    tree p = node->RightC;
    while (p != NullExp())
    {
        if (p->LeftC->NodeOpType == IndexOp)
        {
            /* IndexOps "[]" can be only applied to arrays. */
            if (GetAttr(nSymInd_var, KIND_ATTR) != ARR)
            {
                error_msg(TYPE_MIS, CONTINUE, GetAttr(nSymInd_var, NAME_ATTR), 0);
                type_dim.dim = -1;
                return type_dim;
            }
            /* The number of indices is larger than the dimmension of arrays. */
            if (type_dim.dim <= 0)
            {
                error_msg(INDX_MIS, CONTINUE, GetAttr(nSymInd_var, NAME_ATTR), 0);
                type_dim.dim = -1;
                return type_dim;
            }
            TypeDim type_dim_idx = traverseExpression(p->LeftC->LeftC);
            /* Only integers can work as indices. */
            if (type_dim_idx.type != IntegerT() || type_dim_idx.dim != 0)
            {
                error_msg(OP_MIS, CONTINUE, IndexOp, 0);
            }
            type_dim.dim--;
        }
        /* FieldOps "." can't be applied to arrays. */
        else if (type_dim.dim != 0)
        {
            error_msg(TYPE_MIS, CONTINUE, GetAttr(nSymInd_var, NAME_ATTR), 0);
            type_dim.dim = -1;
            return type_dim;
        }
        /* The FieldOp is applied to a class. */
        else if (GetAttr(nSymInd_var, KIND_ATTR) == CLASS)
        {
            if ((nSymInd_var = convert_ID_to_ST(&p->LeftC->LeftC, FIELD_MODE, nSymInd_var)) == 0)
            {
                type_dim.dim = -1;
                return type_dim;
            }
            type_dim.type = GetAttr(nSymInd_var, TYPE_ATTR);
            type_dim.dim = GetAttr(nSymInd_var, DIMEN_ATTR);
        }
        /* The FieldOp is applied to a variable. */
        else
        {
            if (((tree)GetAttr(nSymInd_var, TYPE_ATTR))->LeftC == IntegerT()
                    || (nSymInd_var = convert_ID_to_ST(&p->LeftC->LeftC, FIELD_MODE, ((tree)GetAttr(nSymInd_var, TYPE_ATTR))->IntVal)) == 0)
            {
                type_dim.dim = -1;
                return type_dim;
            }
            type_dim.type = GetAttr(nSymInd_var, TYPE_ATTR);
            type_dim.dim = GetAttr(nSymInd_var, DIMEN_ATTR);
        }
        p = p->RightC;
    }
    return type_dim;
}

TypeDim traverseMethodCallStatement(tree node, tree call_kind);
TypeDim traverseFactor(tree node)
{
    switch (node->NodeKind)
    {
        case NUMNode: return MakeTypeDim(IntegerT(), 0);
        case STRINGNode: return MakeTypeDim(StringT(), 0);
    }
    TypeDim type_dim;
    switch (node->NodeOpType)
    {
        case VarOp: return traverseVariable(node);
        case RoutineCallOp: return traverseMethodCallStatement(node, FUNC);
        case NotOp:
                            type_dim = traverseFactor(node->LeftC);
                            /* NotOps can be only applied to integers. */
                            if (type_dim.type != IntegerT() || type_dim.dim != 0)
                            {
                                error_msg(OP_MIS, CONTINUE, NotOp, 0);
                            }
                            return MakeTypeDim(IntegerT(), 0);
    }
    return traverseExpression(node);
}

TypeDim traverseTerm(tree node)
{
    if (node->NodeOpType == MultOp
            || node->NodeOpType == DivOp
            || node->NodeOpType == AndOp)
    {
        TypeDim type_dim_left = traverseTerm(node->LeftC);
        TypeDim type_dim_right = traverseFactor(node->RightC);
        /* MultOps, DivOps and AndOps can be only applied to integers. */
        if (type_dim_left.type != IntegerT() || type_dim_left.dim != 0
                || type_dim_right.type != IntegerT() || type_dim_right.dim != 0)
        {
            error_msg(OP_MIS, CONTINUE, node->NodeOpType, 0);
            return MakeTypeDim(IntegerT(), 0);
        }
        return type_dim_left;
    }
    return traverseFactor(node);
}

TypeDim traverseSimpleExpression(tree node)
{
    if (node->NodeOpType == UnaryNegOp)
    {
        TypeDim type_dim = traverseSimpleExpression(node->LeftC);
        /* UnaryNegOps can be only applied to integers. */
        if (type_dim.type != IntegerT() || type_dim.dim != 0)
        {
            error_msg(OP_MIS, CONTINUE, UnaryNegOp, 0);
        }
        return MakeTypeDim(IntegerT(), 0);
    }
    if (node->NodeOpType == AddOp
            || node->NodeOpType == SubOp
            || node->NodeOpType == OrOp)
    {
        TypeDim type_dim_left = traverseSimpleExpression(node->LeftC);
        TypeDim type_dim_right = traverseTerm(node->RightC);
        /* AddOps, SubOps and OrOps can be only applied to integers. */
        if (type_dim_left.type != IntegerT() || type_dim_left.dim != 0
                || type_dim_right.type != IntegerT() || type_dim_right.dim != 0)
        {
            error_msg(OP_MIS, CONTINUE, node->NodeOpType, 0);
        }
        return MakeTypeDim(IntegerT(), 0);
    }
    return traverseTerm(node);
}

TypeDim traverseExpression(tree node)
{
    /* EQOps and NEOps can be applied to all types. */
    if (node->NodeOpType == EQOp || node->NodeOpType == NEOp)
    {
        traverseSimpleExpression(node->LeftC);
        traverseSimpleExpression(node->RightC);
        return MakeTypeDim(IntegerT(), 0);
    }
    if (node->NodeOpType == LTOp
            || node->NodeOpType == LEOp
            || node->NodeOpType == GEOp
            || node->NodeOpType == GTOp)
    {
        TypeDim type_dim_left = traverseSimpleExpression(node->LeftC);
        TypeDim type_dim_right = traverseSimpleExpression(node->RightC);
        /* LTOps, LEOps, GEOps and GTOps can be only applied to integers. */
        if (type_dim_left.type != IntegerT() || type_dim_left.dim != 0
                || type_dim_right.type != IntegerT() || type_dim_right.dim != 0)
        {
            error_msg(OP_MIS, CONTINUE, node->NodeOpType, 0);
            return MakeTypeDim(IntegerT(), 0);
        }
        return type_dim_left;
    }
    return traverseSimpleExpression(node);
}

void traverseWhileStatement(tree node)
{
    TypeDim type_dim = traverseExpression(node->LeftC);
    /* LoopOp can be only applied to integers. */
    if (type_dim.type != IntegerT() || type_dim.dim != 0)
    {
        error_msg(OP_MIS, CONTINUE, LoopOp, 0);
    }
    traverseStatementList(node->RightC);
}

void traverseIfStatement(tree node)
{
    if (node->LeftC != NullExp())
    {
        traverseIfStatement(node->LeftC);
    }
    if (node->RightC->NodeOpType == CommaOp)
    {
        TypeDim type_dim = traverseExpression(node->RightC->LeftC);
        /* IfElseOp can be only applied to integers. */
        if (type_dim.type != IntegerT() || type_dim.dim != 0)
        {
            error_msg(OP_MIS, CONTINUE, IfElseOp, 0);
        }
        traverseStatementList(node->RightC->RightC);
    }
    else
    {
        traverseStatementList(node->RightC);
    }
}

int nSymInd_method;
void traverseReturnStatement(tree node)
{
    tree type = GetAttr(nSymInd_method, TYPE_ATTR);
    int dim = GetAttr(nSymInd_method, DIMEN_ATTR);
    /* Types of return value must be void in procedures. */
    if (node->LeftC == NullExp() && type != NullExp()
            || (node->LeftC != NullExp() && type == NullExp()))
    {
        error_msg(RET_MIS, CONTINUE, GetAttr(nSymInd_method, NAME_ATTR), 0);
    }
    else
    {
        TypeDim type_dim_right = traverseExpression(node->LeftC);
        /* The type of return value must match the type of function. */
        if (type != type_dim_right.type || dim != type_dim_right.dim)
        {
            error_msg(RET_MIS, CONTINUE, GetAttr(nSymInd_method, NAME_ATTR), 0);
        }
    }
}

TypeDim traverseMethodCallStatement(tree node, tree kind)
{
    TypeDim type_dim = traverseVariable(node->LeftC);
    if (type_dim.dim == -1)
    {
        return type_dim;
    }
    int nSymInd = nSymInd_var;
    int var_kind = GetAttr(nSymInd, KIND_ATTR);
    /* Only functions and procedures can be called. */
    if (type_dim.dim != 0 || (var_kind != FUNC && var_kind != PROCE) || (var_kind == PROCE && kind == FUNC))
    {
        error_msg(kind == PROCE ? PROCE_MISMATCH : FUNC_MISMATCH, CONTINUE, GetAttr(nSymInd, NAME_ATTR), 0);
    }
    tree p = node->RightC;
    for (int i = 0; i < GetAttr(nSymInd, ARGNUM_ATTR); ++i)
    {
        /* The number of arguments is less than the number of parameters. */
        if (p == NullExp())
        {
            error_msg(ARGUMENTS_NUM2, CONTINUE, GetAttr(nSymInd, NAME_ATTR), 0);
            break;
        }
        TypeDim type_dim_arg = traverseExpression(p->LeftC);
        if (!GetAttr(nSymInd, PREDE_ATTR))
        {
            /* The type of arguments is different from the type of parameters. */
            if (type_dim_arg.dim != 0 || type_dim_arg.type != GetAttr(nSymInd + 1 + i, TYPE_ATTR))
            {
                error_msg(ARG_MIS, CONTINUE, GetAttr(nSymInd, NAME_ATTR), i);
            }
            /* The parameter is a reference parameter, so the argument must be a variable. */
            if (GetAttr(nSymInd + 1 + i, KIND_ATTR) == REF_ARG && p->LeftC->NodeOpType != VarOp)
            {
                error_msg(p->LeftC->NodeKind == EXPRNode ? EXPR_VAR : CONSTANT_VAR, CONTINUE, GetAttr(nSymInd, NAME_ATTR), i);
            }
        }
        p = p->RightC;
    }
    /* The number of arguments is larger than the number of parameters. */
    if (p != NullExp())
    {
        error_msg(ARGUMENTS_NUM2, CONTINUE, GetAttr(nSymInd, NAME_ATTR), 0);
    }
    return type_dim;
}

void traverseAssignmentStatement(tree node)
{
    TypeDim type_dim_left = traverseVariable(node->LeftC->RightC);
    TypeDim type_dim_right = traverseExpression(node->RightC);
    if (type_dim_left.dim != -1 && type_dim_right.dim != -1)
    {
        /* The type of the lvalue doesn't match the type of the rvalue. */
        if (type_dim_left.type != type_dim_right.type)
        {
            error_msg(STRING_ASSIGN, CONTINUE, GetAttr(node->LeftC->RightC->LeftC->IntVal, NAME_ATTR), 0);
        }
        /* The dimension of the lvalue doesn't match the dimension of the rvalue. */
        else if (type_dim_left.dim != type_dim_right.dim)
        {
            error_msg(INDX_MIS, CONTINUE, GetAttr(node->LeftC->RightC->LeftC->IntVal, NAME_ATTR), 0);
        }
    }
}

void traverseStatementList(tree node)
{
    if (node->LeftC != NullExp())
    {
        traverseStatementList(node->LeftC);
    }
    switch (node->RightC->NodeOpType)
    {
        case AssignOp: traverseAssignmentStatement(node->RightC); break;
        case RoutineCallOp: traverseMethodCallStatement(node->RightC, PROCE); break;
        case ReturnOp: traverseReturnStatement(node->RightC); break;
        case IfElseOp: traverseIfStatement(node->RightC); break;
        case LoopOp: traverseWhileStatement(node->RightC);
    }
}

int traverseType(tree node)
{
    int dim = 0;
    int nSymInd;
    if (node->LeftC == IntegerT() || (nSymInd = convert_ID_to_ST(&node->LeftC, VAR_MODE, 0)) != 0)
    {
        tree p = node->RightC;
        while (p != NullExp())
        {
            /* FiledOps in type trees are meaningless. */
            if (p->NodeOpType == FieldOp)
            {
                error_msg(REC_TYPE_MIS, CONTINUE, GetAttr(nSymInd, NAME_ATTR), 0);
                break;
            }
            p = p->RightC;
            ++dim;
        }
    }
    return dim;
}

TypeDim traverseArrayCreationExpression_LeftC(tree node)
{
    TypeDim type_dim = MakeTypeDim(IntegerT(), 0);
    if (node->LeftC != NullExp())
    {
        type_dim.dim = traverseArrayCreationExpression_LeftC(node->LeftC).dim;
    }
    TypeDim type_dim_expr = traverseExpression(node->RightC);
    /* Only integers can work as indices. */
    if (type_dim_expr.type != IntegerT() || type_dim_expr.dim != 0)
    {
        error_msg(OP_MIS, CONTINUE, IndexOp, 0);
    }
    ++type_dim.dim;
    return type_dim;
}

TypeDim traverseVariableInitializer(tree node);
TypeDim traverseArrayInitializer_LeftC(tree node, tree type)
{
    if (node->LeftC == NullExp())
    {
        TypeDim type_dim = traverseVariableInitializer(node->RightC);
        type_dim.dim += type_dim.dim != -1;
        return type_dim;
    }
    TypeDim type_dim = traverseArrayInitializer_LeftC(node->LeftC, type);
    if (type_dim.dim != -1)
    {
        TypeDim type_dim_elem = traverseVariableInitializer(node->RightC);
        if (type_dim.type == type_dim_elem.type && type_dim.dim == type_dim_elem.dim + 1)
        {
            return type_dim;
        }
    }
    type_dim.dim = -1;
    return type_dim;
}

TypeDim traverseVariableInitializer(tree node)
{
    if (node->NodeOpType == ArrayTypeOp)
    {
        if (node->RightC->NodeOpType == TypeIdOp)
        {
            return traverseArrayInitializer_LeftC(node->LeftC, node->RightC->LeftC);
        }
        return traverseArrayCreationExpression_LeftC(node->LeftC);
    }
    return traverseExpression(node);
}

void traverseFieldDecl(tree node)
{
    if (!IsNull(node->LeftC))
    {
        traverseFieldDecl(node->LeftC);
    }
    int nSymInd;
    if ((nSymInd = convert_ID_to_ST(&node->RightC->LeftC, DECL_MODE, 0)) != 0)
    {
        tree type_tree = node->RightC->RightC->LeftC;
        int dim = traverseType(type_tree);
        SetAttr(nSymInd, TYPE_ATTR, type_tree->LeftC);
        if (node->RightC->RightC->RightC != NullExp())
        {
            TypeDim type_dim = traverseVariableInitializer(node->RightC->RightC->RightC);
            /* The type of the lvalue doesn't match the type of the rvalue. */
            if (type_dim.type != type_tree->LeftC || type_dim.dim != dim)
            {
                error_msg(STRING_ASSIGN, CONTINUE, GetAttr(nSymInd, NAME_ATTR), 0);
            }
        }
        if (dim == 0)
        {
            SetAttr(nSymInd, KIND_ATTR, VAR);
        }
        else
        {
            SetAttr(nSymInd, KIND_ATTR, ARR);
            SetAttr(nSymInd, DIMEN_ATTR, dim);
        }
    }
}

void traverseDecls(tree node)
{
    if (!IsNull(node->LeftC))
    {
        traverseDecls(node->LeftC);
    }
    traverseFieldDecl(node->RightC);
}

int traverseFormalParameterList(tree node)
{
    if (node == NullExp())
    {
        return 0;
    }
    int nSymInd;
    if ((nSymInd = convert_ID_to_ST(&node->LeftC->LeftC, DECL_MODE, 0)) != 0)
    {
        SetAttr(nSymInd, KIND_ATTR, node->NodeOpType == RArgTypeOp ? REF_ARG : VALUE_ARG);
        SetAttr(nSymInd, TYPE_ATTR, node->LeftC->RightC);
    }
    return traverseFormalParameterList(node->RightC) + 1;
}

int is_main = false;
extern char* strg_tbl;
void traverseMethodDecl(tree node)
{
    int nSymInd;
    if (strcmp(strg_tbl + node->LeftC->LeftC->IntVal, "main") == 0)
    {
        /* main method must be declared once. */
        if (is_main)
        {
            error_msg(MULTI_MAIN, CONTINUE, 0, 0);
            return;
        }
        else
        {
            is_main = true;
        }
    }
    if ((nSymInd = convert_ID_to_ST(&node->LeftC->LeftC, DECL_MODE, 0)) != 0)
    {
        tree type_tree = node->LeftC->RightC->RightC;
        if (type_tree == NullExp())
        {
            SetAttr(nSymInd, KIND_ATTR, PROCE);
        }
        else
        {
            SetAttr(nSymInd, KIND_ATTR, FUNC);
            int dim = traverseType(type_tree);
            SetAttr(nSymInd, TYPE_ATTR, type_tree->LeftC);
            if (dim != 0)
            {
                SetAttr(nSymInd, DIMEN_ATTR, dim);
            }
        }
        nSymInd_method = nSymInd;
        OpenBlock();
        SetAttr(nSymInd, ARGNUM_ATTR, traverseFormalParameterList(node->LeftC->RightC->LeftC));
        if (node->RightC->LeftC != NullExp())
        {
            traverseDecls(node->RightC->LeftC);
        }
        traverseStatementList(node->RightC->RightC);
        SetAttr(nSymInd, TREE_ATTR, node);
        CloseBlock();
    }
}

void traverseClassBody(tree node)
{
    if (node->RightC->NodeOpType == DeclOp)
    {
        traverseDecls(node);
        return;
    }
    if (!IsNull(node->LeftC))
    {
        traverseClassBody(node->LeftC);
    }
    if (node->RightC != NullExp())
    {
        traverseMethodDecl(node->RightC);
    }
}

void traverseClassDecl(tree node)
{
    int nSymInd;
    if ((nSymInd = convert_ID_to_ST(&node->RightC, DECL_MODE, 0)) != 0)
    {
        SetAttr(nSymInd, KIND_ATTR, CLASS);
        if (!IsNull(node->LeftC))
        {
            OpenBlock();
            traverseClassBody(node->LeftC);
            CloseBlock();
        }
    }
}

void traverseProgram_LeftC(tree node)
{
    if (!IsNull(node->LeftC))
    {
        traverseProgram_LeftC(node->LeftC);
    }
    traverseClassDecl(node->RightC);
}

void do_semantic(tree parseTree)
{
    STInit();           	                 // Initialize the symbol table
    traverseProgram_LeftC(parseTree->LeftC); // Traverse tree
    free(parseTree->RightC);
    parseTree->RightC = NullExp();
    /* main method must be declared once. */
    if (!is_main)
    {
        error_msg(NO_MAIN, CONTINUE, 0, 0);
    }
}
