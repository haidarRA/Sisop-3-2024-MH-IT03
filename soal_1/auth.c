#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define DIRECTORY "new-data/"


void move_to_shared_memory(const char *filename, int key) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    // Mendapatkan ukuran file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Membuat shared memory segment
    int shmid = shmget(key, file_size, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error creating shared memory");
        fclose(file);
        return;
    }

    // Menempatkan data file ke dalam shared memory
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("Error attaching shared memory");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(shm_ptr, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        shmdt(shm_ptr);
        fclose(file);
        return;
    }

    shmdt(shm_ptr);
    fclose(file);
}

// Fungsi untuk memindahkan nama file ke shared memory
void move_filename_to_shared_memory(const char *filename, int key) {
    int shmid = shmget(key, strlen(filename) + 1, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error creating shared memory");
        return;
    }

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("Error attaching shared memory");
        return;
    }

    strcpy(shm_ptr, filename);
    shmdt(shm_ptr);
}

int main() {
    char dir_path[256];
    if (getcwd(dir_path, sizeof(dir_path)) == NULL) {
        perror("Error getting current directory");
        return 1;
    }
    strcat(dir_path, "/");
    strcat(dir_path, DIRECTORY);

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Hanya memproses file regular
            if (strstr(entry->d_name, "trashcan.csv") != NULL) {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s%s", dir_path, entry->d_name);
                move_filename_to_shared_memory(entry->d_name, 1235);
                move_to_shared_memory(filepath, 1236);
            } else if (strstr(entry->d_name, "parkinglot.csv") != NULL) {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s%s", dir_path, entry->d_name);
                move_filename_to_shared_memory(entry->d_name, 1233);
                move_to_shared_memory(filepath, 1234);
            } else {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s%s", dir_path, entry->d_name);
                remove(filepath);
            }
        }
    }
    closedir(dir);

    return 0;
}
