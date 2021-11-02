#include <stdio.h>
#include "List.h"

int main()
{
    List_t list = {};

    size_t capacity = 10;

    structList_t elem = 0;

    IS_LIST_ERROR_(ListCtor(&list, capacity));
    IS_LIST_ERROR_(ListInsert(&list, 1, list.tail));
    for (int i = 1; i < list.capacity - 1; i++)
    {
        IS_LIST_ERROR_(ListInsert(&list, i * 10, i));
    }

    IS_LIST_ERROR_(ListRemove(&list, &elem, list.head));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(ListRemove(&list, &elem, list.tail));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(ListRemove(&list, &elem, 5));
    printf("elem : %d\n", elem);

    IS_LIST_ERROR_(ListInsert(&list, elem, 4));

    return LIST_NO_ERROR;
}
