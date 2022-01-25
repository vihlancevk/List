#include <stdio.h>
#include "../libs/List.h"
#include "../libs/UnitTests.h"

int main()
{
    ListErrorCode listError = LIST_NO_ERROR;

    UNIT_TEST_(ListInsertAfter, listError);

    return listError;
}
