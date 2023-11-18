#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int i, index = 0, totalAnggota = 0, jumlahAnggotaSpesial = 0, jumlahAnggotaBiasa = 0, jumlahAnggotaPerKelompok,
    metodeDistribusi;
    char anggota[1000], anggotaSpesial[1000][1000], anggotaBiasa[1000][1000], *anggotaKeseluruhan[2000];

    printf("Masukkan daftar anggota (enter dua kali untuk konfirmasi):\n");

    while (scanf("%[^\n]%*c", anggota) == 1) {
        strcpy(anggotaSpesial[totalAnggota], anggota);

        totalAnggota++;

        if (strchr(anggota, '$') != NULL) {
            strcpy(anggotaSpesial[jumlahAnggotaSpesial], anggota);
            jumlahAnggotaSpesial++;
        } else {
            strcpy(anggotaBiasa[jumlahAnggotaBiasa], anggota);
            jumlahAnggotaBiasa++;
        }
    }

    printf("Jumlah anggota: %d\n", totalAnggota);
    printf("Jumlah anggota spesial: %d\n", jumlahAnggotaSpesial);

    printf("\n");

    printf("Daftar anggota Biasa:\n");
    for (i = 0; i < jumlahAnggotaBiasa; i++) {
        printf("%s\n", anggotaBiasa[i]);
    }

    printf("\nDaftar anggota Spesial:\n");
    for (i = 0; i < jumlahAnggotaSpesial; i++) {
        printf("%s\n", anggotaSpesial[i]);
    }

    printf("\n");

    printf("Daftar anggota keseluruhan: \n");

    for (i = 0; i <= jumlahAnggotaBiasa && i <= jumlahAnggotaSpesial; i++) {
        anggotaKeseluruhan[index++] = anggotaBiasa[i];
        anggotaKeseluruhan[index++] = anggotaSpesial[i];
    }

    for (int i = 0; i < index; i++) {
        printf("%s\n", anggotaKeseluruhan[i]);
    }

    printf("\n");

    printf("Masukkan jumlah anggota pada setiap kelompok: ");

    clearBuffer();

    scanf("%d", &jumlahAnggotaPerKelompok);

    printf("\n");

    printf("Metode Distribusi:\n1. Semua anggota spesial dalam kelompok yang sama\n2. Hanya satu anggota spesial per kelompok\n3. Distribusi acak\n\nPilih antara 1 sampai 3: ");

    clearBuffer();

    scanf("%d", &metodeDistribusi);

    switch(metodeDistribusi) {
        case 1:
            printf("\nMetode Distribusi: Semua anggota spesial dalam kelompok yang sama\n\n");
            break;
        case 2:
            printf("\nMetode Distribusi: Hanya satu anggota spesial per kelompok\n\n");
            break;
        case 3:
            printf("\nMetode Distribusi: Distribusi acak\n\n");
            break;
        default:
            printf("\nMetode Distribusi: Distribusi acak\n\n");
            break;
    }

    return 0;
}