// #include <cs50.h>
#include <stdio.h>

int main(void)
{   
    int height = 0;
    while(height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }
    if(height == 1)
    {
        printf("#\n");
    } 
    else 
    {
        for(int i = 1; i < height + 1; i++) 
        {
            int spaces = height - i;
            for(int j = 1; j < height + 1; j++)
            {
                if (j < spaces + 1)
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
            }
            printf("\n");

        }
    }
}
