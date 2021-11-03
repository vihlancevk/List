#include <stdio.h>
#include "List.h"

int main()
{
    List_t list = {};

    size_t capacity = 100;
    structList_t elem = 0;
    ListErrorCode listErrorIn = LIST_NO_ERROR;

    IS_LIST_ERROR_(&list, ListCtor(&list, capacity));
    IS_LIST_ERROR_(&list, ListInsert(&list, 1, list.tail));
    for (size_t i = 1; i < list.capacity - 1; i++)
    {
        IS_LIST_ERROR_(&list,ListInsert(&list, i * 10, i));
    }

    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, list.head));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, list.tail));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 5));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(&list, ListInsert(&list, elem, 4));

    IS_LIST_ERROR_(&list, ListDtor(&list));

    IS_LIST_ERROR_(&list, ListDtor(&list));

    return LIST_NO_ERROR;
}
