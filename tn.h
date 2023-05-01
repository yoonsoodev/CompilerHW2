//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

enum tnumber {
    /*End of File*/
    TEOF,

    /*identifier*/
    TIDENT,
    
    /*constant*/
    TNUMBER, TREALNUM,
    
    /*keyword*/
    TCONST, TELSE, TIF, TINT, TRETURN, TVOID, TWHILE,//(const, else, if, int, return, void, while)
    
    /*operator*/
    TPLUS, TMINUS, TSTAR, TSLASH, TMOD, //사칙연산자(+, -, *, /, %)
    TASSIGN, TADDASSIGN, TSUBASSIGN, TMULASSIGN, TDIVASSIGN, TMODASSIGN, //배정연산자(=, +=, -=, *=, /=, %=)
    TNOT, TAND, TOR, //논리연산자(!, &&, ||)
    TEQUAL, TNOTEQU, TLESS, TGREAT, TLESSE, TGREATE, //관계연산자(==, !=, <, >, <=, >=)
    TINC, TDEC, //증감연산자
    
    /*Special Symbol*/
    TSQBRL, TSQBRR, //대괄호(Square Brackets) 왼쪽, 오른쪽([, ])
    TCBRL, TCBRR, //중괄호(Curly Brackets) 왼쪽, 오른쪽({, })
    TPL, TPR, //소괄호(parentheses) 왼쪽, 오른쪽((, ))
    TCOMMA, //반점(,)
    TSEMICOLON, //세미클론(;)
    
   
    /*error*/
    TERROR    
};
