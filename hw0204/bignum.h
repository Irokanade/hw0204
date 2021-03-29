//
//  bignum.h
//  hw0204
//
//  Created by Michael Leong on 2021/3/22.
//

#ifndef bignum_h
#define bignum_h
#define MAXDIGITS 1024

#include <stdio.h>
#include <stdint.h>

typedef struct _sBigNum {
    char num[MAXDIGITS]; //represents the number
    int signbit;
    unsigned long lastDigit; //index of the size of the number
} sBigNum;

void initializeBigNum(sBigNum *pNum);
int checkNonDig(char *str);
void rvereseArray(char arr[], int start, int end);
int removeNegative(sBigNum *num);
int addNegative(sBigNum *num);
void positiveAdd( sBigNum *pResult ,const sBigNum num01 , const sBigNum
                 num02 ); // both num01 and num02 must be positive
int positiveSubtraction(sBigNum *pResult , const sBigNum num01 , const
                         sBigNum num02); //both num01 and num02 must be positive
void print( const sBigNum num );

int32_t set( sBigNum *pNum, char *str );

int32_t compare( const sBigNum num01 , const sBigNum num02 );

int32_t digits( const sBigNum num );

void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum
         num02 );

void subtract( sBigNum *pResult , const sBigNum num01 , const
              sBigNum num02 );

void multiply( sBigNum *pResult , const sBigNum num01 , const
              sBigNum num02 );

void divide( sBigNum *pQuotient , sBigNum *pRemainder , const
            sBigNum num01 , const sBigNum num02 );

int32_t power( sBigNum *pResult , int32_t n, int32_t k );

int32_t combine( sBigNum *pResult , int32_t n, int32_t k );

#endif /* bignum_h */
