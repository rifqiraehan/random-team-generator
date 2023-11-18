/**
 * Random Team Generator
 *
 * Program ini menghasilkan kelompok acak berdasarkan masukan dari user. Program ini memungkinkan user untuk memasukkan daftar anggota kelompok, menentukan jumlah anggota per kelompok, dan memilih metode distribusi. Program ini kemudian secara acak mendistribusikan anggota kelompok ke setiap kelompok sesuai dengan metode distribusi yang dipilih.
 *
 * Program ini menggunakan sebuah struct yaitu AnggotaData untuk menyimpan anggota kelompok. Struct ini memiliki dua array, AnggotaSpesial dan AnggotaBiasa, untuk memisahkan anggota kelompok spesial dan biasa. Array anggotaKeseluruhan digunakan untuk menyimpan semua anggota kelompok dalam sebuah daftar gabungan.
 *
 * Program ini menyediakan tiga metode distribusi:
 * 1. Semua anggota spesial dalam kelompok yang sama: Metode ini mendistribusikan semua anggota kelompok spesial ke kelompok pertama dan mendistribusikan anggota biasa ke kelompok yang tersisa.
 * 2. Satu anggota spesial per kelompok: Metode ini mendistribusikan satu anggota kelompok spesial untuk setiap kelompok dan mendistribusikan anggota spesial dan biasa yang tersisa secara acak.
 * 3. Distribusi acak: Metode ini mendistribusikan semua anggota kelompok secara acak, termasuk anggota spesial dan biasa, ke semua kelompok.
 *
 * Program ini menggunakan fungsi randomize untuk mengacak urutan anggota kelompok dalam array anggotaSpesial dan anggotaBiasa. Fungsi randomDistribute digunakan untuk mengacak urutan anggota kelompok dalam array anggotaKeseluruhan.
 *
 * Setelah menghasilkan kelompok, program akan meminta user untuk memilih apakah ingin mengacak kelompok lagi atau keluar dari program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h> // digunakan untuk menghasilkan angka acak

// deklarasi struct AnggotaData
// menggunakan typedef sebagai alias dari struct, sehingga tidak perlu menuliskan struct lagi pada deklarasi variabel.
typedef struct {
    char anggota[1000];
    char anggotaSpesial[1000][1000]; // 1000 kolom untuk 1000 anggota dan 1000 baris untuk 1000 karakter per anggota
    char anggotaBiasa[1000][1000];
    char *anggotaKeseluruhan[2000];
} AnggotaData;

/*
clearBuffer() digunakan untuk membersihkan buffer pada saat input data dari user yang menggunakan scanf dan getchar (untuk menghindari bug). Buffer adalah tempat penyimpanan sementara yang digunakan untuk menyimpan data yang diinputkan oleh user.
*/

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// pengacakan dilakukan dengan menggunakan metode pengacakan Fisher-Yates Shuffle
/* randomize() digunakan untuk mengacak anggota kelompok pada metode distribusi pertama dan kedua */
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

// randomDistribute() digunakan untuk mengacak anggota kelompok pada metode distribusi ketiga
void randomDistribute(char *arr[], int n) {
    int i, j;
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    // membuat generator angka acak semu (pseudo-random number generator)
    srand(time(NULL));

    int i, j, index = 0, totalAnggota = 0, jumlahAnggotaSpesial = 0, jumlahAnggotaBiasa = 0, jumlahAnggotaPerKelompok, metodeDistribusi;
    AnggotaData data;
    char choice;

    printf("Masukkan daftar anggota (enter dua kali untuk konfirmasi):\n");

    /* menerima input daftar anggota dari user, ketika . */
    while (scanf("%[^\n]%*c", data.anggota) == 1) {
        strcpy(data.anggotaSpesial[totalAnggota], data.anggota);

        totalAnggota++;

        // Jika anggota mengandung karakter $, maka anggota tersebut adalah anggota spesial
        if (strchr(data.anggota, '$') != NULL) {
            strcpy(data.anggotaSpesial[jumlahAnggotaSpesial], data.anggota);
            jumlahAnggotaSpesial++;
        } else {
            strcpy(data.anggotaBiasa[jumlahAnggotaBiasa], data.anggota);
            jumlahAnggotaBiasa++;
        }
    }

    // Mengisi anggotaKeseluruhan dengan anggotaBiasa
    for (i = 0; i < jumlahAnggotaBiasa; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaBiasa[i];
    }

    // Mengisi anggotaKeseluruhan dengan anggotaSpesial
    for (i = 0; i < jumlahAnggotaSpesial; i++) {
        data.anggotaKeseluruhan[index++] = data.anggotaSpesial[i];
    }

    printf("Masukkan jumlah anggota pada setiap kelompok: ");

    clearBuffer();

    scanf("%d", &jumlahAnggotaPerKelompok);

    printf("\n");

    // Membersihkan layar
    system("cls");

    printf("Metode Distribusi:\n1. Semua anggota spesial dalam kelompok yang sama\n2. Hanya satu anggota spesial per kelompok\n3. Distribusi acak\n\nPilih antara 1 sampai 3: ");

    clearBuffer();

    scanf("%d", &metodeDistribusi);

    system("cls");

    // mengulangi program jika user memilih y atau Y
    do {
        system("cls");

        switch(metodeDistribusi) {
        case 1:
            printf("\nMetode Distribusi = 1\n\n");

            // melakukan pengacakan pada anggota biasa
            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            // karena semua anggota spesial ditempatkan pada kelompok pertama, maka tidak perlu diacak
            printf("Kelompok 1:\n");
            for (i = 0; i < jumlahAnggotaSpesial; i++) {
                printf("%s\n", data.anggotaSpesial[i]);
            }
            printf("\n");

            // menghitung jumlah kelompok selain kelompok pertama
            int jumlahKelompok = jumlahAnggotaBiasa / jumlahAnggotaPerKelompok;

            // menghitung sisa anggota. Sisa anggota terjadi ketika jumlah anggota (biasa) tidak habis dibagi dengan jumlah anggota per kelompok
            int anggotaSisa = jumlahAnggotaBiasa % jumlahAnggotaPerKelompok;

            // mencetak anggota biasa setiap kelompok
            for (i = 0; i < jumlahKelompok; i++) {
                printf("Kelompok %d:\n", i + 2);
                for (j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaBiasa[i * jumlahAnggotaPerKelompok + j]);
                }

                // jika sudah mencapai kelompok terakhir dan masih ada anggota sisa, maka anggota sisa akan dicetak pada kelompok terakhir
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

            // melakukan pengacakan pada anggota spesial dan anggota biasa
            randomize(data.anggotaSpesial, jumlahAnggotaSpesial);
            randomize(data.anggotaBiasa, jumlahAnggotaBiasa);

            // menghitung total kelompok
            int totalKelompok = (jumlahAnggotaBiasa + jumlahAnggotaPerKelompok - 2) / (jumlahAnggotaPerKelompok - 1);

            // specialIndex digunakan untuk mengakses anggota spesial
            int specialIndex = 0;

            // mencetak anggota pada setiap kelompok
            for (i = 0; i < totalKelompok; i++) {
                printf("Kelompok %d:\n", i + 1);

                // mencetak anggota biasa
                for (j = 0; j < jumlahAnggotaPerKelompok - 1; j++) {
                    int index = i * (jumlahAnggotaPerKelompok - 1) + j;
                    if (index < jumlahAnggotaBiasa) {
                        printf("%s\n", data.anggotaBiasa[index]);
                    }
                }

                // mencetak satu anggota spesial pada setiap kelompok
                if (specialIndex < jumlahAnggotaSpesial) {
                    printf("%s\n", data.anggotaSpesial[specialIndex]);
                    specialIndex++;
                }
                
                // mencetak baris kosong jika bukan kelompok terakhir
                if (i != totalKelompok - 1) {
                    printf("\n");
                }
            }

            // mencetak anggota spesial yang tersisa (jika ada) pada kelompok terakhir
            while (specialIndex < jumlahAnggotaSpesial) {
                printf("%s\n\n", data.anggotaSpesial[specialIndex]);
                specialIndex++;
            }

            break;
        case 3:
            printf("\nMetode Distribusi = 3\n\n");

            // melakukan pengacakan pada semua anggota
            randomDistribute(data.anggotaKeseluruhan, totalAnggota);

            // menghitung total kelompok
            totalKelompok = totalAnggota / jumlahAnggotaPerKelompok;

            // menghitung sisa anggota. Sisa anggota terjadi ketika jumlah anggota tidak habis dibagi dengan jumlah anggota per kelompok
            anggotaSisa = totalAnggota % jumlahAnggotaPerKelompok;

            // mencetak anggota pada setiap kelompok
            for (i = 0; i < totalKelompok; i++) {
                printf("Kelompok %d:\n", i + 1);
                for (j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaKeseluruhan[i * jumlahAnggotaPerKelompok + j]);
                }

                // mencetak baris kosong jika bukan kelompok terakhir
                if (i != totalKelompok - 1) {
                    printf("\n");
                }
            }

            // mencetak anggota sisa (jika ada) pada kelompok terakhir
            if (anggotaSisa > 0) {
                for (i = 0; i < anggotaSisa; i++) {
                    printf("%s\n", data.anggotaKeseluruhan[totalKelompok * jumlahAnggotaPerKelompok + i]);
                }
            }
            break;
        default:
            printf("\nMetode Distribusi = 3\n\n");

            // melakukan pengacakan pada semua anggota
            randomDistribute(data.anggotaKeseluruhan, totalAnggota);

            // menghitung total kelompok
            totalKelompok = totalAnggota / jumlahAnggotaPerKelompok;

            // menghitung sisa anggota. Sisa anggota terjadi ketika jumlah anggota tidak habis dibagi dengan jumlah anggota per kelompok
            anggotaSisa = totalAnggota % jumlahAnggotaPerKelompok;

            // mencetak anggota pada setiap kelompok
            for (i = 0; i < totalKelompok; i++) {
                printf("Kelompok %d:\n", i + 1);
                for (j = 0; j < jumlahAnggotaPerKelompok; j++) {
                    printf("%s\n", data.anggotaKeseluruhan[i * jumlahAnggotaPerKelompok + j]);
                }

                // mencetak baris kosong jika bukan kelompok terakhir
                if (i != totalKelompok - 1) {
                    printf("\n");
                }
            }

            // mencetak anggota sisa (jika ada) pada kelompok terakhir
            if (anggotaSisa > 0) {
                for (i = 0; i < anggotaSisa; i++) {
                    printf("%s\n", data.anggotaKeseluruhan[totalKelompok * jumlahAnggotaPerKelompok + i]);
                }
            }
            break;
        }

        // menanyakan apakah user ingin mengacak lagi
        printf("\nAcak lagi? (y/n): ");
        clearBuffer();
        scanf("%c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}