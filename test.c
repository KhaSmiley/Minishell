#include <stdio.h>
#include <string.h>

int main()
{
    char var[] = "U";
    if (strncmp("USER=kboulkri", var, strlen(var)) == 0)
    {
        printf("Ok");
        return (1);
    }
    printf("Nok");
    return (0);
}