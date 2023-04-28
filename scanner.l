%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
cLine = 1;
%}
letter				[a-zA-z_]
digit				[0-9]

%%
"const"				return(TCONST);
"else"				return(TELSE);
"if"				return(TIF);
"int"				return(TINT);
"return"			return(TRETURN);
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
"+"					return(TPLUS);
"-"					return(TMINUS);
"*"					return(TSTAR);
"/"					return(TSLASH);
"%"					return(TMOD);
"!"					return(TNOT);
"="					return(TASSIGN);


"("					return(TPL);
")"					return(TPR);
"{"					return(TCBRL);
"}"					return(TCBRR);
"["					return(TSQBRL);
"]"					return(TSQBRR);
","					return(TCOMMA);
";"					return(TSEMICOLON);


[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?	return(TNUMBER);
[0-9]+"."[0-9]+		return(TREALNUM);

"/*"([^*]|\*+[^*/])*\**"*/"		{
for(int i=0;i<yyleng;i++){
	if(yytext[i]=='\n') cLine ++;}
	}
"//".*				;

{letter}({letter}|{digit})*	{
						if(yyleng > 12) {
							error= illid_long;
							return(TERROR);
						}
						else {
							SymbolTable();
							return(TIDENT);
						}
					}
{digit}({letter}|{digit})+	{
						error = illid_digit;
						return(TERROR);;
					}
{letter}+[^A-Za-z0-9_ .,;:?!\t\n]+({letter}|{digit})* 	| 
[^A-Za-z0-9_ .,;:?!\t\n]+({letter}|{digit})+  {
									error = illid_illch;
									return(TERROR);;
								}


"\n"			{cLine++; return(TCARR);}
[ \t]				;
.				{error= illid_illch; return(TERROR);}	
%%

int yywrap()
{
	printf("   End of Lex \n");
	return 1;
}