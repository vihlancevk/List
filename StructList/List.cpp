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
const size_t POISON = -(1000 - 7);
const void *const ERR_PTR = (void*)666;

static int IsListCycle(const List_t *list)
{
    assert(list != nullptr);

    int slow = list->head;
    int fast = list->head;

    while (fast != 0 && list->next[fast] != 0)
    {
        slow = list->next[slow];
        fast = list->next[fast];
        fast = list->next[fast];

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

    size_t  i = 0;
    for (i = 1; i < list->capacity - 1; i++)
    {
        list->next[i] = i + 1;
    }

    list->prev = (int*)calloc(list->capacity, sizeof(int));
    if (list->prev == nullptr)
    {
        return LIST_PREV_CALLOC_ERROR;
    }

    for (i = 1; i < list->capacity; i++)
    {
        list->prev[i] = LIST_PLACE_FREE;
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

    #define FREE_LIST_ARRAY_(type, name)     \
        do                                   \
        {                                    \
                free(list->name);            \
                list->name = (type*)ERR_PTR; \
        }while (0)

    list->status = LIST_DESTRUCTED;
    list->capacity = POISON;
    list->size = POISON;
    FREE_LIST_ARRAY_(structList_t, data);
    FREE_LIST_ARRAY_(int, next);
    FREE_LIST_ARRAY_(int, prev);
    list->prev = (int*)ERR_PTR;
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

    #define PRINT_LIST_ARRAY_(specifier, arrayName)            \
        do{                                                    \
            printf("%4s : ", #arrayName);                      \
            for (i = 0; i < list->capacity; i++)               \
            {                                                  \
                printf("%3"#specifier" ", list->arrayName[i]); \
            }                                                  \
            printf("\n\n");                                    \
        } while(0)

    PRINT_LIST_ARRAY_(d, data);
    PRINT_LIST_ARRAY_(d, next);
    PRINT_LIST_ARRAY_(d, prev);

    printf("head : %lu\n", list->head);
    printf("tail : %lu\n", list->tail);
    printf("free : %lu\n", list->free);

    printf("--------------------------------------------------------------------------------");
}

ListErrorCode ListInsertAfter(List_t *list, const structList_t elem, const size_t place)
{
    ASSERT_OK_(list);

    if (list->free == 0)
    {
        return LIST_NO_FREE_PLACE;
    }

    if (list->prev[place] == LIST_PLACE_FREE)
    {
        return LIST_INSERT_UNCORRECT_PLACE;
    }

    size_t free = list->free;
    list->free = list->next[free];

    list->next[free] = list->next[place];
    list->prev[free] = place;
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
    else
    {
        list->prev[list->next[free]] = free;
    }
    list->data[free] = elem;
    list->size = list->size + 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}

ListErrorCode ListInsertBefore(List_t *list, const structList_t elem, const size_t place)
{
    ASSERT_OK_(list);

    if (list->size == 0)
    {
        return LIST_INSERT_BEFORE_UNCORRECT_USE;
    }

    if (list->free == 0)
    {
        return LIST_NO_FREE_PLACE;
    }

    if (list->prev[place] == LIST_PLACE_FREE)
    {
        return LIST_INSERT_UNCORRECT_PLACE;
    }

    size_t free = list->free;
    list->free = list->next[free];

    list->prev[free] = list->prev[place];
    list->prev[place] = free;
    list->next[free] = place;
    if (list->head == place)
    {
        list->head = free;
    }
    else
    {
        list->next[list->prev[free]] = free;
    }
    list->data[free] = elem;
    list->size = list->size + 1;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}

ListErrorCode ListRemove(List_t *list, structList_t *elem, size_t place)
{
    ASSERT_OK_(list);

    assert(elem != nullptr);

    if (list->size <= 0)
    {
        return LIST_IS_EMPTY;
    }

    if (list->prev[place] == LIST_PLACE_FREE)
    {
        return LIST_REMOVE_UNCORRECT_PLACE;
    }

    size_t prev = list->prev[place];
    printf("prev : %lu\n", prev);
    if (prev == 0)
    {
        *elem = list->data[place];
        list->data[place] = 0;
        list->size = list->size - 1;
        list->prev[list->next[place]] = list->prev[place];
        if (list->head == list->tail)
        {
            list->head = 0;
            list->tail = 0;
        }
        else
        {
            list->head = list->next[place];
        }
    }
    else
    {
        *elem = list->data[place];
        list->data[place] = 0;
        list->size = list->size - 1;
        list->next[prev] = list->next[place];
        if (list->tail == place)
        {
            list->tail = list->tail - 1;
        }
        else
        {
            list->prev[list->next[place]] = list->prev[place];
        }
    }

    list->next[place] = list->free;
    list->prev[place] = LIST_PLACE_FREE;
    list->free = place;

    #ifdef DEBUG
        ListDump(list);
    #endif // DEBUG

    ASSERT_OK_(list);

    return LIST_NO_ERROR;
}
