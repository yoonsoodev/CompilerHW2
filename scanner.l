%option case-insensitive

%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
cLine = 1;
%}

%%

"const"				return(TCONST);
"else"				return(TELSE);
"if"				return(TIF);
"int"				return(TINT);
"return"			return(TRETURN);
"void"				return(TVOID);
"while"				return(TWHILE);

"\n"				{cLine++;}
[ \t]				;

0|[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?	return(TNUMBER);
[0-9]+"."[0-9]+		return(TREALNUM);

"/*"([^*]|\*+[^*/])*\**"*/"		{
for(int i=0;i<yyleng;i++){
	if(yytext[i]=='\n') cLine ++;}
	}
"//".*				;

[a-zA-Z_][a-zA-Z0-9_]* {
						if(yyleng > 12) {
							error= illid_long;
							return(TERROR);
						}
						else {
							SymbolTable();
							return(TIDENT);
						}
					}
[0-9][a-zA-Z0-9_]*	{
						error = illid_digit;
						return(TERROR);
					}

[a-zA-Z_]*[^a-zA-Z0-9_ .,;:?!\t\n(){}[\]=!<>&|+\-\*\/%]+[a-zA-Z0-9_]*[^a-zA-Z0-9_ .,;:?!\t\n(){}[\]=!<>&|+\-\*\/%]*	{
						error = illid_illch;
						return(TERROR);
					}

"=="				return(TEQUAL);
"!="				return(TNOTEQU);
"<"					return(TLESS);
">"					return(TGREAT);
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

.				{error= illid_illch; return(TERROR);}	
%%

int yywrap()
{
	printf("   End of Lex \n");
	return 1;
}