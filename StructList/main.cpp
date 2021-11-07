#include <stdio.h>
#include "List.h"

int main()
{
    List_t list = {};

    size_t capacity = 5;
    structElem_t elem = 0;
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

    //--------------------------------------------------------------------------------
    //UNIT TEST for define
    /*IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, 10));
    IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, 20));
    IS_LIST_ERROR_(&list, LIST_INSERT_AT_HEAD_(&list, 30));
    IS_LIST_ERROR_(&list, LIST_REMOVE_AT_END_(&list, &elem));
    IS_LIST_ERROR_(&list, LIST_REMOVE_AT_HEAD_(&list, &elem));*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListResizeUp()
    for (int i = 1; i < 2 * capacity; i++)
    {
        IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, i * 10));
    }
    //--------------------------------------------------------------------------------

    IS_LIST_ERROR_(&list, ListDtor(&list));

    //IS_LIST_ERROR_(&list, ListDtor(&list));

    return LIST_NO_ERROR;
}
