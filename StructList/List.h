#ifndef LIST_H_
#define LIST_H_

#define DEBUG

#define IS_LIST_ERROR_(listError)   \
    if (listError != LIST_NO_ERROR) \
    {                               \
        return listError;           \
    }

typedef int structList_t;

enum ListStatus
{
    LIST_NOT_CONSTRUCTED,
    LIST_CONSTRUCTED,
    LIST_DESTRUCTED,
};

enum ListErrorCode
{
    LIST_NO_ERROR,
    LIST_ERROR,
    LIST_CONSTRUCTED_ERROR,
    LIST_DESTRUCTED_ERROR,
    LIST_DATA_CALLOC_ERROR,
    LIST_NEXT_CALLOC_ERROR,
    LIST_CAPACITY_LESS_SIZE,
    LIST_IS_EMPTY,
    LIST_INSERT_UNCORRECT_PLACE,
    LIST_REMOVE_UNCORRECT_PLACE,
    LIST_ARRAY_NEXT_NO_FREE_ELEMENT,
};

struct List_t
{
    ListStatus status;
    size_t capacity;
    size_t size;
    structList_t *data;
    int *next;
    size_t head;
    size_t tail;
};

ListErrorCode GetListError(List_t *list);

ListErrorCode ListCtor(List_t *list, size_t capacity);

ListErrorCode ListDtor(List_t *list);

void ListDump(List_t *list);

ListErrorCode ListInsert(List_t *list, structList_t elem, size_t place);

ListErrorCode ListRemove(List_t *list, structList_t *elem, size_t place);

#endif // LIST_H_
