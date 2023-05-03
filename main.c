//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern yylex();
extern char *yytext;

int cErrors = 0; //에러 개수를 세기 위한 변수


//각 token의 line number, token type, symboltable index(identifier인 경우에만), token을 프린트 하는 함수
void printtoken(enum tnumber tn){
    /*print line number*/
    printf("%-15d",cLine);
    
    /*print token type*/
    switch(tn){
        case TIDENT: printf("ident          "); break;
            
        case TNUMBER: printf("number         "); break;
        case TREALNUM: printf("real number    "); break;
        
        case TCONST: printf("const          ");break;
        case TELSE: printf("else           "); break;
        case TIF: printf("if             "); break;
        case TINT: printf("int            ");break;
        case TRETURN: printf("return         "); break;
        case TVOID: printf("void           "); break;
        case TWHILE: printf("while          "); break;
            
        case TPLUS: printf("plus           "); break;
        case TMINUS: printf("minus          ");break;
        case TSTAR: printf("star           "); break;
        case TSLASH: printf("slash          "); break;
        case TMOD: printf("mod            ");break;
        case TASSIGN: printf("assign         "); break;
        case TADDASSIGN: printf("addassign      "); break;
        case TSUBASSIGN: printf("subassign      "); break;
        case TMULASSIGN: printf("mulassign      ");break;
        case TDIVASSIGN: printf("divassign      "); break;
        case TMODASSIGN: printf("modassign      "); break;
        case TNOT: printf("not            ");break;
        case TAND: printf("and            "); break;
        case TOR: printf("or             "); break;
        case TEQUAL: printf("equal          "); break;
        case TNOTEQU: printf("notequ         ");break;
        case TLESS: printf("less           "); break;
        case TGREAT: printf("great          "); break;
        case TLESSE: printf("lesse          ");break;
        case TGREATE: printf("greate         "); break;
        case TINC: printf("inc            "); break;
        case TDEC: printf("dec            "); break;

        case TSQBRL: printf("square bracket "); break;
        case TSQBRR: printf("square bracket "); break;
        case TCBRL: printf("curly bracket  "); break;
        case TCBRR: printf("curly bracket  "); break;
        case TPL: printf("parentheses    "); break;
        case TPR: printf("parentheses    "); break;
        case TCOMMA: printf("comma          "); break;
        case TSEMICOLON: printf("semicolon      "); break;
            
        case TERROR: printf("**Error**      ");break;
    }
    
    /*print error(error가 있는 경우)*/
    if (tn == TERROR) {
        ReportError(error);//에러메세지 출력하는 함수 호출
        cErrors++;//error 개수 세기
        return;
    }

    /*print ST-index(identifier인 경우에만)*/
    else if(tn == TIDENT){
        if (!found) {
            printf("%-15d", STindex);//ST에서의 index를 symtable로부터 가져옴
            printf("%-12s       (entered) \n", yytext);
        }
        else {
            printf("%-15d", sameid);
            printf("%-12s       (already entered) \n", yytext);
        }
        return;
    }
    else {/*print token*/
        printf("               %-12s \n", yytext);
    }
}

//token 인식 및 출력(ident인 경우 ST에 삽입)
int main()
{
    enum tnumber tn;  // token number
    printf("Line number    Token type     ST-index       Token               \n");//print head
    while  ((tn = yylex()) != TEOF) {
        printtoken(tn);
    }
    
    //error 개수 출력
    if (cErrors == 0){
        printf("No Errors detected.");
    }
    else{
        printf("%d errors detected", cErrors);
    }
    return 0;
}
