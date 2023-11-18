#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char anggota[1000], anggotaSpesial[1000][1000], anggotaBiasa[1000][1000];
    int totalAnggota = 0, jumlahAnggotaSpesial = 0, jumlahAnggotaBiasa = 0;

    printf("Masukkan daftar anggota (enter dua kali untuk konfirmasi):\n");

    // Membaca anggota dan menghentikan input jika enter dua kali
    while (scanf("%[^\n]%*c", anggota) == 1) {
        // menyimpan anggota spesial
        strcpy(anggotaSpesial[totalAnggota], anggota);

        totalAnggota++;

        // Menghitung jumlah anggota spesial
        if (strchr(anggota, '$') != NULL) {
            strcpy(anggotaSpesial[jumlahAnggotaSpesial], anggota);
            jumlahAnggotaSpesial++;
        } else {
            strcpy(anggotaBiasa[jumlahAnggotaBiasa], anggota);
            jumlahAnggotaBiasa++;
        }

    }

    // Menampilkan jumlah anggota
    printf("Jumlah anggota: %d\n", totalAnggota);
    printf("Jumlah anggota spesial: %d\n", jumlahAnggotaSpesial);

    system("cls");

    char nama[1000];
    printf("Masukkan nama anda: ");

    // Membersihkan newline di buffer sebelum membaca nama
    clearBuffer();

    fgets(nama, sizeof(nama), stdin);

    printf("Nama anda adalah %s", nama);
    printf("Jumlah anggota: %d\n", totalAnggota);
    printf("Jumlah anggota spesial: %d\n", jumlahAnggotaSpesial);

    return 0;
}
