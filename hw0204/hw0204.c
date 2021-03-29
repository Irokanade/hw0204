//
//  hw0204.c
//  hw0204
//
//  Created by Michael Leong on 2021/3/20.
//

#include <stdio.h>
#include "bignum.h"
#include <string.h>

int main() {
    printf("sizeof long double: %ld\n", sizeof(long double));
    printf("MAXDIGITS: %d\n", MAXDIGITS);
    sBigNum bignum1;
    sBigNum bignum2;
    sBigNum result;
    
    set(&bignum1, "9955555");
    set(&bignum2, "71166");
    
    printf("bignum1: ");
    print(bignum1);
    printf("\n");
    printf("lastDigit: %ld\n", bignum1.lastDigit);
    
    printf("bignum2: ");
    print(bignum2);
    printf("\n");
    printf("lastDigit: %ld\n", bignum2.lastDigit);
    
    printf("compare: %d\n", compare(bignum1, bignum2));
    
    printf("add\n");
    add(&result, bignum1, bignum2);
    print(result);
    printf("\n");
    
    printf("subtraction\n");
    subtract(&result, bignum1, bignum2);
    print(result);
    printf("\n");
    
    printf("multiplication\n");
    multiply(&result, bignum1, bignum2);
    print(result);
    printf("\n");
    
    sBigNum quotient;
    sBigNum remainder;
    
    printf("divide\n");
    divide(&quotient, &remainder, bignum1, bignum2);
    printf("remainder\n");
    print(remainder);
    printf("\n");
    printf("quotient\n");
    print(quotient);
    printf("\n");
    
    sBigNum test;
    test.num[0] = '0';
    test.num[1] = '0';
    test.num[2] = '0';
    test.num[3] = '0';
    test.num[4] = '1';
    test.num[5] = '2';
    test.num[6] = '3';
    test.lastDigit = strlen(test.num);
    printf("test\n");
    print(test);
    printf("\n");
    removeFrontZero(&test);
    printf("test\n");
    print(test);
    printf("\n");
    return 0;
}
