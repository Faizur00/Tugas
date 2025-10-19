#include <stdio.h>

int main(void) 
{
    int bilangan;

    printf("Masukkan bilangan: ");
    scanf("%d", &bilangan);

    if (bilangan > 0) {
        printf("Bilangan Positif\n");
    } else if (bilangan < 0) {
        printf("Bilangan Negatif\n");
    } else {
        printf("Bilangan Nol\n");
    }
    return 0;
}
