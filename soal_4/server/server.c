#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <libgen.h>

#define PORT 8087

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

void removeLastDir(char *path) {
    int length = strlen(path);
    if (length == 0 || (length == 1 && path[0] == '/')) {
        return;
    }

    int i;
    for (i = length - 1; i >= 0; i--) {
        if (path[i] == '/') {
            break;
        }
    }

    if (i < 0) {
        return;
    }

    if (i == length - 1) {
        path[i] = '\0';
    } 
    else {
        path[i] = '\0';
    }
}

char* splitComma(char* str, int index) {
    char* token;
    char* rest = str;
    int count = 0;

    while ((token = strtok_r(rest, ",", &rest))) {
        count++;
        if (count == index) {
            return token;
        }
    }

    return NULL;
}

void splitEdit(char *input, char *str1, char *str2) {
    char *token = strtok(input, ",");
    if (token != NULL) {
        strcpy(str1, token);
        token = strtok(NULL, "");
        if (token != NULL) {
            strcpy(str2, token);
        } else {
            str2[0] = '\0';
        }
    } else {
        str1[0] = '\0';
        str2[0] = '\0';
    }
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char input1[100], input2[100], tempRes[1024];
    int count = 0;
    int isFound = 0;

    char* uPath = getPath();

    removeLastDir(uPath);

    char csvPath[100];
    strcpy(csvPath, uPath);
    strcat(csvPath, "/myanimelist.csv");

    char line[1024];
    FILE *fcsv = fopen(csvPath, "a+");

    char logPath[100];
    strcpy(logPath, uPath);
    strcat(logPath, "/change.log");
    FILE *flog;

    while(1) {
        valread = read(new_socket, buffer, 1024);
            
	if (valread <= 0) {
	    perror("read");
	    close(new_socket);
	    break;
	}
        printf("Received: %s\n\n", buffer);

        char *token = strtok(buffer, " \n");
            
        if(strcmp(buffer, "show") == 0) {
        }
        else if (token != NULL) {
            strcpy(input1, token);
        
            token = strtok(NULL, "\n");

            if (token != NULL) {
                strcpy(input2, token);
            } 
            else {
                printf("Invalid input.\n");
            }
        } 
        else {
            printf("Invalid input.\n");
        }
        
        if(strcmp(buffer, "exit") == 0) {
            sprintf(tempRes, "Exiting the client\n");
            send(new_socket, tempRes, strlen(tempRes), 0);
            close(new_socket);
            break;
        }

    	if(strcmp(buffer, "show") == 0) {
	    char output[8196] = {0};
	    while(fgets(line, sizeof(line), fcsv)) {
	    	sprintf(tempRes, "%d. %s\n", (count+1), splitComma(line, 3));
	    	strcat(output, tempRes);
	    	count++;
	    }
	    send(new_socket, output, strlen(output), 0);
    	}
    	else if(strcmp(input1, "status") == 0) {
    	    char output[8196] = {0};
	    while(fgets(line, sizeof(line), fcsv)) {
	    	if(strstr(line, input2)) {
		    sprintf(tempRes, "%s", splitComma(line, 4));
		    strcat(output, tempRes);
	    	    isFound = 1;
	        }
	    }
	    if(isFound == 0) {
	    	sprintf(tempRes, "anime tidak ditemukan\n");
	    	strcat(output, tempRes);
	    }
	    send(new_socket, output, strlen(output), 0);
        }
        else if(strcmp(input1, "genre") == 0 || strcmp(input1, "hari") == 0) {
    	    char output[8196] = {0};
    	    while(fgets(line, sizeof(line), fcsv)) {
    	        if(strstr(line, input2)) {
	    	    sprintf(tempRes, "%d. %s\n", (count+1), splitComma(line, 3));
		    strcat(output, tempRes);
	    	    count++;
	        }
	    }
	    send(new_socket, output, strlen(output), 0);
        }
        else if(strcmp(input1, "add") == 0) {
            char output[8196] = {0};
	    char addPath[100];
	    strcpy(addPath, uPath);
	    strcat(addPath, "/temp.csv");
	    FILE *fadd = fopen(addPath, "a");
	    while(fgets(line, sizeof(line), fcsv)) {
	    	fprintf(fadd, "%s", line);
	    }
	    fprintf(fadd, "\n%s", input2);
	    
	    rename(addPath, csvPath);
	    sprintf(tempRes, "anime berhasil ditambahkan\n");
	    strcat(output, tempRes);
	        
	    send(new_socket, output, strlen(output), 0);
	
    	    flog = fopen(logPath, "a");
            if (flog != NULL) {
                char date[25];
                time_t current_time = time(NULL);
                strftime(date, 25, "[%d/%m/%Y]", localtime(&current_time));
                fprintf(flog, "%s [ADD] %s ditambahkan.\n", date, splitComma(input2, 3));
            }
		
            fclose(flog);
            remove(addPath);
            fclose(fadd);
        }
        else if(strcmp(input1, "delete") == 0) {
            char output[8196] = {0};
    	    char delPath[100];
            strcpy(delPath, uPath);
    	    strcat(delPath, "/temp.csv");
    	    FILE *fdel = fopen(delPath, "w");
    	    while(fgets(line, sizeof(line), fcsv)) {
    	        if(!strstr(line, input2)) {
    	    	    fprintf(fdel, "%s", line);
    	        }
    	    }
    
    	    rename(delPath, csvPath);
	    sprintf(tempRes, "anime berhasil dihapus\n");
	    strcat(output, tempRes);
	    send(new_socket, output, strlen(output), 0);
	
    	    flog = fopen(logPath, "a");
            if (flog != NULL) {
                char date[25];
                time_t current_time = time(NULL);
                strftime(date, 25, "[%d/%m/%Y]", localtime(&current_time));
                fprintf(flog, "%s [DEL] %s berhasil dihapus.\n", date, input2);
            }
            fclose(flog);
    	    remove(delPath);
    	    fclose(fdel);
        }
        else if(strcmp(input1, "edit") == 0) {
            char output[8196] = {0};
    	    char editPath[100];
    	    strcpy(editPath, uPath);
    	    strcat(editPath, "/temp.csv");
    	    FILE *fedit = fopen(editPath, "w");

    	    char targetEdit[100], replacement[100], logLine[100];;

	    splitEdit(input2, targetEdit, replacement);

    	    while(fgets(line, sizeof(line), fcsv)) {
    	        if(strstr(line, targetEdit)) {
    	    	    fprintf(fedit, "%s", replacement);
    	    	    strcpy(logLine, line);
    	        }
    	        else {
    	            fprintf(fedit, "%s", line);
    	        }
    	    }

    	    rename(editPath, csvPath);
	    sprintf(tempRes, "anime berhasil diedit\n");
	    strcat(output, tempRes);
	    send(new_socket, output, strlen(output), 0);
	
    	    flog = fopen(logPath, "a");
            if (flog != NULL) {
                char date[25];
                time_t current_time = time(NULL);
                strftime(date, 25, "[%d/%m/%Y]", localtime(&current_time));
                fprintf(flog, "%s [EDIT] %s diubah menjadi %s.\n", date, logLine, replacement);
            }
            fclose(flog);
    	    remove(editPath);
    	    fclose(fedit);
        }
        else {
    	    printf("Invalid Command\n");
        }
       
        count = 0;
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
    }
//    close(new_socket); // Close connection after client disconnects


    fclose(fcsv);
    return 0;
}

