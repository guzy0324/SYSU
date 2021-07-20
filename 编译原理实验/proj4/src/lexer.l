%{
#include "proj2.h"
#include "y.tab.h"
// #include "token.h"
#define INIT_LINE 1
#define INIT_COLUMN 1


/* TODO: declare variables here */
int yyline = INIT_LINE, yycolumn = INIT_COLUMN;

/* String table is an array that is similar to a vector in C++.
If the size of the array is not big enough to accommodate the new text,
it will be allocated twice the current space. */
char* strg_tbl;

/* strg_tbl_length is the actually used space's size. */
int strg_tbl_length = 0;

/* strg_tbl_size is the total memory allocated to the string table. */
int strg_tbl_size = 0;

/* Maintaining processes decribed above are excuted in maintain_strg_tbl.
If the allocation is unsuccessful the function will return 0.
Otherwise, it will return 1. */
int maintain_strg_tbl(int leng);

/* Index table contains the indices of frist characters of unique strings in string table.
It is also an array resembling a vector. */
int* index_table;

/* index_table_length is the actually used space's size. */
int index_table_length = 0;

/* index_table_size is the total memory allocated to index table. */
int index_table_size = 0;

/* maintain_index_table finds a string in string table that is the same as the new text.
If the function finds the index, it will return the index's location in index table.
Otherwise, it may reallocate the space.
If the allocation is not successful, the function will return -1.
Otherwise, it will return index_table_length. */
int loc_index(int leng, char* text);
int maintain_index_table(int leng, char* text);
%}

/* TODO: define regular expressions */
COMMENT             (\/\*([^\*]|\*[^\/])*\*\/)
SCONST   			('(\\n|\\t|\\'|\\\\|[^\n\t'\\])*')
INVALIDSTR          ('[^\n']*)
INVALIDCMT          (\/\*([^\*]|\*[^\/])*)
AND   				(&&)
ASSGN   			(:=)
DOT   				(\.)
ENDDECLARATIONS   	(enddeclarations)
INT   				(int)
LBRAC   			(\[)
LPAREN   			(\()
METHOD   			(method)
NE   				(!=)
OR   				(\|\|)
PROGRAM   			(program)
RBRAC   			(\])
RPAREN   			(\))
SEMI   				(;)
VAL   				(val)
WHILE   			(while)
CLASS   			(class)
COMMA   			(,)
DIVIDE   			(\/)
ELSE   				(else)
EQ   				(==)
GE   				(>=)
IF   				(if)
LBRACE   			(\{)
LE   				(<=)
MINUS   			(-)
PLUS   				(\+)
RBRACE   			(\})
RETURN   			(return)
TIMES   			(\*)
VOID   				(void)
DECLARATIONS   		(declarations)
EQUAL   			(=)
GT   				(>)
LT   				(<)
NOT   				(!)
/* ID_OR_ICONST matches ID, invalid ID and ICONST. */
ID_OR_ICONST        ([a-zA-Z0-9]+)
WHITESPACE          ([ \n\t])
OTHERS              (.)

/* TODO: define translation rules: pattern and action */
%%
{COMMENT} {
    for (int i = 0; i < yyleng; i++)
    {
        if (yytext[i] == '\n')
        {
            yycolumn = INIT_COLUMN;
            yyline++;
        }
        else
        {
            yycolumn++;
        }
    }
    // return (COMMENTnum);
}

{SCONST} {
    yycolumn += yyleng;
    int leng = 0;
    char* text = (char*)malloc((yyleng - 2) * sizeof(char));
    if (text == NULL)
    {
        // return (MALLOCERRnum);
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
        return (SCONSTnum);
    }
    for (int i = 1; i < yyleng - 1; i++)
    {
        if (yytext[i] == '\\')
        {
            switch (yytext[++i])
            {
                case 'n': text[leng++] = '\n'; break;
                case 't': text[leng++] = '\t'; break;
                case '\'': text[leng++] = '\''; break;
                default: text[leng++] = '\\';
            }
        }
        else
        {
            text[leng++] = yytext[i];
        }
    }
    if (!maintain_strg_tbl(leng))
    {
        // return (MALLOCERRnum);
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
        goto RET;
    }
    int index_i = maintain_index_table(leng, text);
    if (index_i >= index_table_length)
    {
        index_table[index_table_length++] = strg_tbl_length;
        for (int i = 0; i < leng; i++)
        {
            strg_tbl[strg_tbl_length++] = text[i];
        }
        strg_tbl[strg_tbl_length++] = '\0';
    }
    if (index_i == -1)
    {
        // return (MALLOCERRnum);
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
    }
    else
    {
        yylval.intg = index_table[index_i];
    }
RET:
    free(text);
    return (SCONSTnum);
}

{INVALIDSTR} {
    for (int i = 0; i < yyleng; i++)
    {
        switch (yytext[i])
        {
            case '\n': yycolumn = INIT_COLUMN; yyline++; break;
            case '\t': yycolumn += 4; break;
            default: yycolumn++;
        }
    }
    // return (INVALIDSTRnum);
    printf("Lexical error: invalid SCONST at line %d, column %d.\n", yyline, yycolumn);
    return (SCONSTnum);
}

{INVALIDCMT} {
    for (int i = 0; i < yyleng; i++)
    {
        switch (yytext[i])
        {
            case '\n': yycolumn = INIT_COLUMN; yyline++; break;
            case '\t': yycolumn += 4; break;
            default: yycolumn++;
        }
    }
    printf("Lexical error: invalid comment at line %d, column %d.\n", yyline, yycolumn);
    // return (INVALIDCMTnum);
}

{AND} {
    yycolumn += 2;
    return (ANDnum);
}

{ASSGN} {
    yycolumn += 2;
    return (ASSGNnum);
}

{DOT} {
    yycolumn++;
    return (DOTnum);
}

{ENDDECLARATIONS} {
    yycolumn += 15;
    return (ENDDECLARATIONSnum);
}

{INT} {
    yycolumn += 3;
    return (INTnum);
}

{LBRAC} {
    yycolumn++;
    return (LBRACnum);
}

{LPAREN} {
    yycolumn++;
    return (LPARENnum);
}

{METHOD} {
    yycolumn += 6;
    return (METHODnum);
}

{NE} {
    yycolumn += 2;
    return (NEnum);
}

{OR} {
    yycolumn += 2;
    return (ORnum);
}

{PROGRAM} {
    yycolumn += 7;
    return (PROGRAMnum);
}

{RBRAC} {
    yycolumn++;
    return (RBRACnum);
}

{RPAREN} {
    yycolumn++;
    return (RPARENnum);
}

{SEMI} {
    yycolumn++;
    return (SEMInum);
}

{VAL} {
    yycolumn += 3;
    return (VALnum);
}

{WHILE} {
    yycolumn += 5;
    return (WHILEnum);
}

{CLASS} {
    yycolumn += 5;
    return (CLASSnum);
}

{COMMA} {
    yycolumn++;
    return (COMMAnum);
}

{DIVIDE} {
    yycolumn++;
    return (DIVIDEnum);
}

{ELSE} {
    yycolumn += 4;
    return (ELSEnum);
}

{EQ} {
    yycolumn += 2;
    return (EQnum);
}

{GE} {
    yycolumn += 2;
    return (GEnum);
}

{IF} {
    yycolumn += 2;
    return (IFnum);
}

{LBRACE} {
    yycolumn++;
    return (LBRACEnum);
}

{LE} {
    yycolumn += 2;
    return (LEnum);
}

{MINUS} {
    yycolumn++;
    return (MINUSnum);
}

{PLUS} {
    yycolumn++;
    return (PLUSnum);
}

{RBRACE} {
    yycolumn++;
    return (RBRACEnum);
}

{RETURN} {
    yycolumn += 6;
    return (RETURNnum);
}

{TIMES} {
    yycolumn++;
    return (TIMESnum);
}

{VOID} {
    yycolumn += 4;
    return (VOIDnum);
}

{DECLARATIONS} {
    yycolumn += 12;
    return (DECLARATIONSnum);
}

{EQUAL} {
    yycolumn++;
    return (EQUALnum);
}

{GT} {
    yycolumn++;
    return (GTnum);
}

{LT} {
    yycolumn++;
    return (LTnum);
}

{NOT} {
    yycolumn++;
    return (NOTnum);
}

{ID_OR_ICONST} {
    yycolumn += yyleng;
    if (!maintain_strg_tbl(yyleng))
    {
        // return (MALLOCERRnum);
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
        return (IDnum);
    }
    int type = '0' <= yytext[0] && yytext[0] <= '9' ? 1 : 0;
    for (int i = 0; i < yyleng; i++)
    {
        if (type && !('0' <= yytext[i] && yytext[i] <= '9'))
        {
            type = -1;
        }
    }
    switch (type)
    {
        case -1: // return (INVALIDIDnum);
        printf("Lexical error: invalid identifier at line %d, column %d.\n", yyline, yycolumn);
        return (IDnum);
        case 1:
        yylval.intg = atoi(yytext);
        return (ICONSTnum);
    }
    int index_i = maintain_index_table(yyleng, yytext);
    if (index_i >= index_table_length)
    {
        index_table[index_table_length++] = strg_tbl_length;
        for (int i = 0; i < yyleng; i++)
        {
            strg_tbl[strg_tbl_length++] = yytext[i];
        }
        strg_tbl[strg_tbl_length++] = '\0';
    }
    if (index_i == -1)
    {
        // return (MALLOCERRnum);
        printf("Memory allocation error at line %d, column %d.\n", yyline, yycolumn);
    }
    else
    {
        yylval.intg = index_table[index_i];
    }
    return (IDnum);
}

<<EOF>> {
    // return (EOFnum);
    return 0;
}

{WHITESPACE} {
    switch (yytext[0])
    {
        case '\n': yycolumn = INIT_COLUMN; yyline++; break;
        // case '\t': yycolumn += 4; break;
        default: yycolumn++;
    }
    // return (WHITESPACEnum);
}

{OTHERS} {
    yycolumn++;
    // return (OTHERSnum);
    printf("Lexical error: unrecognized character at line %d, column %d.\n", yyline, yycolumn);
}

%%

/* TODO: define the auxiliary functions you may use */
int yywrap()
{
    return 1;
}

int maintain_strg_tbl(int leng)
{
    if (strg_tbl_size == 0)
    {
        strg_tbl_size = 1;
        strg_tbl = (char*)malloc(sizeof(char));
    }
    else if (strg_tbl_size < strg_tbl_length + leng + 1)
    {
        while (strg_tbl_size < strg_tbl_length + leng + 1)
        {
            strg_tbl_size *= 2;
        }
        strg_tbl = (char*)realloc(strg_tbl, strg_tbl_size * sizeof(char));
    }
    if (strg_tbl == NULL)
    {
        return 0;
    }
    return 1;
}

int loc_index(int leng, char* text)
{
    int i, j;
    for (i = 0; i < index_table_length; i++)
    {
        if ((i + 1 < index_table_length ? index_table[i + 1] : strg_tbl_length) - index_table[i] == leng + 1)
        {
            for (j = 0; j < leng; j++)
            {
                if (strg_tbl[index_table[i] + j] != text[j])
                {
                    break;
                }
            }
            if (j == leng)
            {
                break;
            }
        }
    }
    return i;
}

int maintain_index_table(int leng, char* text)
{
    int i = loc_index(leng, text);
    if (i == index_table_length)
    {
        if (index_table_size == 0)
        {
            index_table_size = 1;
            index_table = (int*)malloc(sizeof(int));
        }
        else if (index_table_size < index_table_length + 1)
        {
            index_table_size *= 2;
            index_table = (int*)realloc(index_table, index_table_size * sizeof(int));
        }
        if (index_table == NULL)
        {
            return -1;
        }
    }
    return i;
}
