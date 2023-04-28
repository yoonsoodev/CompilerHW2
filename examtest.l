%{
#include <stdio.h>
#include <stdlib.h>
enum tnumber { TEOF, TINTEGER, TIDEN, TNUM, TASSIGN, TADD, TSEMI, TDOT, TBEGIN, TEND, TERROR};
%}

letter	[a-zA-Z_]
digit	[0-9]

%%
abc					ECHO;
def					ECHO;
Mega-				yymore();
Kludge				print("%/s\n",yytext);
Foobar				yyless(3);
bar					ECHO;
[a-z]+				print("ident");
[ \t\n]				;
.				;
%%

void main()
{
	printf("  Start of Lex\n");
	yylex();
}

int yywrap()
{
	printf("   End of Lex \n1771032 신윤수 \n");
	return 1;
}