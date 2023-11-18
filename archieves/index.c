#include <stdio.h>
#include <string.h>

struct member {
    char name[100];
    int isSpecial;
};

int main(){

    struct member members[1000];

    int totalMember = 0, totalSpecialMember = 0;

    printf("Masukkan anggota (enter dua kali untuk konfirmasi):\n");

    // Membaca anggota dan menghentikan input jika enter dua kali
    while (fgets(members[totalMember].name, 100, stdin) != NULL) {
        // Menghapus karakter newline dari input
        members[totalMember].name[strcspn(members[totalMember].name, "\n")] = 0;

        // Menghentikan input jika enter dua kali
        if (members[totalMember].name[0] == '\0') {
            break;
        }

        // Menyimpan anggota spesial
        if (strchr(members[totalMember].name, '$') != NULL) {
            members[totalMember].isSpecial = 1;
            totalSpecialMember++;
        } else {
            members[totalMember].isSpecial = 0;
        }

        totalMember++;
    }

    printf("Jumlah anggota: %d\n", totalMember);
    printf("Jumlah anggota spesial: %d\n", totalSpecialMember);


    return 0;
}