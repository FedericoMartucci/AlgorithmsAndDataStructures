#include "recursivity.h"

int main()
{
    int vec[] = {1, 5, 7, 13, 19, 22, 43};
    int valueToSearch = 1;
//    char batch[] = "aa     a   anItAlava la tinaa,.,. a  ,454  a";
//    printf("%f", _powWrapper(2, 20));
//    printf("%d", multiplication(1, 3000000));
//    printf("%d", calculateFibonacci(13));
//    printf("%llu", decimalToBinary(1048575));
//    printf("%d", binaryToDecimal(11111));
//    printf("%d", ackermannFunction(2, 8));
//    printf("%d", isPalindromeWrapper(batch));
    void* element = bsearch(&valueToSearch, vec, sizeof(vec)/sizeof(int), sizeof(int), cmpInt);
    if(!element)
        printf("404 NOT FOUND");
    else
        printf("%d", *(int*)element);
    return 0;
}
