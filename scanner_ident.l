%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
%}

%%
"const"				return(TCONST);
"else"				return(TELSE);
"if"				return(TIF);
"int"				return(TINT);
"return"				return(TRETURN);
"void"				return(TVOID);
"while"				return(TWHILE);
"=="				return(TEQUAL);
"!="				return(TNOTEQU);
"<="				return(TLESSE);
">="				return(TGREATE);
"&&"				return(TAND);
"||"				return(TOR);
"++"				return(TINC);
"--"				return(TDEC);
"+="				return(TADDASSIGN);
"-="				return(TSUBASSIGN);
"*="				return(TMULASSIGN);
"/="				return(TDIVASSIGN);
"%="				return(TMODASSIGN);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?	return(TNUMBER);
"/*"([^*]|\*+[^*/])*\++"*/"		;
"//".*				;
[ \t\n]				;
{letter}({letter}|{digit})*	{
						if(yyleng > 12) {
							err= illid_long;
							reporterror(err);
						}
						else {
							symtable();
							return(TIDENT);
						}
					}
{digit}({letter}|{digit})+	{
						err = illid_digit;
						reporterror(err);
					}
{letter}+[^A-Za-z0-9_ .,;:?!\t\n]+({letter}|{digit})* 	|
[^A-Za-z0-9_ .,;:?!\t\n]+({letter}|{digit})+  {
									err = illid_ch;
									reporterror(err);
								}


%%


int yywrap()
{
	printf("   End of Lex \n");
	return 1;
}