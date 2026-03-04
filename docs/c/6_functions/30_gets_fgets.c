#include <stdio.h>
#include <string.h>

int main(void) {
    char ad1[20], ad2[20];

    printf("Adınızı (gets ile) girin: ");
    gets(ad1);  //TEHLİKELİ — boyut kontrolü yok!

    printf("Adınızı (fgets ile) girin: ");
    fgets(ad2, sizeof(ad2), stdin);

    printf("\ngets sonucu : %s\n", ad1);
    printf("fgets sonucu: %s\n", ad2);

}