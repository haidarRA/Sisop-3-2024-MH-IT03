#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include <libgen.h>

#define PORT 8085
#define BUFFER_SIZE 1024

char* tireChange(char* N);
char* gap(float N);
char* tire(int N);
int isFloat(char* N);
int isPercent(char* N);
char* fuel(char* N);

char* getPath() {
    static char path[200];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1) {
        path[len] = '\0';
        return dirname(path);
    } else {
        perror("Error getting executable path");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char command[50], info[50], result[100];
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid, sid;        

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
      exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        while(1) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            int bytes_read = read(new_socket, command, sizeof(command));
            if (bytes_read <= 0) {
                printf("Invalid data received from client\n");
                close(new_socket);
                continue;
            }

            bytes_read = read(new_socket, info, sizeof(info));
            if (bytes_read <= 0) {
                printf("Invalid data received from client\n");
                close(new_socket);
                continue;
            }

	    int iInfo;
	    int isFuel = 0;
	    float fInfo;
/*
    	    char logLoc[100];
    	    char* realLoc;
/*
    	    realLoc = getcwd(logLoc, sizeof(logLoc));
    	    if(realLoc == NULL) {
    		perror("Failed to get path");
    		exit(EXIT_FAILURE);
    	    }
    	    strcat(realLoc, "/race.log");
*/	  

	    char* logPath = getPath();

	    char realLog[200];
	    snprintf(realLog, 200, "%s/race.log", logPath);
//	    printf("%s\n", logFilePath);  
    	    
            if(strcmp(command, "Gap") == 0) {
                fInfo = atof(info);
                strcpy(result, gap(fInfo));
            }
            else if(strcmp(command, "Fuel") == 0) {
                strcpy(result, fuel(info));
                isFuel = 1;
            }
            else if(strcmp(command, "Tire") == 0) {
                iInfo = atoi(info);
                strcpy(result, tire(iInfo));
            }
            else if(strcmp(command, "Tire Change") == 0) {
                strcpy(result, tireChange(info));
            }
            else {
                strcpy(result, "Invalid command");
            }

//            FILE *flog = fopen("/home/haidar/sisop/modul3/soal_3/server/race.log", "a");
            FILE *flog = fopen(realLog, "a");
            char date[25];
            time_t current_time = time(NULL);
            strftime(date, 25, "[%d/%m/%Y %H:%M:%S]", localtime(&current_time));
            if(isFuel == 1) {
            	fprintf(flog, "[Driver] %s: [%s] [%s%%]\n", date, command, info);
            }
            else {
            	fprintf(flog, "[Driver] %s: [%s] [%s]\n", date, command, info);
            }
            fprintf(flog, "[Paddock] %s: [%s] [%s]\n", date, command, result);
//            fprintf(flog, "%s %s\n", logLoc, realLoc);
            fclose(flog);

            send(new_socket, result, sizeof(result), 0);

            close(new_socket);
        }
        sleep(1);
    }

    return 0;
}
