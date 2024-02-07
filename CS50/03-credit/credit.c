#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    float dollars = -1;
    while(dollars < 0)
    {
        dollars = get_float("Change owed: ");
        if (dollars == 0.01) return 1;
    }
    int coins = round(dollars * 100);
    int result = 0;
    while(coins != 0)
    {   
        int subCoins = 0;
        if(coins > 25 || coins == 25)
        {
            result = round(coins / 25);
            coins = coins - result * 25;
        }
        if(coins > 10 || coins == 10)
        {   
            subCoins = round(coins / 10);
            result = result + subCoins;
            coins = coins - subCoins * 10;
        }
        if(coins > 5 || coins == 5)
        {
            subCoins = round(coins / 5);
            result = result + round(coins / 5);
            coins = coins - subCoins * 5;
        }
        if(coins > 1 || coins == 1)
        {
            result = result + round(coins);
        }
        printf("%i\n", result);
        return 0;
    }
}

