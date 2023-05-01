//  compiler_HW2
//  Programmer : 배주연, 신윤수, 윤규빈, 조예은
//  Date : 2023.04.25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define FALSE 0
#define TRUE 1
#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z' || (x) == '_') )
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )
#define MAX_LEN        12

#define STsize 10  //size of string table
#define HTsize 100 //size of hash table

/*scanner에서 가져온 함수*/
extern yylex();
extern char *yytext; 

/*reporterror.c에서 가져온 함수*/
extern void ReportError(ERRORtypes error);

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index;  //index of identifier in ST
    HTpointer next;  //pointer to next identifier
} HTentry;

char seperators[] = " .,;:?!\t\n";


HTpointer HT[HTsize];
char ST[STsize];

/*관련 변수 정의*/

int hashcode;  //hashcode of identifier
int sameid;  //first index of identifier
int found;  //for the previous occurrence of an identifie
int nextid=0; //the current identifier
int nextfree=0;  //the next available index of ST
int STindex; // ST의 index를 나타내는 변수
char ST[STsize];
char* token; //pointer to token
char in;

//Initialize - open input file
 void initialize()
{
    token = yytext;//현재 처리 중인 입력 텍스트에서 마지막으로 인식된 토큰을 token pointer로 가르킴
    in = *token;//token의 가장 첫번째 문자를 input에 넣어줌
}

//isSerperator  -  distinguish the seperator
//Returns 1 if seperator, otherwise returns 0

 int isSeperator(char in)
{
    int i;
    int sep_len;
    sep_len = strlen(seperators);
    for (i = 0; i < sep_len; i++) {
        if (in == seperators[i])
            return 1;
    }
    return 0;
}


/*ReadIO     -     Read identifier from the input file the string table ST directly into
            ST(append it to the previous identifier).
            An identifier is a string of letters and digits, starting with a letter.
            If first letter is digit, print out error message. */
 void ReadID() // ST에 넣어줌
{
    int count = 0;
    nextid = nextfree;
    STindex = nextid; //ST의 index를 전역변수 STindex에 저장하여 main에서의 출력에 사용
    while (in != EOF && !isSeperator(in)) {
        if (nextfree == STsize) {
            error = overst;
            ReportError(error);
        }
        ST[nextfree++] = in;
        token++;
        in = *token;
        count++;

        if (!(isLetter(in) || isDigit(in) || isSeperator(in)) && in != EOF) {
            error = illid_illch;
        }
    }
    if (count >= MAX_LEN) {
        error = illid_long;
        ST[nextfree] = '\0';
        ReportError(error);
        nextfree = nextid;
    }
    if (error == illid_illch) {
        ST[nextfree] = '\0';
        ReportError(error);
        nextfree = nextid;
    }
}

/* ComputeHS     -     Compute the hash code of identifier by summing the ordinal values of its
                    characters and then taking the sum modulo the size of HT. */
 void ComputeHS(int nextid, int nextfree)
{
    int code, i;
    code = 0;
    for (i = nextid; i < nextfree - 1; i++) {
        int current = (int)ST[i];
        //If current is lowercase, convert it to uppercase
        current = (current >= 'A' && current <= 'Z' ? current - 'A' + 'a' : current);
        code += current;
    }
    hashcode = (code % HTsize)+1;
    hashcode = (hashcode == HTsize ? 0 : hashcode);
}

/*LookupHS     -    For each identifier,Look it up in the hashtable for previous occurrence
                of the identifier.If find a match, set the found flag as true.
                Otherwise flase.
                If find a match, save the starting index of ST in same id. */
 void LookupHS(int nextid, int hashcode)
{
    HTpointer here;
    int i, j;

    found = FALSE;
    if (HT[hashcode] != NULL) {
        here = HT[hashcode];
        while (here != NULL && found == FALSE) {
            found = TRUE;
            i = here->index;
            j = nextid;
            sameid = i;

            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
                int left = ST[i] >= 'A' && ST[i] <= 'Z' ? ST[i] - 'A' + 'a' : ST[i];
                int right = ST[j] >= 'A' && ST[j] <= 'Z' ? ST[j] - 'A' + 'a' : ST[j];
                if (left != right)
                    found = FALSE;
                else {
                    i++;
                    j++;
                }
            }
            here = here->next;
        }
    }
}


/* ADDHT    -    Add a new identifier to the hash table.
            If list head ht[hashcode] is null, simply add a list element with
            starting index of the identifier in ST.
            IF list head is not a null , it adds a new identifier to the head of the chain */
 void ADDHT(int hashcode)
{
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr));
    ptr->index = nextid;
    ptr->next = HT[hashcode];
    HT[hashcode] = ptr;
}

/* SymbolTable        -    Read the identifier from the file directly into ST.
            Compute its hashcode.
            Look up the idetifier in hashtable HT[hashcode]
            If matched, delete the identifier from ST and print ST-index
            of the matching identifier.
            If not matched , add a new element to the list,pointing to new identifier.
*/
 
 void SymbolTable(){ //HashTable에 넣는 과정 
    int i;
    initialize();

    while (in != EOF) { //
        error = noerror;
        SkipSeperators();
        ReadID();
        if (error == noerror) {
            if (nextfree == STsize) {
                error = overst;
                ReportError(error);
            }
            ST[nextfree++] = '\0';

            ComputeHS(nextid, nextfree);
            LookupHS(nextid, hashcode);
            if (!found) {
                ADDHT(hashcode);
            }
            else {//same identifier already exsist
                nextfree = nextid;
            }
        }
    }
}
