#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

// Fungsi untuk mendapatkan hanya nama file dari suatu path
const char *get_basename(const char *path) {
    const char *filename = strrchr(path, '/');
    if (filename == NULL)
        return path;
    else
        return filename + 1;
}

// Fungsi untuk membaca data dari shared memory berdasarkan kunci yang diberikan
char *read_shared_memory(int key) {
    // Mendapatkan ID shared memory menggunakan kunci
    int shmid = shmget(key, 0, 0666);
    // Melakukan kaitan (attach) shared memory ke ruang alamat proses
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    // Menyalin data dari shared memory ke string baru
    char *string = strdup(shm_ptr);
    // Melepaskan kaitan (detach) shared memory
    shmdt(shm_ptr);
    // Mengembalikan string yang berisi data yang dibaca dari shared memory
    return string;
}

// Fungsi untuk memperbarui path file dan mencatat perubahan tersebut ke dalam file log
void updatePathAndLog(char **path, const char *type) {
    char *token;
    const char search[] = "new-data";
    const char replacement[] = "microservices/database";

    // Mencari keberadaan string "new-data" dalam path file yang diberikan
    token = strstr(*path, search);

    // Jika ditemukan, mengganti "new-data" dengan "microservices/database" dalam path file
    if (token != NULL) {
        size_t length_before = token - *path;
        size_t length_after = strlen(token + strlen(search));
        char *new_path = (char *)malloc(length_before + strlen(replacement) + length_after + 1);
        strncpy(new_path, *path, length_before);
        new_path[length_before] = '\0';
        strcat(new_path, replacement);
        strcat(new_path, token + strlen(search));

        // Memindahkan file dari path lama ke path baru
        if (rename(*path, new_path) == 0) {
            // Jika pemindahan berhasil, membebaskan memori yang dialokasikan untuk path lama
            free(*path);
            // Menetapkan path baru
            *path = new_path;

            // Membuka file log dan menulis entri log yang mencatat perubahan path beserta jenisnya
            FILE *log_file = fopen("database/db.log", "a");
            if (log_file != NULL) {
                time_t raw_time;
                struct tm *time_info;
                time(&raw_time);
                time_info = localtime(&raw_time);

                fprintf(log_file, "[%02d/%02d/%04d %02d:%02d:%02d] [%s] [%s]\n",
                        time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
                        time_info->tm_hour, time_info->tm_min, time_info->tm_sec, type, get_basename(*path));

                fclose(log_file);
            }
        }
    }
}

int main() {
    int keys[] = {1233, 1235};
    const char *types[] = {"Parking Lot", "Trash Can"};

    for (int i = 0; i < 2; ++i) {
        char *string = read_shared_memory(keys[i]);
        char *oldstring = read_shared_memory(keys[i]);
        updatePathAndLog(&string, types[i]);
        free(oldstring);
    }

    return 0;
}
