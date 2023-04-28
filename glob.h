//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

#ifndef symtable_h
#define symtable_h

#define FALSE 0
#define TRUE 1
#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z' || (x) == '_') )
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )
#define MAX_LEN        12

#define STsize 10  //size of string table
#define HTsize 100    //size of hash table

/*error type*/
enum errorTypes { noerror, illid_digit, illid_long, illid_illch, overst };
typedef enum errorTypes ERRORtypes;
ERRORtypes error;

/*ST index 관련 변수*/
extern int nextid;  //the current identifier
extern int nextfree;  //the next available index of ST
extern int STindex; // ST의 index를 나타내는 변수
extern char ST[STsize];
extern char* token; //pointer to token
extern char in;

/*Identifier Line number*/
extern int cLine;

void initialize();
int isSeperator(char c);
void PrintError(ERRORtypes error);
void SkipSeperators();
void ReadID();
void ComputeHS(int nid, int nfree);
void LookupHS(int nid, int hscode);
void ADDHT(int hscode);
void SymbolTable();

/*symtable.c와 reporterror.c에서 공통적으로 사용할 변수*/

#endif /* symtable_h */

#ifndef reporterror_h
#define reporterror_h

#include <stdio.h>

void ReportError(ERRORtypes error);

#endif /* reporterror_h */
