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

typedef int structElem_t;

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
    LIST_CONVERT_LOG_TO_PHYS_NUM_ERROR,
    LIST_DUMP_OPEN_LOG_FILE_ERROR,
    LIST_DATA_CALLOC_ERROR,
    LIST_USE_NOT_CONSTRUCTED,
    LIST_RESIZE_UP_ERROR,
    LIST_IS_EMPTY,
    LIST_HAVE_CYCLE,
    LIST_INSERT_UNCORRECT_PLACE,
    LIST_INSERT_BEFORE_UNCORRECT_USE,
    LIST_REMOVE_UNCORRECT_PLACE,
    LIST_ARRAY_NEXT_NO_freePlace_ELEMENT,
};

struct ListData
{
    structElem_t elem;
    int next;
    int prev;
};

struct List_t
{
    ListStatus status;
    int isSorted;
    size_t capacity;
    size_t size;
    ListData *data;
    size_t head;
    size_t tail;
    size_t freePlace;
};

ListErrorCode GetListError(const List_t *list);

ListErrorCode ListCtor(List_t *list, const size_t capacity);

ListErrorCode ListDtor(List_t *list);

ListErrorCode ListDump(const List_t *list);

ListErrorCode ListConvertLogToPhysNum(List_t *list);

ListErrorCode ListInsertAfter(List_t *list, int *physNum, const structElem_t elem, const size_t place);

#define LIST_INSERT_AT_END_(list, physNum, elem) \
    ListInsertAfter(list, physNum, elem, (*list).tail)

ListErrorCode ListInsertBefore(List_t *list, int *physNum, const structElem_t elem, const size_t place);

#define LIST_INSERT_AT_HEAD_(list, physNum, elem) \
    ListInsertBefore(list, physNum, elem, (*list).head)

ListErrorCode ListRemove(List_t *list, structElem_t *elem, const size_t place);

#define LIST_REMOVE_AT_END_(list, elem) \
    ListRemove(list, elem, (*list).tail)

#define LIST_REMOVE_AT_HEAD_(list, elem) \
    ListRemove(list, elem, (*list).head)

#endif // LIST_H_
