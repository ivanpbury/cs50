#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // Gets user's name and prints personalized hello message
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}