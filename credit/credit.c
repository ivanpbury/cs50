#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get number
    long number = get_long("Number: ");
    string type;

    //Determine type of card
    if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
    {
        type = "AMEX";
    }
    else if (number / 100000000000000 > 50 && number / 100000000000000 < 56)
    {
        type = "MASTERCARD";
    }
    else if (number / 1000000000000000 == 4 || number / 1000000000000 == 4)
    {
        type = "VISA";
    }
    else
    {
        type = "INVALID";
    }

    //Determine if card is valid
    int first_sum = 0;
    int second_sum = 0;
    int product;

    while (number > 0)
    {
        first_sum += number % 10;
        number /= 10;
        product = (number % 10) * 2;
        if (product > 9)
        {
            second_sum += (product % 10) + (product / 10);
        }
        else
        {
            second_sum += product;
        }
        number /= 10;
    }
    int total = first_sum + second_sum;
    if (total % 10 != 0)
    {
        type = "INVALID";
    }
    printf("%s\n", type);
}