/* Declarations: include, extern, variables, patterns, etc. */

%{
    int yyline = 0, yyid = 0;
%}

/* Pattern format: <name> <definition> */

letter      [a-zA-Z]
digit       [0-9]
id          {letter}({letter}|{digit})*
id_error    {digit}({letter}|{digit})*
newline     \n

/* Translation rules: pattern {Action}
    - Patter: a RE, which may use the regular definitions in declaratinos
    - Action: fragments of code, typically written in C */

/* Lex Variables
    - yytext: Of type char* it contains the lexeme currently found
    - - Lexeme is a sequence of chars in the input stream that matches some pattern in the Rules section
    - yyleng: Of type int and it stores the length of lexeme pointed by yytext */

%%
{id}        {
                yyid++;
                printf("\nid: %s (len=%d)", yytext, yyleng);
            }
{id_error}  {
                printf("\nwrong id: %s (len=%d)", yytext, yyleng);
            }
{newline}   {
                yyline++;
            }
%%

/* Auxiliary functions: additional user-defined functinos */

/* Lex Functions
    - yylex(): Scans through the input looking for a matching pattern */

int main()
{
    yylex();
    printf("\n\n%d lines in total ...\n", yyline);
    return 0;
}
