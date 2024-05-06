#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8087

int main(int argc, char const *argv[]) {
    while (1) {
        struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char buffer[1024] = {0};

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }

        while (1) {
            char input[125];
            memset(input, 0, sizeof(input)); // Clear buffer
            printf("You: ");
            fgets(input, 125, stdin);
            input[strcspn(input, "\n")] = '\0';
            send(sock, input, strlen(input), 0);

            if(strcmp(input, "exit") == 0) {
                close(sock);
                return 0;
            }
            
	    char output[8192] = {0};
            valread = read(sock, output, sizeof(output));
            printf("Server:\n");
            printf("%s\n", output);
            memset(buffer, 0, sizeof(buffer)); // Clear buffer
        }
    }
    return 0;
}

