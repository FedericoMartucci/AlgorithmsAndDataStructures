#include "file.h"

int main()
{
    createBatch("datos");
    traverseFileWithList("datos", sizeof(tProduct), insertToEndWithoutProvider);
    return 0;
}
