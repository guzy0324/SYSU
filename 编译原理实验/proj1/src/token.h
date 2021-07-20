#ifndef _TOKEN_H
#define _TOKEN_H

#define	ANDnum				257
#define ASSGNnum			258
#define DECLARATIONSnum		259
#define DOTnum				260
#define ENDDECLARATIONSnum	261
#define EQUALnum			262
#define GTnum				263
#define IDnum				264
#define INTnum				265
#define LBRACnum			266
#define LPARENnum			267
#define METHODnum			268
#define NEnum				269
#define ORnum				270
#define PROGRAMnum			271
#define RBRACnum			272
#define RPARENnum			273
#define SEMInum				274
#define VALnum				275
#define WHILEnum			276
#define CLASSnum			277
#define COMMAnum			278
#define DIVIDEnum			279
#define ELSEnum				280
#define EQnum				281
#define GEnum				282
#define ICONSTnum			283
#define IFnum				284
#define LBRACEnum			285
#define LEnum				286
#define LTnum				287
#define MINUSnum			288
#define NOTnum				289
#define PLUSnum				290
#define RBRACEnum			291
#define RETURNnum			292
#define SCONSTnum			293
#define TIMESnum			294
#define VOIDnum				295
#define EOFnum				0

/* Valid comments begining with "\/\*" and ending with "\*\/". */
#define COMMENTnum          296 

/* Memory allocation error. */
#define MALLOCERRnum        297

/* Strings containing invisible characters like '\n' and '\t' and backslash '\\\\', or strings not terminated with single quotes '\\''. */
#define INVALIDSTRnum       298

/* Comments not terminated with "\*\/". */
#define INVALIDCMTnum       299

/* Identifiers starting with numbers. */
#define INVALIDIDnum        300

/* Whitespace characters such as ' ', '\n' and '\t'. */
#define WHITESPACEnum       301

/* Other characters which are not recognized. */
#define OTHERSnum           302

#endif
