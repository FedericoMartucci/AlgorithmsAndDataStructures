#include "recursivity.h"
#include <time.h>

float _powWrapper(float base, int exponent){
    if(base == 0 && exponent <= 0)
        return 0;
    if(exponent < 0){
        float newBase = 1 / base;
        exponent *= -1;
        return _pow(newBase, exponent);
    }
    return _pow(base, exponent);
}

float _pow(float base, int exponent){
    if(exponent == 0)
        return 1;

    base *= _pow(base, exponent - 1);

    return base;
}

int multiplication(int factor1, int factor2){
    if(factor1 < factor2){
        int aux = factor1;
        factor1 = factor2;
        factor2 = aux;
    }
    if(factor1 < 0 && factor2 < 0){
        factor1 *= -1;
        factor2 *= -1;
    }
    if(!factor2)
        return 0;
    return multiplication(factor1, factor2 - 1) + factor1;

}

int calculateFibonacci(int iTerm){
    if(iTerm < 0)
        return FIBONACCI_ERR;
    if(iTerm == 1 || iTerm == 0)
        return iTerm;
    return calculateFibonacci(iTerm - 1) + calculateFibonacci(iTerm - 2);
}

long long unsigned decimalToBinary(int decimalNumber){
    if(decimalNumber < 0)
        return CONVERTION_ERR;
    if(decimalNumber == 1 || decimalNumber == 0)
        return decimalNumber;

    return decimalToBinary(decimalNumber/2) * 10 + decimalNumber % 2;
}

int binaryToDecimal(int binaryNumber){///anda mal
    static int multiplicationFactor = 0;
    if(binaryNumber == 1 || binaryNumber == 0){
        return binaryNumber;
    }
    return binaryToDecimal(binaryNumber/10) + _powWrapper(2, multiplicationFactor) * (binaryNumber / _powWrapper(10, multiplicationFactor));
}

int ackermannFunction(int m, int n){
    if(m < 0 || n < 0)
        return FUNCTION_ERR;
    if(m == 0)
        return n + 1;
    if(n == 0)
        return ackermannFunction(m - 1, 1);
    return ackermannFunction(m - 1, ackermannFunction(m, n - 1));
}
int isPalindromeWrapper(const char* word){
    const char* finalLetter = word + sstrlen(word) - 1;

    return isPalindrome(word, finalLetter);
}

int isPalindrome(const char* initialLetter, const char* finalLetter){
    if(initialLetter >= finalLetter)
        return 1;
    if(!IS_LETTER(*initialLetter))
        return isPalindrome(initialLetter + 1, finalLetter);
    if(!IS_LETTER(*finalLetter))
        return isPalindrome(initialLetter, finalLetter - 1);
    if(TO_LOWER(*initialLetter) != TO_LOWER(*finalLetter))
        return 0;
    return isPalindrome(initialLetter + 1, finalLetter - 1);
}

int sstrlen(const char* word){
    if(!*word)
        return 0;

    return sstrlen(word + 1) + 1;
}

void* bsearch(const void* valueToSearch, const void* data, size_t nitems,
              size_t sizeOfItem, int (*cmp)(const void*, const void*)){
    void* dataWithOffset = (void*)data + (nitems / 2) * sizeOfItem;
    if(!cmp(valueToSearch, dataWithOffset))
        return dataWithOffset;
    if(data == dataWithOffset)
        return NULL;
    if(cmp(valueToSearch, dataWithOffset) < 0)
        return bsearch(valueToSearch, data, nitems / 2, sizeOfItem, cmp);
    if(cmp(valueToSearch, dataWithOffset) > 0)
        return bsearch(valueToSearch, dataWithOffset + sizeOfItem,
                       nitems / 2 - !(nitems % 2), sizeOfItem, cmp);
}

int cmpInt(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}
