%{
    #include <ctype.h>
    #include <stdio.h>
    #define YYSTYPE double /* double type for Yacc stack */
%}
%token NUMBER

/* associativity */
%right '+' '-'
%right '*' '/'

%%

/* LHS:RHS; */
lines : lines expr '\n' { printf("= %g\n", $2); }
      | lines '\n'
      | /* empty */
      ;
expr : expr '+' expr { $$ = $1 + $3; }
     | expr '-' expr { $$ = $1 - $3; }
     | expr '*' expr { $$ = $1 * $3; }
     | expr '/' expr { $$ = $1 / $3; }
     | '(' expr ')' { $$ = $2; }
     | NUMBER
     ;

%%

/*
int yylex() {
    int c;
    while ((c = getchar()) == ' ');
    if ((c == '.') || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }
    return c;
}
*/

int main() {
    if (yyparse() != 0)
        fprintf(stderr, "Abnormal exit\n");
    return 0;
}

int yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
}
