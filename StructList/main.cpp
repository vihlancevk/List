#include <stdio.h>
#include "List.h"
#include "UnitTests.h"

int main()
{
    ListErrorCode listError = LIST_NO_ERROR;

    UNIT_TEST_(ListResizeUp, listError);

    return listError;
}
