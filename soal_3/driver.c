#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8085
#define IP "127.0.0.1"

int main() {
    while(1) {
        int sock = 0;
        struct sockaddr_in serv_addr;
	char input[100];
	char command[50], info[50], result[100];
        printf("[Driver] : ");
	fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = '\0';
    	sscanf(input, "[%[^]]] [%[^]]]", command, info);

        command[strcspn(command, "\n")] = '\0';
        info[strcspn(info, "\n")] = '\0';
        
//	printf("%s %s\n", command, info);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }

        if (send(sock, &command, sizeof(command), 0) < 0) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        if (send(sock, &info, sizeof(info), 0) < 0) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        if (recv(sock, &result, sizeof(result), 0) < 0) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("[Paddock]: [%s]\n", result);

        close(sock);
    }

    return 0;
}
