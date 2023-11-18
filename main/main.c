#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char anggota[1000];
    char anggotaSpesial[1000][1000];
    char anggotaBiasa[1000][1000];
    char *anggotaKeseluruhan[2000];
} AnggotaData;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void randomize(char arr[1000][1000], int n) {
    int i, j;
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        char temp[1000];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void randomDistribute(char *arr[], int n) {
    int i, j;
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void distributeMethod3AndDefault(char *arr[], int totalAnggota, int jumlahAnggotaPerKelompok) {
    randomDistribute(arr, totalAnggota);

    int totalKelompok = totalAnggota / jumlahAnggotaPerKelompok;

    int anggotaSisa = totalAnggota % jumlahAnggotaPerKelompok;

    for (int i = 0; i < totalKelompok; i++) {
        printf("Kelompok %d:\n", i + 1);
        for (int j = 0; j < jumlahAnggotaPerKelompok; j++) {
            printf("%s\n", arr[i * jumlahAnggotaPerKelompok + j]);
        }

        if (i != totalKelompok - 1) {
            printf("\n");
        }
    }

    if (anggotaSisa > 0) {
        for (int i = 0; i < anggotaSisa; i++) {
            printf("%s\n", arr[totalKelompok * jumlahAnggotaPerKelompok + i]);
        }
    }
}

int main() {
    srand(time(NULL));

    int i, j, index = 0, totalAnggota = 0, jumlahAnggotaSpesial = 0, jumlahAnggotaBiasa = 0, jumlahAnggotaPerKelompok, metodeDistribusi;
    AnggotaData data;
    char choice;

    printf("Masukkan daftar anggota (enter dua kali untuk konfirmasi):\n");

    while (scanf("%[^\n]%*c", data.anggota) == 1) {
        strcpy(data.anggotaSpesial[totalAnggota], data.anggota);

        totalAnggota++;

        if (strchr(data.anggota, '$') != NULL) {
            strcpy(data.anggotaSpesial[jumlahAnggotaSpesial], data.anggota);
            jumlahAnggotaSpesial++;
        } else {
            strcpy(data.anggotaBiasa[jumlahAnggotaBiasa], data.anggota);
            jumlahAnggotaBiasa++;
        }
    }

    for (i = 0; i < jumlahAnggotaBiasa; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaBiasa[i];
    }

    for (i = 0; i < jumlahAnggotaSpesial; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaSpesial[i];
    }

    printf("Masukkan jumlah anggota pada setiap kelompok: ");

    clearBuffer();

    scanf("%d", &jumlahAnggotaPerKelompok);

    printf("\n");

    system("cls");

    printf("Metode Distribusi:\n1. Semua anggota spesial dalam kelompok yang sama\n2. Hanya satu anggota spesial per kelompok\n3. Distribusi acak\n\nPilih antara 1 sampai 3: ");

    clearBuffer();

    scanf("%d", &metodeDistribusi);

    system("cls");

    do {
        system("cls");

        switch(metodeDistribusi) {
        case 1:
            printf("\nMetode Distribusi = 1\n\n");

            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            printf("Kelompok 1:\n");
            for (i = 0; i < jumlahAnggotaSpesial; i++) {
                printf("%s\n", data.anggotaSpesial[i]);
            }
            printf("\n");

            int jumlahKelompok = jumlahAnggotaBiasa / jumlahAnggotaPerKelompok;
            int anggotaSisa = jumlahAnggotaBiasa % jumlahAnggotaPerKelompok;

            for (i = 0; i < jumlahKelompok; i++) {
                printf("Kelompok %d:\n", i + 2);
                for (j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaBiasa[i * jumlahAnggotaPerKelompok + j]);
                }

                if (i == jumlahKelompok - 1 && anggotaSisa > 0) {
                    for (j = 0; j < anggotaSisa; j++) {
                        printf("%s\n", data.anggotaBiasa[jumlahKelompok * jumlahAnggotaPerKelompok + j]);
                    }
                }
                printf("\n");
            }

            break;
        case 2:
            printf("\nMetode Distribusi = 2\n\n");

            randomize(data.anggotaSpesial, jumlahAnggotaSpesial);
            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            int totalKelompok = (jumlahAnggotaBiasa + jumlahAnggotaPerKelompok - 2) / (jumlahAnggotaPerKelompok - 1);

            int specialIndex = 0;

            for (i = 0; i < totalKelompok; i++) {
                printf("Kelompok %d:\n", i + 1);

                for (j = 0; j < jumlahAnggotaPerKelompok - 1; j++) {
                    int index = i * (jumlahAnggotaPerKelompok - 1) + j;
                    if (index < jumlahAnggotaBiasa) {
                        printf("%s\n", data.anggotaBiasa[index]);
                    }
                }

                if (specialIndex < jumlahAnggotaSpesial) {
                    printf("%s\n", data.anggotaSpesial[specialIndex]);
                    specialIndex++;
                }

                if (i != totalKelompok - 1) {
                    printf("\n");
                }
            }

            while (specialIndex < jumlahAnggotaSpesial) {
                printf("%s\n\n", data.anggotaSpesial[specialIndex]);
                specialIndex++;
            }

            break;
        case 3:
            printf("\nMetode Distribusi = 3\n\n");

            distributeMethod3AndDefault(data.anggotaKeseluruhan, totalAnggota, jumlahAnggotaPerKelompok);

            break;
        default:
            printf("\nMetode Distribusi = 3\n\n");

            distributeMethod3AndDefault(data.anggotaKeseluruhan, totalAnggota, jumlahAnggotaPerKelompok);

            break;
        }

        printf("\nAcak lagi? (y/n): ");
        clearBuffer();
        scanf("%c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}