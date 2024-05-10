#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Fungsi untuk mengonversi string menjadi angka
int string_to_number(char *str) {
    if (strcmp(str, "satu") == 0) return 1;
    if (strcmp(str, "dua") == 0) return 2;
    if (strcmp(str, "tiga") == 0) return 3;
    if (strcmp(str, "empat") == 0) return 4;
    if (strcmp(str, "lima") == 0) return 5;
    if (strcmp(str, "enam") == 0) return 6;
    if (strcmp(str, "tujuh") == 0) return 7;
    if (strcmp(str, "delapan") == 0) return 8;
    if (strcmp(str, "sembilan") == 0) return 9;
    return -1; // Error
}

// Fungsi untuk menangani input yang tidak valid
int handle_invalid_input(char *num_str) {
    if (strcmp(num_str, "angka_1") == 0) return 1;
    if (strcmp(num_str, "angka_2") == 0) return 2;
    if (strcmp(num_str, "angka_3") == 0) return 3;
    if (strcmp(num_str, "angka_4") == 0) return 4;
    if (strcmp(num_str, "angka_5") == 0) return 5;
    if (strcmp(num_str, "angka_6") == 0) return 6;
    if (strcmp(num_str, "angka_7") == 0) return 7;
    if (strcmp(num_str, "angka_8") == 0) return 8;
    if (strcmp(num_str, "angka_9") == 0) return 9;
    return -1; // Error
}

// Fungsi untuk mengonversi angka menjadi teks
void number_to_text(int number, char *text) {
    // Array of strings untuk masing-masing angka
    char *ones[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    char *teens[] = {"sepuluh", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    char *tens[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

    // Kasus khusus jika angka dibawah 10
    if (number < 10) {
        strcpy(text, ones[number]);
    } 
    // Kasus khusus untuk angka 10 sampai 19
    else if (number < 20) {
        strcpy(text, teens[number - 10]);
    } 
    // Kasus umum
    else {
        int tens_digit = number / 10;
        int ones_digit = number % 10;
        if (ones_digit == 0) {
            sprintf(text, "%s", tens[tens_digit]);
        } else {
            sprintf(text, "%s dan %s", tens[tens_digit], ones[ones_digit]);
        }
    }
}

// Fungsi untuk menulis ke dalam log
void write_to_log(char *type, char *message) {
    FILE *fptr;
    fptr = fopen("histori.log", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    time_t current_time;
    struct tm *time_info;
    char timeString[40];
    
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%d/%m/%y %H:%M:%S", time_info);
    
    fprintf(fptr, "[%s] [%s] %s\n", timeString, type, message);
    fclose(fptr);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <operation>\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];
    char input[50], num1_str[20], num2_str[20];
    int num1, num2, result;
    char result_text[200];

    printf("Masukkan dua angka: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline
    sscanf(input, "%s %s", num1_str, num2_str);

    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[1]); // Close write end

        read(pipefd[0], &result, sizeof(result));
        read(pipefd[0], &result_text, sizeof(result_text));
        
        if (result < 0) {
            printf("ERROR\n");
            write_to_log(operation, "ERROR");
            close(pipefd[0]);
            return 1;
        }

        printf("Hasil: %s\n", result_text);

        write_to_log(operation, result_text);

        close(pipefd[0]);
    } else { // Child process
        close(pipefd[0]); // Close read end

        // Konversi string ke angka
        if ((num1 = string_to_number(num1_str)) == -1 || (num2 = string_to_number(num2_str)) == -1) {
            num1 = handle_invalid_input(num1_str);
            num2 = handle_invalid_input(num2_str);
            if (num1 == -1 || num2 == -1) {
                printf("ERROR: Salah satu angka tidak valid.\n");
                write_to_log(operation, "ERROR: Salah satu angka tidak valid.");
                close(pipefd[1]);
                exit(EXIT_FAILURE);
            }
        }

        // Lakukan operasi matematika sesuai argumen yang diberikan
        if (strcmp(operation, "-kali") == 0) {
            result = num1 * num2;
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_text, sizeof(result_text), "hasil perkalian %s dan %s adalah %s.", num1_str, num2_str, text_result);
        } else if (strcmp(operation, "-tambah") == 0) {
            result = num1 + num2;
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_text, sizeof(result_text), "hasil penjumlahan %s dan %s adalah %s.", num1_str, num2_str, text_result);
        } else if (strcmp(operation, "-kurang") == 0) {
            result = num1 - num2;
            if (result < 0) {
                printf("ERROR\n");
                write_to_log(operation, "ERROR: Hasil pengurangan negatif.");
                close(pipefd[1]);
                exit(EXIT_FAILURE);
            }
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_text, sizeof(result_text), "hasil pengurangan %s dan %s adalah %s.", num1_str, num2_str, text_result);
        } else if (strcmp(operation, "-bagi") == 0) {
            if (num2 == 0) {
                printf("ERROR: Pembagian oleh nol.\n");
                write_to_log(operation, "ERROR: Pembagian oleh nol.");
                close(pipefd[1]);
                exit(EXIT_FAILURE);
            }
            result = num1 / num2;
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_text, sizeof(result_text), "hasil pembagian %s dan %s adalah %s.", num1_str, num2_str, text_result);
        } else {
            printf("Operasi tidak valid.\n");
            write_to_log(operation, "ERROR: Operasi tidak valid.");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        // Kirim hasil operasi ke parent process
        write(pipefd[1], &result, sizeof(result));
        write(pipefd[1], &result_text, sizeof(result_text));

        close(pipefd[1]);
    }

    return 0;
}
