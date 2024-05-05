#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <libgen.h>

// Fungsi untuk mengekstrak nama file dari path
const char *extract_file_name(const char *path) {
    const char *file_name = strrchr(path, '/');
    if (file_name == NULL)
        return path; 
    else
        return file_name + 1; 
}

// Fungsi untuk menampilkan data yang disimpan di shared memory
void show_shared_data(key_t key) {
    int segment_id = shmget(key, 0, 0666); 
    char *shared_memory = (char *)shmat(segment_id, NULL, 0); 

    const char *file_name = NULL;
    if (key == 1233) {
        file_name = extract_file_name(shared_memory); // Ekstrak nama file dari shared memory
        printf("Type: Parking lot\nFile Name: %s\n", file_name); // Tampilkan jenis dan nama file
    } else if (key == 1235) {
        file_name = extract_file_name(shared_memory); // Ekstrak nama file dari shared memory
        printf("Type: Trash can\nFile Name: %s\n", file_name); // Tampilkan jenis dan nama file
    }

    printf("-------------------------------------\n"); 

    shmdt(shared_memory); 
}

// Fungsi untuk mencari item dengan peringkat tertinggi dalam data yang disimpan di shared memory
void find_highest_rating(key_t key) {
    float highest_rating = -1; 
    char item_name[100] = ""; 

    int segment_id = shmget(key, 0, 0666); 
    char *shared_memory = (char *)shmat(segment_id, NULL, 0); 
    char *data = strdup(shared_memory); 

    char *line = strtok(data, "\n"); 

    // Melakukan iterasi untuk setiap baris dalam data
    while (line != NULL) {
        char item[100];
        float rating;
        sscanf(line, "%[^,], %f", item, &rating); // Membaca item dan peringkat dari setiap baris

        if (rating > highest_rating) { // Jika peringkat item saat ini lebih tinggi dari peringkat tertinggi yang ditemukan sebelumnya
            highest_rating = rating; // Perbarui nilai peringkat tertinggi
            strcpy(item_name, item); // Salin nama item ke string
        }

        line = strtok(NULL, "\n"); // Pindah ke baris berikutnya
    }

    free(data);
    shmdt(shared_memory);

    printf("Highest Rating: %.1f - Item: %s\n", highest_rating, item_name); // Tampilkan peringkat tertinggi dan nama item
}

// Fungsi utama program
int main() {
    show_shared_data(1233); // Tampilkan data untuk kunci 1233 (parking lot)
    find_highest_rating(1234); // Cari item dengan peringkat tertinggi untuk kunci 1234
    printf("\n\n");
    show_shared_data(1235); // Tampilkan data untuk kunci 1235 (trash can)
    find_highest_rating(1236); // Cari item dengan peringkat tertinggi untuk kunci 1236

    return 0; // Program berjalan dengan sukses
}
