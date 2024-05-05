#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <time.h>

int word_to_number(char *word) {
    if (strcmp(word, "satu") == 0) return 1;
    if (strcmp(word, "dua") == 0) return 2;
    if (strcmp(word, "tiga") == 0) return 3;
    if (strcmp(word, "empat") == 0) return 4;
    if (strcmp(word, "lima") == 0) return 5;
    if (strcmp(word, "enam") == 0) return 6;
    if (strcmp(word, "tujuh") == 0) return 7;
    if (strcmp(word, "delapan") == 0) return 8;
    if (strcmp(word, "sembilan") == 0) return 9;
    return -1; // Error
}

void number_to_text(int number, char *text) {
    char *ones[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    char *teens[] = {"sepuluh", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    char *tens[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

    if (number < 10) {
        strcpy(text, ones[number]);
    } else if (number < 20) {
        strcpy(text, teens[number - 10]);
    } else {
        int tens_digit = number / 10;
        int ones_digit = number % 10;
        sprintf(text, "%s %s", tens[tens_digit], ones[ones_digit]);
    }
}

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
    char input[50], word1[20], word2[20];
    int num1, num2, result;
    char result_word[200]; // Increased buffer size

    printf("Masukkan dua kata: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline
    sscanf(input, "%s %s", word1, word2);

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
        read(pipefd[0], &result_word, sizeof(result_word));
        
        if (result < 0) {
            printf("ERROR\n");
            write_to_log(operation, "ERROR");
            close(pipefd[0]);
            return 1;
        }

        printf("Hasil: %s\n", result_word);

        write_to_log(operation, result_word);

        close(pipefd[0]);
    } else { // Child process
        close(pipefd[0]); // Close read end

        if ((num1 = word_to_number(word1)) == -1 || (num2 = word_to_number(word2)) == -1) {
            printf("ERROR: Salah satu kata tidak valid.\n");
            write_to_log(operation, "ERROR: Salah satu kata tidak valid.");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        if (strcmp(operation, "-kali") == 0) {
            result = num1 * num2;
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_word, sizeof(result_word), "%s", text_result);
        } else if (strcmp(operation, "-tambah") == 0) {
            result = num1 + num2;
            char text_result[100];
            number_to_text(result, text_result);
            snprintf(result_word, sizeof(result_word), "%s", text_result);
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
            snprintf(result_word, sizeof(result_word), "%s", text_result);
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
            snprintf(result_word, sizeof(result_word), "%s", text_result);
        } else {
            printf("Operasi tidak valid.\n");
            write_to_log(operation, "ERROR: Operasi tidak valid.");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        write(pipefd[1], &result, sizeof(result));
        write(pipefd[1], &result_word, sizeof(result_word));

        close(pipefd[1]);
    }

    return 0;
}
