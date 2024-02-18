#ifndef RECURSIVITY_H_INCLUDED
#define RECURSIVITY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define IS_LETTER(X) ((X >= 'a' && X <= 'z') || (X >= 'A' && X <= 'Z'))
#define TO_UPPER(X) ((X >= 'a' && X <= 'z')? (X - ('a' - 'A')) : (X))
#define TO_LOWER(X) ((X >= 'A' && X <= 'Z')? (X + ('a' - 'A')) : (X))

#define FIBONACCI_ERR -1
#define CONVERTION_ERR -1
#define FUNCTION_ERR -1

float _pow(float base, int exponent);
float _powWrapper(float base, int exponent);
int multiplication(int factor1, int factor2);
int calculateFibonacci(int i_term);
long long unsigned decimalToBinary(int decimalNumber);
int binaryToDecimal(int binaryNumber);
int ackermannFunction(int n1, int n2);
int isPalindromeWrapper(const char* word);
int isPalindrome(const char* initialLetter, const char* finalLetter);
int sstrlen(const char* word);
void* bsearch(const void* valueToSearch, const void* data, size_t nitems,
              size_t sizeOfItem, int (*cmp)(const void*, const void*));
int cmpInt(const void* a, const void* b);
#endif // RECURSIVITY_H_INCLUDED
