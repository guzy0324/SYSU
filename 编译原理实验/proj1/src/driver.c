#include "token.h"
#include <stdio.h>
#include <stdlib.h>

/* TODO: handle the tokens, and output the result */

// yylex() is in lex.yy.c
extern int yylex(), yyleng, yyline, yycolumn, yylval, string_table_length;
extern char* string_table;

int main (int argc, char* argv[]) {
    int lexRtn = -1;			// return value of yylex

	/* recognize each token type */
    puts("Line            Column          Token           Index in String table");
	while (1) {
		lexRtn = yylex();
		switch (lexRtn) {
            case ANDnum:
            {
                printf("%-16d%-16dAND\n", yyline, yycolumn);
                break;
            }

            case ASSGNnum:
            {
                printf("%-16d%-16dASSGN\n", yyline, yycolumn);
                break;
            }

            case DECLARATIONSnum:
            {
                printf("%-16d%-16dDECLARATIONS\n", yyline, yycolumn);
                break;
            }

            case DOTnum:
            {
                printf("%-16d%-16dDOT\n", yyline, yycolumn);
                break;
            }

            case ENDDECLARATIONSnum:
            {
                printf("%-16d%-16dENDDECLARATIONS\n", yyline, yycolumn);
                break;
            }

            case EQUALnum:
            {
                printf("%-16d%-16dEQUAL\n", yyline, yycolumn);
                break;
            }

            case GTnum:
            {
                printf("%-16d%-16dGT\n", yyline, yycolumn);
                break;
            }

            case IDnum:
            {
                printf("%-16d%-16dID              %-16d\n", yyline, yycolumn, yylval);
                break;
            }

            case INTnum:
            {
                printf("%-16d%-16dINT\n", yyline, yycolumn);
                break;
            }

            case LBRACnum:
            {
                printf("%-16d%-16dLBRAC\n", yyline, yycolumn);
                break;
            }

            case LPARENnum:
            {
                printf("%-16d%-16dLPAREN\n", yyline, yycolumn);
                break;
            }

            case METHODnum:
            {
                printf("%-16d%-16dMETHOD\n", yyline, yycolumn);
                break;
            }

            case NEnum:
            {
                printf("%-16d%-16dNE\n", yyline, yycolumn);
                break;
            }

            case ORnum:
            {
                printf("%-16d%-16dOR\n", yyline, yycolumn);
                break;
            }

            case PROGRAMnum:
            {
                printf("%-16d%-16dPROGRAM\n", yyline, yycolumn);
                break;
            }

            case RBRACnum:
            {
                printf("%-16d%-16dRBRAC\n", yyline, yycolumn);
                break;
            }

            case RPARENnum:
            {
                printf("%-16d%-16dRPAREN\n", yyline, yycolumn);
                break;
            }

            case SEMInum:
            {
                printf("%-16d%-16dSEMI\n", yyline, yycolumn);
                break;
            }

            case VALnum:
            {
                printf("%-16d%-16dVAL\n", yyline, yycolumn);
                break;
            }

            case WHILEnum:
            {
                printf("%-16d%-16dWHILE\n", yyline, yycolumn);
                break;
            }

            case CLASSnum:
            {
                printf("%-16d%-16dCLASS\n", yyline, yycolumn);
                break;
            }

            case COMMAnum:
            {
                printf("%-16d%-16dCOMMA\n", yyline, yycolumn);
                break;
            }

            case DIVIDEnum:
            {
                printf("%-16d%-16dDIVIDE\n", yyline, yycolumn);
                break;
            }

            case ELSEnum:
            {
                printf("%-16d%-16dELSE\n", yyline, yycolumn);
                break;
            }

            case EQnum:
            {
                printf("%-16d%-16dEQ\n", yyline, yycolumn);
                break;
            }

            case GEnum:
            {
                printf("%-16d%-16dGE\n", yyline, yycolumn);
                break;
            }

            case ICONSTnum:
            {
                printf("%-16d%-16dICONST\n", yyline, yycolumn);
                break;
            }

            case IFnum:
            {
                printf("%-16d%-16dIF\n", yyline, yycolumn);
                break;
            }

            case LBRACEnum:
            {
                printf("%-16d%-16dLBRACE\n", yyline, yycolumn);
                break;
            }

            case LEnum:
            {
                printf("%-16d%-16dLE\n", yyline, yycolumn);
                break;
            }

            case LTnum:
            {
                printf("%-16d%-16dLT\n", yyline, yycolumn);
                break;
            }

            case MINUSnum:
            {
                printf("%-16d%-16dMINUS\n", yyline, yycolumn);
                break;
            }

            case NOTnum:
            {
                printf("%-16d%-16dNOT\n", yyline, yycolumn);
                break;
            }

            case PLUSnum:
            {
                printf("%-16d%-16dPLUS\n", yyline, yycolumn);
                break;
            }

            case RBRACEnum:
            {
                printf("%-16d%-16dRBRACE\n", yyline, yycolumn);
                break;
            }

            case RETURNnum:
            {
                printf("%-16d%-16dRETURN\n", yyline, yycolumn);
                break;
            }

            case SCONSTnum:
            {
                printf("%-16d%-16dSCONST          %-16d\n", yyline, yycolumn, yylval);
                break;
            }

            case TIMESnum:
            {
                printf("%-16d%-16dTIMES\n", yyline, yycolumn);
                break;
            }

            case VOIDnum:
            {
                printf("%-16d%-16dVOID\n", yyline, yycolumn);
                break;
            }

            case EOFnum:
            {
                printf("%-16d%-16dEOF\n", yyline, yycolumn);
                break;
            }

            case COMMENTnum:
            {
                // printf("%-16d%-16dCOMMENT\n", yyline, yycolumn);
                break;
            }

            case MALLOCERRnum:
            {
                printf("%-16d%-16dMALLOCERR\n", yyline, yycolumn);
                break;
            }

            case INVALIDSTRnum:
            {
                printf("%-16d%-16dINVALIDSTR\n", yyline, yycolumn);
                break;
            }

            case INVALIDCMTnum:
            {
                printf("%-16d%-16dINVALIDCMT\n", yyline, yycolumn);
                break;
            }

            case INVALIDIDnum:
            {
                printf("%-16d%-16dINVALIDID\n", yyline, yycolumn);
                break;
            }

            case WHITESPACEnum:
            {
                break;
            }

            case OTHERSnum:
            {
                printf("%-16d%-16dOTHERS\n", yyline, yycolumn);
                break;
            }
		}

		if (lexRtn == EOFnum) break;
	}

    printf("\nString Table:\n");
    for (int i = 0; i < string_table_length; i++)
    {
        putchar(string_table[i]);
    }
    putchar('\n');

	return 0;
}
