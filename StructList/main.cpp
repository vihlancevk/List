#include <stdio.h>
#include "List.h"

int main()
{
    List_t list = {};

    size_t capacity = 5;
    structList_t elem = 0;
    ListErrorCode listErrorIn = LIST_NO_ERROR;

    IS_LIST_ERROR_(&list, ListCtor(&list, capacity));

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListInsertAfter(...)
    /*for (size_t i = 0; i < list.capacity - 3; i++)
    {
        IS_LIST_ERROR_(&list,ListInsertAfter(&list, (i + 1) * 10, i));
    }

    IS_LIST_ERROR_(&list, ListInsertAfter(&list, 40, 2));

    IS_LIST_ERROR_(&list, ListInsertAfter(&list, 50, 2));*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListInsertBefor(...)
    /*IS_LIST_ERROR_(&list, ListInsertAfter(&list, 10, list.tail));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, 20, list.head));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, 30, 1));*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListRemove(...)
    /*for (size_t i = 0; i < list.capacity - 3; i++)
    {
        IS_LIST_ERROR_(&list, ListInsertAfter(&list, (i + 1) * 10, i));
    }
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 1));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, elem, 2));
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 2));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, elem, 3));
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 3));
    IS_LIST_ERROR_(&list, ListInsertAfter(&list, elem, 2));*/
    //-------------------------------------------------------------------------------

    IS_LIST_ERROR_(&list, ListDtor(&list));

    //IS_LIST_ERROR_(&list, ListDtor(&list));

    return LIST_NO_ERROR;
}
