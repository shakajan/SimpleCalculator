### description
this is a module which includes calculator that calculates string integer expression.

### how to use : source code, execution example
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

``` C
input formula: ( 1 + 2 - 3 * 4 ) / 3 + 4 - ( 3 - 2 ) + 9999 - 900 - 90 - 9
9000
```
