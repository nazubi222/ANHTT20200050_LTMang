#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(){
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client == -1){
        printf("Socket failed.");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    printf("Connecting\n");

    if(connect(client, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        printf("Connect failed");
        exit(0);
    }
    

    printf("Connected.\n");
    char message[256];
    char computer[50];
    printf("Nhap ten may tinh:");
    fgets(computer, sizeof(computer), stdin);
    printf("Nhap so o cung:");
    char n[4];
    fgets(n, sizeof(n), stdin);
    sprintf(message, "%s%s",computer, n);
    fflush(stdin);

    for(int i = 0; i < atoi(n); i++){
        char name[5];
        char dungluong[7];
        printf("Nhap ten o cung:");
        fgets(name, sizeof(name), stdin);
        printf("Nhap dung luong:");
        fgets(dungluong, sizeof(dungluong), stdin);
        strncpy(message + strlen(message),name, sizeof(name));
        strncpy(message + strlen(message),dungluong, sizeof(dungluong));

    }

    send(client, message, strlen(message), 0);

    close(client);
    return 0;
}