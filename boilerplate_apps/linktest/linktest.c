#include <stdio.h>
#include <boilerplatelib.h>

int main()
{
    char* fromlib = boilerplate_get_helloworld();
    printf("From lib : %s", fromlib);
    return 0;
}