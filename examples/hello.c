#include <stdio.h>
#include "../common.h"

static unsigned int global_verbose_level = V_IMPORTANT_S;

int
main()
{
    VPRINT_PLAIN(V_IMPORTANT, "Hello, World\n");
    return 0;
}/* main */
