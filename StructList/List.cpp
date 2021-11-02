#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

#define DEBUG

const int LIST_ARRAY_NEXT_FREE = -1;
const size_t POISON = 1000 - 7;
const void *const ERR_PTR = (void*)666;

ListErrorCode GetListError(List_t *list)
{
    assert(list != nullptr);

    return LIST_NO_ERROR;
}

ListErrorCode ListCtor(List_t *list, size_t capacity)
{
    assert(list != nullptr);

    if (list->status != LIST_NOT_CONSTRUCTED)
    {
        return LIST_CONSTRUCTED_ERROR;
    }

    list->capacity = capacity + 1;
    list->size = 0;

    list->data = (structList_t*)calloc(list->capacity, sizeof(structList_t));
    if (list->data == nullptr)
    {
        return LIST_DATA_CALLOC_ERROR;
    }

    list->next = (int*)calloc(list->capacity, sizeof(int));
    if (list->next == nullptr)
    {
        return LIST_NEXT_CALLOC_ERROR;
    }
    for (size_t i = 1; i < list->capacity; i++)
    {
        list->next[i] = LIST_ARRAY_NEXT_FREE;
    }

    list->head = 0;
    list->tail = 0;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    return LIST_NO_ERROR;
}

ListErrorCode ListDtor(List_t *list)
{
    assert(list != nullptr);

    if (list->status != LIST_CONSTRUCTED)
    {
        return LIST_DESTRUCTED_ERROR;
    }

    list->status = LIST_DESTRUCTED;
    list->capacity = POISON;
    list->size = POISON;
    free(list->data);
    list->data = (structList_t*)ERR_PTR;
    free(list->next);
    list->next = (int*)ERR_PTR;
    list->head = POISON;
    list->tail = POISON;

    return LIST_NO_ERROR;
}

void ListDump(List_t *list)
{
    assert(list != nullptr);

    printf("--------------------------------------------------------------------------------");

    printf("size : %lu\n", list->size);
    printf("head : %lu\n", list->head);
    printf("tail : %lu\n", list->tail);

    size_t i = 0;

    printf("%4s : ", "i");
    for (i = 0; i < list->capacity; i++)
    {
        printf("%3lu ", i);
    }
    printf("\n\n");

    #define PRINT_LIST_ARRAY_(specifier, arrayName)        \
        printf("%4s : ", #arrayName);                      \
        for (i = 0; i < list->capacity; i++)               \
        {                                                  \
            printf("%3"#specifier" ", list->arrayName[i]); \
        }                                                  \
        printf("\n\n");

    PRINT_LIST_ARRAY_(d, data)
    PRINT_LIST_ARRAY_(d, next)

    printf("--------------------------------------------------------------------------------");
}

static size_t FindFreePosition(List_t *list)
{
    assert(list != nullptr);

    for (size_t i = 1; i < list->capacity; i++)
    {
        if (list->next[i] == LIST_ARRAY_NEXT_FREE)
        {
            return i;
        }
    }

    return 0;
}

ListErrorCode ListInsert(List_t *list, structList_t elem, size_t place)
{
    assert(list != nullptr);

    if (list->size >= list->capacity)
    {
        return LIST_IS_EMPTY;
    }

    if (list->next[place] == LIST_ARRAY_NEXT_FREE)
    {
        return LIST_INSERT_UNCORRECT_PLACE;
    }

    size_t free = FindFreePosition(list);
    if (free == 0)
    {
        return LIST_ARRAY_NEXT_NO_FREE_ELEMENT;
    }

    list->next[free] = list->next[place];
    if (list->size == 0)
    {
        list->head = free;
    }
    else
    {
        list->next[place] = free;
    }
    if (list->tail == place)
    {
        list->tail = free;
    }
    list->data[free] = elem;
    list->size = list->size + 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    return LIST_NO_ERROR;
}

static size_t FindPrevPosition(List_t *list, size_t place)
{
    assert(list != nullptr);

    size_t numElem = list->head;

    if (list->head == place)
    {
        return 0;
    }

    while (list->next[numElem] != place)
    {
        numElem = list->next[numElem];
    }

    return numElem;
}

ListErrorCode ListRemove(List_t *list, structList_t *elem, size_t place)
{
    assert(list != nullptr);
    assert(elem != nullptr);

    if (list->size <= 0)
    {
        return LIST_IS_EMPTY;
    }

    if (list->next[place] == LIST_ARRAY_NEXT_FREE)
    {
        return LIST_REMOVE_UNCORRECT_PLACE;
    }

    size_t prev = FindPrevPosition(list, place);
    printf("prev : %lu\n", prev);
    if (prev == 0)
    {
        *elem = list->data[place];
        list->data[place] = 0;
        list->size = list->size - 1;
        if (list->head == list->tail)
        {
            list->head = 0;
            list->tail = 0;
        }
        else
        {
            list->head = list->next[place];
        }
        list->next[place] = LIST_ARRAY_NEXT_FREE;
    }
    else
    {
        *elem = list->data[place];
        list->data[place] = 0;
        list->size = list->size - 1;
        list->next[prev] = list->next[place];
        list->next[place] = LIST_ARRAY_NEXT_FREE;
        if (list->tail == place)
        {
            list->tail = list->tail - 1;
        }
    }

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    return LIST_NO_ERROR;
}
