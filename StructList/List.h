#ifndef LIST_H_
#define LIST_H_

#define DEBUG

#define IS_LIST_ERROR_(list, listError)   \
    do                                    \
    {                                     \
        listErrorIn = listError;          \
        if (listErrorIn != LIST_NO_ERROR) \
        {                                 \
            /*TODO SMTH*/                 \
            ListDtor(list);               \
            return listErrorIn;           \
        }                                 \
    } while(0)

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
    LIST_CONSTRUCTED_ERROR,
    LIST_DESTRUCTED_ERROR,
    LIST_DATA_CALLOC_ERROR,
    LIST_NEXT_CALLOC_ERROR,
    LIST_PREV_CALLOC_ERROR,
    LIST_USE_NOT_CONSTRUCTED,
    LIST_NO_FREE_PLACE,
    LIST_IS_EMPTY,
    LIST_HAVE_CYCLE,
    LIST_INSERT_UNCORRECT_PLACE,
    LIST_INSERT_BEFORE_UNCORRECT_USE,
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
    int *prev;
    size_t head;
    size_t tail;
    size_t free;
};

ListErrorCode GetListError(const List_t *list);

ListErrorCode ListCtor(List_t *list, const size_t capacity);

ListErrorCode ListDtor(List_t *list);

void ListDump(const List_t *list);

ListErrorCode ListInsertAfter(List_t *list, const structList_t elem, const size_t place);

ListErrorCode ListInsertBefore(List_t *list, const structList_t elem, const size_t place);

ListErrorCode ListRemove(List_t *list, structList_t *elem, const size_t place);

#endif // LIST_H_
