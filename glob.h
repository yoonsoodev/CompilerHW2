//  compiler_HW2
//  Programmer : ���ֿ�, ������, ���Ժ�, ������
//  Date : 2023.04.25

#pragma once
#ifndef symtable_h
#define symtable_h
#include "error.h"

/*ST index ���� ���� => symboltable.c ���� ���ǵ� */
extern int nextid;  //the current identifier
extern int sameid;
extern int nextfree;  //the next available index of ST
extern int STindex; // ST�� index�� ��Ÿ���� ����
extern char ST[];
extern char* token; //pointer to token
extern char in;
extern int found;
/*Identifier Line number => scanner.l���� ���ǵ� */
extern int cLine;

extern void SymbolTable();

#endif symtable_h


