#include <stdio.h>

int a[3][4];


int main () {
    for(int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = i * 3 + j;
    
    printf("%d\n", (*(a+1))[2]);
    printf("%d\n", (a[1][2]));
    printf("%ld\n", ((a+1)-a));
}

