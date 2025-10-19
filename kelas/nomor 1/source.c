#include <stdio.h>
#include <string.h>

#define NOMOR_LAYANAN 108
#define SIBUK 0

int main() {
    int nomor_layanan = NOMOR_LAYANAN;
    int status_layanan = 1; 
    char nama[100], alamat[100];
    char *alamat_terdaftar[] = {"rumah1", "rumah2", "rumah3", "rumah4", "rumah5"};
    int nomor_telepon_terdaftar[] = {123456789, 987654321, 555666777, 888999000, 111222333};
    int nomor_telepon = -1;

    
    printf("Menghubungi nomor layanan %d...\n", nomor_layanan);

    if (status_layanan != SIBUK) {
        printf("Masukkan nama: ");
        scanf("%s", nama);
        printf("Masukkan alamat: ");
        scanf("%s", alamat);

        for (int i = 0; i < 5; i++) {
            if (strcmp(alamat, alamat_terdaftar[i]) == 0) {
                nomor_telepon = nomor_telepon_terdaftar[i];
                break;
            }
        }

        if (nomor_telepon != -1) {
            printf("Nomor telepon untuk alamat %s adalah %d\n", alamat, nomor_telepon);
        } else {
            printf("Alamat %s tidak memiliki nomor telepon\n", alamat);
        }
    } else {
        printf("Layanan sibuk, silakan coba lagi nanti.\n");
    }

    printf("Sambungan diputus.\n");
    return 0;
}