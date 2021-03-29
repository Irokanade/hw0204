//
//  bignum.c
//  hw0204
//
//  Created by Michael Leong on 2021/3/22.
//

#include "bignum.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void initializeBigNum(sBigNum *pNum) {
    memset(pNum->num, 0, MAXDIGITS);
    pNum->signbit = 1;
    pNum->lastDigit = 0;
}

int checkNonDig(char *str) {
    
    if(*str == '0' || *(str+1) == '0') {
        return 0; //first digit cannot be 0
    }
    
    for(const char *i = str; *i != 0; i++) {
        if(*i == 45) {
            //skip '-' sign
            continue;
        } else if(*i < 48 || *i > 57) {
            //check if it is decimal character
            return 0; //false
        }
    }
    return 1; //true
}

void rvereseArray(char arr[], int start, int end) {
    char temp;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int removeNegative(sBigNum *num) {
    if(num->signbit > 0) {
        return 0; // not a negative
    }
    if(num->num[0] == '-') {
        size_t i = 0;
        for(i = 0; i < num->lastDigit+1; i++) {
            num->num[i] = num->num[i+1];
        }
        num->signbit = 1;
    }
    
    return 1;
}

int addNegative(sBigNum *num) {
    if(num->signbit < 0) {
        return 0; //not a postitive
    }
    if(num->num[0] != '-') {
        for(int i = (int)num->lastDigit+1; i > 0; i--) {
            num->num[i] = num->num[i-1];
        }
        num->num[0] = '-';
        num->signbit = -1;
    }
    
    return 1;
}

void positiveAdd(sBigNum *pResult, sBigNum num01, sBigNum num02) {
    initializeBigNum(pResult);
    
    initializeBigNum(pResult);
    
    size_t i = 0;
    unsigned carry = 0;
    while(1) {
        if(num01.num[i] == 0 || num02.num[i] == 0) {
            break;
        }
        
        unsigned int d1 = 0;
        unsigned int d2 = 0;
        unsigned int sum = 0;
        
        d1 = num01.num[num01.lastDigit-1-i]-'0';
        d2 = num02.num[num02.lastDigit-1-i]-'0';
        sum = d1+d2+carry;
        carry = 0;
        char temp[2] = {0};
        temp[0] = (sum%10)+'0';
        
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        carry = sum/10;
        free(pResultTemp);
        
        /*printf("d1: %d\n", d1);
        printf("d2: %d\n", d2);
        printf("temp: %s\n", temp);
        printf("carry: %d\n", carry);
        printf("pResult->num: %s\n", pResult->num);*/
        
        i++;
    }
    
    
    while(num01.num[i] != 0) {
        int sum;
        sum = num01.num[num01.lastDigit-1-i]-'0' + carry;
        char temp[2] = {0};
        temp[0] = (sum%10)+'0';
        
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        carry = sum/10;
        free(pResultTemp);
        
        i++;
    }
    
    while(num02.num[i] != 0) {
        int sum;
        sum = num02.num[num02.lastDigit-1-i]-'0' + carry;
        char temp[2] = {0};
        temp[0] = (sum%10)+'0';
        
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        carry = sum/10;
        free(pResultTemp);
        
        i++;
    }
    
    if(carry) {
        char temp[2] = {0};
        temp[0] = carry+'0';
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        carry = 0;
        free(pResultTemp);
        i++;
    }
    pResult->lastDigit = strlen(pResult->num);
    //printf("pResult->num: %s\n", pResult->num);
}

int positiveSubtraction(sBigNum *pResult, sBigNum num01, sBigNum num02) {
    //larger positive - smaller positive
    //must be num01 -num02
    
    initializeBigNum(pResult);
    
    if(compare(num01, num02) == -1) {
        return 0;
    }
    
    initializeBigNum(pResult);
    
    int carry = 0; //negative carry
    size_t i = 0;
    while(1) {
        if(num01.num[i] == 0 || num02.num[i] == 0) {
            break;
        }
        
        unsigned int d1;
        unsigned int d2;
        int substract;
        
        d1 = num01.num[num01.lastDigit-1-i]-'0';
        d2 = num02.num[num02.lastDigit-1-i]-'0';
        substract = d1-d2-carry;
        //printf("subtract: %d\n", substract);
        if(substract < 0) {
            substract += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        //printf("subtract: %d\n", substract);
        char temp[2] = {0};
        temp[0] = substract+'0';
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        free(pResultTemp);
        
        /*printf("d1: %d\n", d1);
        printf("d2: %d\n", d2);
        printf("subtract: %d\n", substract);
        printf("temp: %s\n", temp);
        printf("pResult->num: %s\n", pResult->num);*/
        
        i++;
    }
    
    while(num01.num[i] != 0) {
        int substract;
        substract = num01.num[num01.lastDigit-1-i]-'0'-carry;
        carry = 0;
        char temp[2] = {0};
        temp[0] = substract+'0';
        char *pResultTemp = strdup(pResult->num);
        memset(pResult->num, 0, MAXDIGITS);
        strncpy(pResult->num, temp, strlen(temp));
        strncat(pResult->num, pResultTemp, strlen(pResultTemp));
        free(pResultTemp);
        i++;
    }
    pResult->lastDigit = strlen(pResult->num);
    
    return 1;
}

void print( const sBigNum num ) {
    printf("%s", num.num);
}

int32_t set( sBigNum *pNum, char *str ) {
    memset(pNum->num, 0, MAXDIGITS);
    pNum->signbit = 1;
    pNum->lastDigit = 0;
    
    if(!checkNonDig(str)) {
        strncat(pNum->num, "0", 1);
        return 0; //set failure as there are non decimal characters
    }
    //printf("num: %s\n", pNum->num);
    //printf("str: %s\n", str);
    if(*str == '-') {
        pNum->signbit = -1;
        //printf("signbut: %d\n", pNum->signbit);
    }
    //printf("signbut: %d\n", pNum->signbit);
    strncat(pNum->num, str, strlen(str));
    if(pNum->signbit == -1) {
        pNum->lastDigit = strlen(str)-1;
    } else {
        pNum->lastDigit = strlen(str);
    }
    //printf("num: %s\n", pNum->num);
    
    return 1; //set successfull
}

int32_t compare( const sBigNum num01 , const sBigNum num02 ) {
    /*
     compare: If Num01 is larger than Num02, return 1; If Num01 is
            equal to Num02, return 0; If Num01 is less than Num02, return -1.
    */
    
    if(num01.signbit > num02.signbit) {
        return 1;
    } else if(num01.signbit < num02.signbit) {
        return -1;
    } else if(num01.lastDigit > num02.lastDigit) {
        return 1;
    } else if(num01.lastDigit < num02.lastDigit) {
        return -1;
    }
    
    //else they are the same number of character
    char *pNum1 = NULL;
    char *pNum2 = NULL;
    if(num01.signbit == -1) {
        pNum1 = num01.num  - 1;
    } else {
        pNum1 = num01.num;
    }
    
    if(num02.signbit == -1) {
        pNum2 = num02.num -1;
    } else {
        pNum2 = num02.num;
    }
    
    for(size_t i = 0; i < MAXDIGITS; i++) {
        //printf("%c\n", *(pNum1+i));
        //printf("%c\n", *(pNum2+i));
        
        if(*(pNum1+i) == 0 || *(pNum2+i) == 0) {
            return 0;
        } else if (*(pNum1+i) < *(pNum2+i)) {
            return -1;
        } else if (*(pNum1+i) > *(pNum2+i)) {
            return 1;
        }
    }
    
    return 0;
}

int32_t digits( const sBigNum num ) {
    return (int32_t)num.lastDigit;
}

void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum
         num02 ) {
    initializeBigNum(pResult);
    
    sBigNum num01Copy = num01;
    sBigNum num02Copy = num02;
    removeNegative(&num01Copy);
    removeNegative(&num02Copy);
    //printf("pResult: %s\n", pResult->num);

    //negative plus negative
    if(num01.signbit == -1 && num02.signbit == -1) {
        //printf("num01Copyflip: %s\n", num01Copy.num);
        //printf("num02Copyflip: %s\n", num02Copy.num);
        positiveAdd(pResult, num01Copy, num02Copy);
        //printf("pResult: %s\n", pResult->num);
        addNegative(pResult);
        //printf("pResult: %s\n", pResult->num);
        return;
    } else if(num01.signbit == 1 && num02.signbit == 1){
        //postive plus positive
        positiveAdd(pResult, num01Copy, num02Copy);
        return;
    } else if(num01.signbit == 1) {
        //postive plus negative
        if(compare(num01Copy, num02Copy) >= 0) {
            //result is positive
            positiveSubtraction(pResult, num01Copy, num02Copy);
            return;
        } else {
            //result is negative
            positiveSubtraction(pResult, num02Copy, num01Copy);
            addNegative(pResult);
            return;
        }
    } else if(num02.signbit == 1) {
        //negative plus positive
        if(compare(num01Copy, num02Copy) >= 0) {
            //result is negative
            positiveSubtraction(pResult, num01Copy, num02Copy);
            addNegative(pResult);
            return;
        } else {
            //result is positive
            positiveSubtraction(pResult, num02Copy, num01Copy);
            return;
        }
    }
    
}

void subtract( sBigNum *pResult , const sBigNum num01 , const
              sBigNum num02 ) {
    initializeBigNum(pResult);
    sBigNum num01Copy = num01;
    sBigNum num02Copy = num02;
    removeNegative(&num01Copy);
    removeNegative(&num02Copy);
    
    if(num01.signbit == -1) {
        
        //negative minus positive
        if(num02.signbit == 1) {
            positiveAdd(pResult, num01Copy, num02Copy);
            addNegative(pResult);
            return;
        } else if(num02.signbit == -1) {
            //negative minus negative
            if(compare(num01Copy, num02Copy) >= 0) {
                //result is negative
                positiveSubtraction(pResult, num01Copy, num02Copy);
                addNegative(pResult);
                return;
            } else if(compare(num01Copy, num02Copy) < 0){
                //result is positive
                positiveSubtraction(pResult, num02Copy, num01Copy);
                return;
            }
        }
    } else {
        //postive minus positive
        if(num02.signbit == 1) {
            if(compare(num01Copy, num02Copy) >= 0) {
                //result is positive
                positiveSubtraction(pResult, num01Copy, num02Copy);
                return;
            } else {
                //result is negative
                positiveSubtraction(pResult, num02Copy, num01Copy);
                addNegative(pResult);
                return;
            }
        } else {
            //positive minus negative
            positiveAdd(pResult, num01Copy, num02Copy);
            return;
        }
    }
}

void multiply( sBigNum *pResult , const sBigNum num01 , const
              sBigNum num02 ) {
    initializeBigNum(pResult);
    sBigNum num01Copy = num01;
    sBigNum num02Copy = num02;
    removeNegative(&num01Copy);
    removeNegative(&num02Copy);
    
    int i_n1 = 0;
    int i_n2 = 0;
    
    memset(pResult->num, '0', MAXDIGITS);
    
    for(int i = (int)num01Copy.lastDigit-1; i >= 0; i--) {
        int carry = 0;
        i_n2 = 0;
        int n1 = num01Copy.num[i]-'0';
        for(int j = (int)num02Copy.lastDigit-1; j >= 0; j--) {
            int n2 = num02Copy.num[j]-'0';
            //printf("pResult array: %d\n", pResult->num[i_n1 + i_n2]-'0');
            int sum = n1*n2 + (pResult->num[i_n1 + i_n2]-'0') + carry;
            carry = sum/10;
            pResult->num[i_n1 + i_n2] = (sum % 10)+'0';
            //printf("pResult: %s\n", pResult->num);
            
            i_n2++;
            //printf("sum: %d\n", sum);
        }
        if (carry > 0) {
            pResult->num[i_n1 + i_n2] += carry;
        }
        
        
        
        i_n1++;
    }
    
    //char *i = pResult->num+i_n1+i_n2;
    //printf("*i: %c\n", *i);
    
    for(char *i = pResult->num+i_n1+i_n2; *i == '0'; i++) {
        //printf("*i: %c\n", *i);
        if(*i == '0') {
            *i = 0;
        }
    }
    
    pResult->lastDigit = strlen(pResult->num);
    rvereseArray(pResult->num, 0, (int)pResult->lastDigit-1);
    int resultSign = num01.signbit*num02.signbit;
    if(resultSign == -1) {
        addNegative(pResult);
    }
    //printf("lastDigit: %ld\n", pResult->lastDigit);
}

void divide( sBigNum *pQuotient , sBigNum *pRemainder , const
            sBigNum num01 , const sBigNum num02 ) {
    initializeBigNum(pQuotient);
    initializeBigNum(pRemainder);
    sBigNum num01Copy = num01;
    sBigNum num02Copy = num02;
    removeNegative(&num01Copy);
    removeNegative(&num02Copy);
    
    
   //num01 divided by num02
    for(int i = (int)num01Copy.lastDigit-1; i >= 0; i--) {
        int int1 = num01Copy.num[i]-'0';
        
        for(int j = (int)num02Copy.lastDigit-1; j >= 0;j--) {
            int int2 = num02Copy.num[j]-'0';
            
            while(int1 >= int2) {
                int1 -= int2;
            }
            
        }
    }
}
