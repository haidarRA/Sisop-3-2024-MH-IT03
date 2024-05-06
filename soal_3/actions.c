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

char* tireChange(char* N) {
    if(strcmp(N, "Soft") == 0) {
        return "Mediums Ready";
    }
    else if(strcmp(N, "Medium") == 0) {
        return "Box for Softs";
    }
    else {
        return "Invalid tire type";
    }
}

char* gap(float N) {
    if(N < 3.5 && N >= 0) {
        return "Gogogo";
    }
    else if(N >= 3.5 && N <= 10) {
        return "Push";
    }
    else if(N > 10) {
        return "Stay out of trouble";
    }
    else if(N < 0) {
    	return "Invalid gap value";
    }
}

char* tire(int N) {
    if(N > 80 && N <= 100) {
        return "Go Push Go Push";
    }
    else if(N > 50 && N <= 80) {
        return "Good Tire Wear";
    }
    else if(N >= 30 && N <= 50) {
        return "Conserve Your Tire";
    }
    else if(N < 30 && N >= 0) {
        return "Box Box Box";
    }
    else if(N < 0 || N > 100) {
        return "Invalid tire condition";
    }
}

int isFloat(char* N) {
    int L = strlen(N);
    for(int i = 0; i < L; i++) {
        if(N[i] == '.') {
            return 1;
        }
    }
    return 0;
}

int isPercent(char* N) {
    int L = strlen(N);
    for(int i = 0; i < L; i++) {
        if(N[i] == '%') {
            return 1;
        }
    }
    return 0;
}

char* fuel(char* N) {

    float altN;
    if(isPercent(N)) {
        N[strlen(N)-1] = '\0';
    }
    
    if(isFloat(N)) {
        altN = atof(N);
    }
    else {
        altN = atoi(N);
    }

    if(altN > 80 && altN <= 100) {
        return "Push Push Push";
    }
    else if(altN <= 80 && altN >= 50) {
        return "You can go";
    }
    else if(altN < 50 && altN >= 0) {
        return "Conserve Fuel";
    }
    else if(altN < 0 || altN > 100) {
        return "Invalid fuel value";
    }
}
