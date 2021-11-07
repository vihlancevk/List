#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

#define DEBUG

ListErrorCode listStatus = LIST_NO_ERROR;

#define ASSERT_OK_(list)                 \
    do                                   \
    {                                    \
        assert(list != nullptr);         \
        listStatus = GetListError(list); \
        if (listStatus != LIST_NO_ERROR) \
        {                                \
            return listStatus;           \
        }                                \
    } while(0)

const int LIST_PLACE_FREE = -1;
const int LIST_RESIZE_UP_COEFFICIENT = 2;
const size_t POISON = -(1000 - 7);
const void *const ERR_PTR = (void*)666;

static int IsListCycle(const List_t *list)
{
    assert(list != nullptr);

    int slow = list->head;
    int fast = list->head;

    while (fast != 0 && list->data[fast].next != 0)
    {
        slow = list->data[slow].next;
        fast = list->data[fast].next;
        fast = list->data[fast].next;

        if (slow == fast)
        {
            return 1;
        }
    }

    return 0;
}

ListErrorCode GetListError(const List_t *list)
{
    assert(list != nullptr);

    if (list->status != LIST_CONSTRUCTED)
    {
        return LIST_USE_NOT_CONSTRUCTED;
    }

    if (IsListCycle(list))
    {
        return LIST_HAVE_CYCLE;
    }

    return LIST_NO_ERROR;
}

ListErrorCode ListCtor(List_t *list, const size_t capacity)
{
    assert(list != nullptr);

    if (list->status != LIST_NOT_CONSTRUCTED)
    {
        return LIST_CONSTRUCTED_ERROR;
    }

    list->status = LIST_CONSTRUCTED;
    list->capacity = capacity + 1;
    list->size = 0;

    list->data = (ListData*)calloc(list->capacity, sizeof(ListData));
    if (list->data == nullptr)
    {
        return LIST_DATA_CALLOC_ERROR;
    }

    size_t  i = 0;
    for (i = 1; i < list->capacity - 1; i++)
    {
        list->data[i].next = i + 1;
    }

    for (i = 1; i < list->capacity; i++)
    {
        list->data[i].prev = LIST_PLACE_FREE;
    }

    list->head = 0;
    list->tail = 0;
    list->free = 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    return LIST_NO_ERROR;
}

ListErrorCode ListDtor(List_t *list)
{
    assert(list != nullptr);

    if (list->status == LIST_DESTRUCTED)
    {
        return LIST_DESTRUCTED_ERROR;
    }

    list->status = LIST_DESTRUCTED;
    list->capacity = POISON;
    list->size = POISON;
    free(list->data);
    list->data = (ListData*)ERR_PTR;
    list->head = POISON;
    list->tail = POISON;

    return LIST_NO_ERROR;
}

void ListDump(const List_t *list)
{
    assert(list != nullptr);

    printf("--------------------------------------------------------------------------------");

    printf("size : %lu\n\n", list->size);

    size_t i = 0;
    printf("%4s : ", "i");
    for (i = 0; i < list->capacity; i++)
    {
        printf("%3lu ", i);
    }
    printf("\n\n");

    #define PRINT_LIST_DATA_(specifier, arrayName)                  \
        do{                                                         \
            printf("%4s : ", #arrayName);                           \
            for (i = 0; i < list->capacity; i++)                    \
            {                                                       \
                printf("%3"#specifier" ", list->data[i].arrayName); \
            }                                                       \
            printf("\n\n");                                         \
        } while(0)

    PRINT_LIST_DATA_(d, elem);
    PRINT_LIST_DATA_(d, next);
    PRINT_LIST_DATA_(d, prev);

    printf("head : %lu\n", list->head);
    printf("tail : %lu\n", list->tail);
    printf("free : %lu\n", list->free);

    printf("--------------------------------------------------------------------------------");
}

static ListErrorCode ListResizeUp(List_t *list)
{
    assert(list != nullptr);

    list->capacity = list->capacity * LIST_RESIZE_UP_COEFFICIENT;
    ListData *data = (ListData*)realloc(list->data, list->capacity * sizeof(ListData));
    if (data == nullptr)
    {
        return LIST_RESIZE_UP_ERROR;
    }
    list->data = data;
    list->free = list->size + 1;

    size_t i = 0;
    for (i = list->free; i < list->capacity; i++)
    {
        list->data[i].elem = 0;
        list->data[i].prev = LIST_PLACE_FREE;
    }

    for (i = list->free; i < list->capacity - 1; i++)
    {
        list->data[i].next = i + 1;
    }

    return LIST_NO_ERROR;
}

ListErrorCode ListInsertAfter(List_t *list, const structElem_t elem, const size_t place)
{
    ASSERT_OK_(list);

    if (list->free == 0)
    {
        ListErrorCode listError = ListResizeUp(list);
        if (listError != LIST_NO_ERROR)
            return listError;
    }

    if (list->data[place].prev == LIST_PLACE_FREE)
    {
        return LIST_INSERT_UNCORRECT_PLACE;
    }

    size_t free = list->free;
    list->free = list->data[free].next;

    list->data[free].next = list->data[place].next;
    list->data[free].prev = place;
    if (list->size == 0)
    {
        list->head = free;
    }
    else
    {
        list->data[place].next = free;
    }

    if (list->tail == place)
    {
        list->tail = free;
    }
    else
    {
        list->data[list->data[free].next].prev = free;
    }
    list->data[free].elem = elem;
    list->size = list->size + 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}

ListErrorCode ListInsertBefore(List_t *list, const structElem_t elem, const size_t place)
{
    ASSERT_OK_(list);

    if (list->size == 0)
    {
        return LIST_INSERT_BEFORE_UNCORRECT_USE;
    }

    if (list->free == 0)
    {
        ListErrorCode listError = ListResizeUp(list);
        if (listError != LIST_NO_ERROR)
            return listError;
    }

    if (list->data[place].prev == LIST_PLACE_FREE)
    {
        return LIST_INSERT_UNCORRECT_PLACE;
    }

    size_t free = list->free;
    list->free = list->data[free].next;

    list->data[free].prev = list->data[place].prev;
    list->data[place].prev = free;
    list->data[free].next = place;
    if (list->head == place)
    {
        list->head = free;
    }
    else
    {
        list->data[list->data[free].prev].next = free;
    }
    list->data[free].elem = elem;
    list->size = list->size + 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}

ListErrorCode ListRemove(List_t *list, structElem_t *elem, size_t place)
{
    ASSERT_OK_(list);

    assert(elem != nullptr);

    if (list->size <= 0)
    {
        return LIST_IS_EMPTY;
    }

    if (list->data[place].prev == LIST_PLACE_FREE)
    {
        return LIST_REMOVE_UNCORRECT_PLACE;
    }

    size_t prev = list->data[place].prev;

    *elem = list->data[place].elem;
    list->data[place].elem = 0;
    if (prev == 0)
    {
        list->size = list->size - 1;
        list->data[list->data[place].next].prev = list->data[place].prev;
        if (list->head == list->tail)
        {
            list->head = 0;
            list->tail = 0;
        }
        else
        {
            list->head = list->data[place].next;
        }
    }
    else
    {
        list->size = list->size - 1;
        list->data[prev].next = list->data[place].next;
        if (list->tail == place)
        {
            list->tail = list->tail - 1;
        }
        else
        {
            list->data[list->data[place].next].prev = list->data[place].prev;
        }
    }

    list->data[place].next = list->free;
    list->data[place].prev = LIST_PLACE_FREE;
    list->free = place;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}
