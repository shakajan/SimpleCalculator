### description
this is a module which includes calculator that calculates string integer expression.

### how to use
``` C

#include<stdio.h>

#include"Calculator.h"

int main()
{
    Calculator cal;
    calculatorInit(&cal);
    char buf[12412];
    printf("input formula: ");
    scanf("%[^\n]", buf);
    printf("%lld\n", calculate(&cal, buf));
    calculatorDestroy(&cal);
    return 0;
}

```

