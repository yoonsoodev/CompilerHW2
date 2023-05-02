//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

#include <stdio.h>
#include <stdlib.h>

#include "glob.h"

extern char* yytext;
/* ReportError    -     Print out error messages
            overst :  overflow in ST. print the hashtable and abort
            illid_digit    : illegal identifier (start with digit)
            illid_long    : illegal identifier (too long identifier)
            illid_illch    : illegal identifier (containing illegal characters) */

void ReportError(ERRORtypes error){ //원본 symbol table 코드에서 PrintError 함수 부분 추출
    int index = nextid;//illid_illch에서 이용해줄 변수. switch문 안에 선언해두면 에러가 발생할 가능성이 있어서 switch문 바깥에 뺴둠.

    switch (error) {
    case overst:
        nextfree = nextid;
        printf("               %-20s\n","Overflow");
        exit(0);
        break;
    case illid_long:
        printf("               %-20s\n","Too long identifier");
        break;
    case illid_illch:
        printf("               %-20sillegal IDENT\n", yytext);
        break;
    case illid_digit:
        printf("               %-20sillegal IDENT\n", yytext);
        break;
    }
}
