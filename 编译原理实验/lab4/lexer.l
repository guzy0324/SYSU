%{
    # define YYSTYPE double 
    # include "y.tab.h"
    extern double yylval;
%}
number [0-9]+\.?|[0-9]*\.[0-9]+

%%

[  ] {
    /* skip blanks */
}
{number} {
    double temp;
    sscanf(yytext, "%lf", &yylval);
    return NUMBER;
}
\n|. {
    return yytext[0];
}

%%

int yywrap(void)
{
    return 1;
}
