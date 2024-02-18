#include "../ADT/Dynamic/List.h"

int main()
{
//    int vec[] = {7, 23, 48, 9, 17, 7, 8, 10, 7, 41, 7};
//    int sortedVec[] = {9, 5, 3, 4, 1, 6, 7, 8, 0, -1};
//    int element;
//    int key = 488;
    tList _list;
//
    createList(&_list);
//
//    printf("Adding to list\n");
//    for(int i = 0; i < sizeof(vec)/sizeof(int); i ++){
//        addToEndList(&_list, &vec[i], sizeof(int));
//        printf("%d ", vec[i]);
//    }
//    printf("\nRemoving 7 last elements");
//    removeNLastElements(&_list, 7);

//    printf("\nRemoving by position\n");
//    removeElementByPosition(&_list, 11);
//    sortList(&_list, cmpKey);
//    findMinor(&_list, cmpKey);
//    sortListBySelection(&_list, cmpKey);
//    printf("\nRemoving aparitions\n");
//    removeCoincidencesFromList(&_list, &key, cmpKey);
//    printf("\nShowing list Reverse\n");
//    showListReverseFiltered(&_list, &key, showInt, cmpKey);
//    printf("\nShowing and clearing list reverse\n");
//    showAndClearListReverse(&_list, showInt);
//    printf("\nShowing and clearing list\n");
//    showAndClearList(&_list, showInt);
//    printf("\nShowing list\n");
//    showList(&_list, showInt);
//    printf("\nRemoving from list\n");
//    for(int i = 0; i < sizeof(vec)/sizeof(int); i ++){
//        if(removeLastFromList(&_list, &element, sizeof(int)) == 0)
//            break;
//        printf("%d ", element);
//    }

//    createBatch("datos1");
//    traverseAndRecordBinaryFileWithList("datos1", sizeof(tProduct),
//                                        cmpDateProviderId, insertSorted);
//    traverseBinaryFile("datos1", sizeof(tProduct), showIdExpDateProvider);
//    system("pause");
//    system("cls");
//    createBatch("datos2");
//    traverseAndRecordBinaryFileSortingList("datos2", sizeof(tProduct),
//                                           cmpDateProviderId, addToStartList);
//    traverseBinaryFile("datos2", sizeof(tProduct), showIdExpDateProvider);
//    printf("\nShowing and clearing list\n");
//    showAndClearList(&_list, showIdExpDateProvider);

    tList l;

    createList(&l);
    createBatch("products.dat");
    loadListWithMostExpensiveProducts(&l, 1, "products.dat",
                                      sizeof(tProduct), cmpPrice);

    showAndClearList(&l, showProduct);

    return 0;
}
