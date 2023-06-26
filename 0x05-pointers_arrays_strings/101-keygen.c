#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD_LENGTH 9

int main(void)
{
    char password[PASSWORD_LENGTH + 1];
    int i, sum;

    srand(time(NULL));

    for (i = 0, sum = 0; i < PASSWORD_LENGTH - 1; i++)
    {
        password[i] = rand() % 94 + 33;
        sum += password[i];
    }

    password[i] = 2772 - sum;
    password[PASSWORD_LENGTH] = '\0';

    printf("%s\n", password);

    return 0;
}

