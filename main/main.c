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
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[1000];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void randomDistribute(char *arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int main() {
    srand(time(NULL));
    int i, index = 0, totalAnggota = 0, jumlahAnggotaSpesial = 0, jumlahAnggotaBiasa = 0, jumlahAnggotaPerKelompok, metodeDistribusi;
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

    // Populate anggotaKeseluruhan with anggotaBiasa
    for (i = 0; i < jumlahAnggotaBiasa; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaBiasa[i];
    }

    // Populate anggotaKeseluruhan with anggotaSpesial
    for (i = 0; i < jumlahAnggotaSpesial; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaSpesial[i];
    }

    for (i = 0; i < jumlahAnggotaBiasa; i++) {
        data.anggotaBiasa[i];
    }

    for (i = 0; i < jumlahAnggotaSpesial; i++) {
        data.anggotaSpesial[i];
    }

    for (i = 0; i <= jumlahAnggotaBiasa && i <= jumlahAnggotaSpesial; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaBiasa[i];
        data.anggotaKeseluruhan[index++] = data.anggotaSpesial[i];
    }

    for (int i = 0; i < index; i++) {
        data.anggotaKeseluruhan[i];
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

            // Randomize non-special members
            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            printf("Kelompok 1:\n");
            for (i = 0; i < jumlahAnggotaSpesial; i++) {
                printf("%s\n", data.anggotaSpesial[i]);
            }
            printf("\n");

            int numGroups = jumlahAnggotaBiasa / jumlahAnggotaPerKelompok;
            int leftover = jumlahAnggotaBiasa % jumlahAnggotaPerKelompok;

            for (i = 0; i < numGroups; i++) {
                printf("Kelompok %d:\n", i + 2);
                for (int j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaBiasa[i * jumlahAnggotaPerKelompok + j]);
                }
                if (i == numGroups - 1 && leftover > 0) {
                    for (int j = 0; j < leftover; j++) {
                        printf("%s\n", data.anggotaBiasa[numGroups * jumlahAnggotaPerKelompok + j]);
                    }
                }
                printf("\n");
            }

            break;
        case 2:
            printf("\nMetode Distribusi = 2\n\n");

            // Randomize both special and non-special members
            randomize(data.anggotaSpesial, jumlahAnggotaSpesial);
            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            int totalGroups = (jumlahAnggotaBiasa + jumlahAnggotaPerKelompok - 2) / (jumlahAnggotaPerKelompok - 1);
            int specialIndex = 0;

            for (i = 0; i < totalGroups; i++) {
                printf("Kelompok %d:\n", i + 1);

                // Print non-special members
                for (int j = 0; j < jumlahAnggotaPerKelompok - 1; j++) {
                    int index = i * (jumlahAnggotaPerKelompok - 1) + j;
                    if (index < jumlahAnggotaBiasa) {
                        printf("%s\n", data.anggotaBiasa[index]);
                    }
                }

                // Print one special member if any left
                if (specialIndex < jumlahAnggotaSpesial) {
                    printf("%s\n", data.anggotaSpesial[specialIndex]);
                    specialIndex++;
                }

                // don't print \n if in the last group
                if (i != totalGroups - 1) {
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
            // Randomize all members
            randomDistribute(data.anggotaKeseluruhan, totalAnggota);

            // Distribute members into groups
            totalGroups = totalAnggota / jumlahAnggotaPerKelompok;
            leftover = totalAnggota % jumlahAnggotaPerKelompok;

            for (i = 0; i < totalGroups; i++) {
                printf("Kelompok %d:\n", i + 1);
                for (int j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaKeseluruhan[i * jumlahAnggotaPerKelompok + j]);
                }

                if (i != totalGroups - 1) {
                    printf("\n");
                }
            }

            // If there are leftover members, put them in the last group
            if (leftover > 0) {
                for (i = 0; i < leftover; i++) {
                    printf("%s\n", data.anggotaKeseluruhan[totalGroups * jumlahAnggotaPerKelompok + i]);
                }
            }
            break;
        default:
            printf("\nMetode Distribusi = 3\n\n");
            // Randomize all members
            randomDistribute(data.anggotaKeseluruhan, totalAnggota);

            // Distribute members into groups
            totalGroups = totalAnggota / jumlahAnggotaPerKelompok;
            leftover = totalAnggota % jumlahAnggotaPerKelompok;

            for (i = 0; i < totalGroups; i++) {
                printf("Kelompok %d:\n", i + 1);
                for (int j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaKeseluruhan[i * jumlahAnggotaPerKelompok + j]);
                }

                if (i != totalGroups - 1) {
                    printf("\n");
                }
            }

            // If there are leftover members, put them in the last group
            if (leftover > 0) {
                for (i = 0; i < leftover; i++) {
                    printf("%s\n", data.anggotaKeseluruhan[totalGroups * jumlahAnggotaPerKelompok + i]);
                }
            }
            break;
        }

        printf("\nAcak lagi? (y/n): ");
        clearBuffer();
        scanf("%c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}