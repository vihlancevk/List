#include <stdio.h>
#include "../include/List.h"
#include "../include/UnitTests.h"

int main()
{
    ListErrorCode listError = LIST_NO_ERROR;

    UNIT_TEST_(ListInsertAfter, listError);

    return listError;
}
