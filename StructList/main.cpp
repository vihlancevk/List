#include <stdio.h>
#include "List.h"

int main()
{
    List_t list = {};

    size_t capacity = 10;
    structElem_t elem = 0;
    int physNum = 0;
    ListErrorCode listErrorIn = LIST_NO_ERROR;

    IS_LIST_ERROR_(&list, ListCtor(&list, capacity));

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListInsertAfter(...)
    for (size_t i = 0; i < list.capacity - 3; i++)
    {
        IS_LIST_ERROR_(&list,ListInsertAfter(&list, &physNum, (i + 1) * 10, i));
    }

    IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, 80, 2));

    IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, 90, 2));

    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 4));

    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 8));
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListInsertBefor(...)
    /*IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, 10, list.tail));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, &physNum, 20, list.head));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, &physNum, 30, 1));*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListRemove(...)
    /*for (size_t i = 0; i < list.capacity - 3; i++)
    {
        IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, (i + 1) * 10, i));
    }
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 1));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, &physNum, elem, 2));
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 2));
    IS_LIST_ERROR_(&list, ListInsertBefore(&list, &physNum, elem, 3));
    IS_LIST_ERROR_(&list, ListRemove(&list, &elem, 3));
    IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, elem, 2));*/
    //-------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for define
    /*IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, &physNum, 10));
    IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, &physNum, 20));
    IS_LIST_ERROR_(&list, LIST_INSERT_AT_HEAD_(&list, &physNum, 30));
    IS_LIST_ERROR_(&list, LIST_REMOVE_AT_END_(&list, &elem));
    IS_LIST_ERROR_(&list, LIST_REMOVE_AT_HEAD_(&list, &elem));*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListResizeUp()
    /*for (int i = 1; i < 2 * capacity; i++)
    {
        IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, &physNum, i * 10));
    }*/
    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    //UNIT TEST for ListConvertLogToPhysNum()
    /*for (int i = 1; i < capacity + 1; i++)
    {
        IS_LIST_ERROR_(&list, LIST_INSERT_AT_END_(&list, &physNum, i * 10));
    }
    IS_LIST_ERROR_(&list, ListInsertAfter(&list, &physNum, 60, 2));
    IS_LIST_ERROR_(&list, ListConvertLogToPhysNum(&list));*/
    //--------------------------------------------------------------------------------

    IS_LIST_ERROR_(&list, ListDtor(&list));

    //IS_LIST_ERROR_(&list, ListDtor(&list));

    return LIST_NO_ERROR;
}
