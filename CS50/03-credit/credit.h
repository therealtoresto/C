#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for a credit card number
    long long card_number = get_long_long("Number: ");

    // Validate the credit card number using the Luhn algorithm
    int sum = 0;
    bool should_double = false;
    for (long long i = card_number; i > 0; i /= 10)
    {
        int digit = i % 10;
        if (should_double)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = (digit % 10) + (digit / 10);
            }
        }
        sum += digit;
        should_double = !should_double;
    }
    bool is_valid = (sum % 10 == 0);

    // Check the length and starting digits of the credit card number to determine the type of card
    int length = 0;
    long long temp = card_number;
    while (temp > 0)
    {
        length++;
        temp /= 10;
    }
    int first_two_digits;
    int first_digit;
    if (length == 13)
    {
        first_digit = card_number / 10000000000000000;
    }
    else if (length == 15)
    {
        first_two_digits = card_number / 10000000000000;
    }
    else if (length == 16)
    {
        first_digit = card_number / 1000000000000000;
        first_two_digits = card_number / 100000000000000;
    }

    // Output the result to the user
    if (!is_valid)
    {
        printf("INVALID\n");
    }
    else if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

