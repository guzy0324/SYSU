%{ /* definition */
#include "proj2.h"
#include <stdio.h>
%}

%token <intg> ANDnum ASSGNnum DECLARATIONSnum DOTnum ENDDECLARATIONSnum EQUALnum GTnum IDnum INTnum LBRACnum LPARENnum METHODnum NEnum ORnum PROGRAMnum RBRACnum RPARENnum SEMInum VALnum WHILEnum CLASSnum COMMAnum DIVIDEnum ELSEnum EQnum GEnum ICONSTnum IFnum LBRACEnum LEnum LTnum MINUSnum NOTnum PLUSnum RBRACEnum RETURNnum SCONSTnum TIMESnum VOIDnum

%type <tptr> Program ProgramSuffix ClassDecl ClassBody ClassBodyInfix Decls DeclsInfix FieldDecl FieldType FieldDeclInfix VariableDeclId VariableInitializer ArrayInitializer ArrayInitializerInfix ArrayCreationExpression ArrayCreationExpressionSuffix MethodDecl FormalParameterList FormalParameterListSuffix RefOrVal Block Type TypeSuffix StatementList StatementListInfix Statement AssignmentStatement MethodCallStatement MethodCallStatementInfix ReturnStatement IfStatement IfStatementPreffix WhileStatement Expression SimpleExpression Term Factor UnsignedConstant Variable VariableSuffix Indices


%% /* yacc specification */
Program : PROGRAMnum IDnum SEMInum ProgramSuffix
        {
            $$ = MakeTree(ProgramOp, $4, maintain_leaf_table(IDNode, $2));
            printtree($$, 0);
        }
        ;

ProgramSuffix : ClassDecl
              { $$ = MakeTree(ClassOp, NullExp(), $1); }
              | ProgramSuffix ClassDecl
              { $$ = MakeTree(ClassOp, $1, $2); }
              ;

ClassDecl : CLASSnum IDnum ClassBody
          { $$ = MakeTree(ClassDefOp, $3, maintain_leaf_table(IDNode, $2)); }
          ;

ClassBody : LBRACEnum Decls RBRACEnum
          { $$ = MakeTree(BodyOp, $2, NullExp()); }
          | LBRACEnum ClassBodyInfix RBRACEnum
          { $$ = $2; }
          ;

ClassBodyInfix : /* empty */
               { $$ = NullExp(); }
               | Decls MethodDecl
               { $$ = MakeTree(BodyOp, $1, $2); }
               | ClassBodyInfix MethodDecl
               { $$ = MakeTree(BodyOp, $1, $2); }
               ;

Decls : DECLARATIONSnum DeclsInfix ENDDECLARATIONSnum
      { $$ = $2; }
      ;

DeclsInfix : /* empty */
           { $$ = NullExp(); }
           | DeclsInfix FieldDecl
           { $$ = MakeTree(BodyOp, $1, $2); }
           ;

FieldDecl : FieldType FieldDeclInfix SEMInum
          { $$ = $2; }
          ;

FieldType : Type
          { FieldTypeGlobal = $1; }
          ;

FieldDeclInfix : VariableDeclId
               { $$ = MakeTree(DeclOp, NullExp(), MakeTree(CommaOp, $1, MakeTree(CommaOp, FieldTypeGlobal, NullExp()))); }
               | FieldDeclInfix COMMAnum VariableDeclId
               { $$ = MakeTree(DeclOp, $1, MakeTree(CommaOp, $3, MakeTree(CommaOp, FieldTypeGlobal, NullExp()))); }
               | VariableDeclId EQUALnum VariableInitializer
               { $$ = MakeTree(DeclOp, NullExp(), MakeTree(CommaOp, $1, MakeTree(CommaOp, FieldTypeGlobal, $3))); }
               | FieldDeclInfix COMMAnum VariableDeclId EQUALnum VariableInitializer
               { $$ = MakeTree(DeclOp, $1, MakeTree(CommaOp, $3, MakeTree(CommaOp, FieldTypeGlobal, $5))); }
               ;

VariableDeclId : IDnum
               { $$ = maintain_leaf_table(IDNode, $1); }
               | VariableDeclId LBRACnum RBRACnum
               { $$ = $1; }
               ;

VariableInitializer : Expression
                    { $$ = $1; }
                    | ArrayInitializer
                    { $$ = $1; }
                    | ArrayCreationExpression
                    { $$ = $1; }
                    ;

ArrayInitializer : LBRACEnum ArrayInitializerInfix RBRACEnum
                 { $$ = MakeTree(ArrayTypeOp, $2, FieldTypeGlobal); }
                 ;

ArrayInitializerInfix : VariableInitializer
                      { $$ = MakeTree(CommaOp, NullExp(), $1); }
                      | ArrayInitializerInfix COMMAnum VariableInitializer
                      { $$ = MakeTree(CommaOp, $1, $3); }
                      ;

ArrayCreationExpression : INTnum ArrayCreationExpressionSuffix
                        { $$ = MakeTree(ArrayTypeOp, $2, IntegerT()); }
                        ;

ArrayCreationExpressionSuffix : LBRACnum Expression RBRACnum
                              { $$ = MakeTree(BoundOp, NullExp(), $2); }
                              | ArrayCreationExpressionSuffix LBRACnum Expression RBRACnum
                              { $$ = MakeTree(BoundOp, $1, $3); }
                              ;

MethodDecl : METHODnum Type IDnum LPARENnum RPARENnum Block
           { $$ = MakeTree(MethodOp, MakeTree(HeadOp, maintain_leaf_table(IDNode, $3), MakeTree(SpecOp, NullExp(), $2)), $6); }
           | METHODnum VOIDnum IDnum LPARENnum RPARENnum Block
           { $$ = MakeTree(MethodOp, MakeTree(HeadOp, maintain_leaf_table(IDNode, $3), MakeTree(SpecOp, NullExp(), NullExp())), $6); }
           | METHODnum Type IDnum LPARENnum FormalParameterList RPARENnum Block
           { $$ = MakeTree(MethodOp, MakeTree(HeadOp, maintain_leaf_table(IDNode, $3), MakeTree(SpecOp, $5, $2)), $7); }
           | METHODnum VOIDnum IDnum LPARENnum FormalParameterList RPARENnum Block
           { $$ = MakeTree(MethodOp, MakeTree(HeadOp, maintain_leaf_table(IDNode, $3), MakeTree(SpecOp, $5, NullExp())), $7); }
           ;

FormalParameterList : RefOrVal INTnum IDnum FormalParameterListSuffix
                    { $$ = MakeTree(ATO_stack[ATO_stack_back--], MakeTree(CommaOp, maintain_leaf_table(IDNode, $3), IntegerT()), $4); }
                    ;

FormalParameterListSuffix : /* empty */
                          { $$ = NullExp(); }
                          | COMMAnum IDnum FormalParameterListSuffix
                          { $$ = MakeTree(ATO_stack[ATO_stack_back], MakeTree(CommaOp, maintain_leaf_table(IDNode, $2), IntegerT()), $3); }
                          | SEMInum RefOrVal INTnum IDnum FormalParameterListSuffix
                          { $$ = MakeTree(ATO_stack[ATO_stack_back--], MakeTree(CommaOp, maintain_leaf_table(IDNode, $4), IntegerT()), $5); }
                          ;

RefOrVal : /* empty */
         { ATO_stack_push(RArgTypeOp); }
         | VALnum
         { ATO_stack_push(VArgTypeOp); }
         ;

Block : StatementList
      { $$ = MakeTree(BodyOp, NullExp(), $1); }
      | Decls StatementList
      { $$ = MakeTree(BodyOp, $1, $2); }
      ;

Type : IDnum TypeSuffix
     { $$ = MakeTree(TypeIdOp, maintain_leaf_table(IDNode, $1), $2); }
     | INTnum TypeSuffix
     { $$ = MakeTree(TypeIdOp, IntegerT(), $2); }
     ;

TypeSuffix : /* empty */
           { $$ = NullExp(); }
           | LBRACnum RBRACnum TypeSuffix 
           { $$ = MakeTree(IndexOp, NullExp(), $3); }
           | DOTnum Type
           { $$ = MakeTree(FieldOp, $2, NullExp()); }
           ;

/* If there're other actual statements in the list, dummy statements won't be assigned a StmtOp.
At least 1 StmtOp is in the list. */
StatementList : LBRACEnum StatementListInfix RBRACEnum
              {
                  if (IsNull($2))
                  {
                      $$ = MakeTree(StmtOp, $2, $2);
                  }
                  else
                  {
                      $$ = $2;
                  }
              }
              ;

StatementListInfix : Statement
                   {
                       if (IsNull($1))
                       {
                           $$ = $1;
                       }
                       else
                       {
                           $$ = MakeTree(StmtOp, NullExp(), $1);
                       }
                   }
                   | StatementListInfix SEMInum Statement
                   {
                       if (IsNull($3))
                       {
                           $$ = $1;
                       }
                       else
                       {
                           $$ = MakeTree(StmtOp, $1, $3);
                       }
                   }
                   ;

Statement : AssignmentStatement
          { $$ = $1; }
          | MethodCallStatement
          { $$ = $1; }
          | ReturnStatement
          { $$ = $1; }
          | IfStatement
          { $$ = $1; }
          | WhileStatement
          { $$ = $1; }
          | /* empty */
          { $$ = NullExp(); }
          ;

AssignmentStatement : Variable ASSGNnum Expression
                    { $$ = MakeTree(AssignOp, MakeTree(AssignOp, NullExp(), $1), $3); }
                    ;

MethodCallStatement : Variable LPARENnum RPARENnum
                    { $$ = MakeTree(RoutineCallOp, $1, NullExp()); }
                    | Variable LPARENnum MethodCallStatementInfix RPARENnum
                    { $$ = MakeTree(RoutineCallOp, $1, $3); }
                    ;

MethodCallStatementInfix : Expression
                         { $$ = MakeTree(CommaOp, $1, NullExp()); }
                         | Expression COMMAnum MethodCallStatementInfix
                         { $$ = MakeTree(CommaOp, $1, $3); }
                         ;

ReturnStatement : RETURNnum
                { $$ = MakeTree(ReturnOp, NullExp(), NullExp()); }
                | RETURNnum Expression
                { $$ = MakeTree(ReturnOp, $2, NullExp()); }
                ;

IfStatement : IfStatementPreffix
            { $$ = $1; }
            | IfStatementPreffix ELSEnum StatementList
            { $$ = MakeTree(IfElseOp, $1, $3); }
            ;

IfStatementPreffix : IFnum Expression StatementList
                   { $$ = MakeTree(IfElseOp, NullExp(), MakeTree(CommaOp, $2, $3)); }
                   | IfStatementPreffix ELSEnum IFnum Expression StatementList
                   { $$ = MakeTree(IfElseOp, $1, MakeTree(CommaOp, $4, $5)); }
                   ;

WhileStatement : WHILEnum Expression StatementList
               { $$ = MakeTree(LoopOp, $2, $3); }
               ;

Expression : SimpleExpression
           | SimpleExpression LTnum SimpleExpression
           { $$ = MakeTree(LTOp, $1, $3); }
           | SimpleExpression LEnum SimpleExpression
           { $$ = MakeTree(LEOp, $1, $3); }
           | SimpleExpression EQnum SimpleExpression
           { $$ = MakeTree(EQOp, $1, $3); }
           | SimpleExpression NEnum SimpleExpression
           { $$ = MakeTree(NEOp, $1, $3); }
           | SimpleExpression GEnum SimpleExpression
           { $$ = MakeTree(GEOp, $1, $3); }
           | SimpleExpression GTnum SimpleExpression
           { $$ = MakeTree(GTOp, $1, $3); }
           ;

SimpleExpression : Term
                 { $$ = $1; }
                 | PLUSnum Term
                 { $$ = $2; }
                 | MINUSnum Term
                 { $$ = MakeTree(UnaryNegOp, $2, NullExp()); }
                 | SimpleExpression PLUSnum Term
                 { $$ = MakeTree(AddOp, $1, $3); }
                 | SimpleExpression MINUSnum Term
                 { $$ = MakeTree(SubOp, $1, $3); }
                 | SimpleExpression ORnum Term
                 { $$ = MakeTree(OrOp, $1, $3); }
                 ;

Term : Factor
     { $$ = $1; }
     | Term TIMESnum Factor
     { $$ = MakeTree(MultOp, $1, $3); }
     | Term DIVIDEnum Factor
     { $$ = MakeTree(DivOp, $1, $3); }
     | Term ANDnum Factor
     { $$ = MakeTree(AndOp, $1, $3); }
     ;

Factor : UnsignedConstant
       { $$ = $1; }
       | Variable
       { $$ = $1; }
       | MethodCallStatement
       { $$ = $1; }
       | LPARENnum Expression RPARENnum
       { $$ = $2; }
       | NOTnum Factor
       { $$ = MakeTree(NotOp, $2, NullExp()); }
       ;

UnsignedConstant : ICONSTnum
                 { $$ = MakeLeaf(NUMNode, $1); }
                 | SCONSTnum
                 { $$ = maintain_leaf_table(STRINGNode, $1); }
                 ;

Variable : IDnum VariableSuffix
         { $$ = MakeTree(VarOp, maintain_leaf_table(IDNode, $1), $2); }
         ;

VariableSuffix : /* empty */
               { $$ = NullExp(); }
               | LBRACnum Indices RBRACnum VariableSuffix
               { $$ = MakeTree(SelectOp, $2, $4); }
               | DOTnum IDnum VariableSuffix
               { $$ = MakeTree(SelectOp, MakeTree(FieldOp, maintain_leaf_table(IDNode, $2), NullExp()), $3); }
               ;

Indices : Expression
        { $$ = MakeTree(IndexOp, $1, NullExp()); }
        | Expression COMMAnum Indices
        { $$ = MakeTree(IndexOp, $1, $3); }
        ;

%%
// int yycolumn, yyline;
FILE *treelst;

main() {
   treelst = stdout;
   yyparse();
}

/* The parser will cease and call this function when syntax error or memory error occurs, while lexer won't cease when error arises. */
yyerror(char *str) { printf("%s at line %d column %d\n", str, yyline, yycolumn); }
