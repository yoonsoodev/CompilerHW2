//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

#pragma once
#ifndef symtable_h
#define symtable_h
#include "error.h"

/*ST index 관련 변수 => symboltable.c 에서 정의됨 */
extern int nextid;  //the current identifier
extern int sameid;
extern int nextfree;  //the next available index of ST
extern int STindex; // ST의 index를 나타내는 변수
extern char ST[];
extern char* token; //pointer to token
extern char in;
extern int found;
/*Identifier Line number => scanner.l에서 정의됨 */
extern int cLine;

extern void SymbolTable();

#endif symtable_h


