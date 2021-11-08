#ifndef UNIT_TESTS_H_
#define UNIT_TESTS_H_

#include "List.h"

#define UNIT_TEST_(name, listError)                    \
        do                                                 \
        {                                                  \
            listError = UnitTestFor##name();               \
            if (listError != LIST_NO_ERROR)                \
            {                                              \
                printf("Error in UnitTestFor%s\n", #name); \
                return listError;                          \
            }                                              \
        } while(0)

ListErrorCode UnitTestForListInsertAfter();

ListErrorCode UnitTestForListInsertBefore();

ListErrorCode UnitTestForListRemove();

ListErrorCode UnitTestForListDefine();

ListErrorCode UnitTestForListResizeUp();

ListErrorCode UnitTestForListConvertLogToPhysNum();

#endif // UNIT_TESTS_H_
