#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>


int main(int argc, char *argv[]){
    
    if( argc != 3){
        printf("Error");
        exit(1);
    }
    int port = atoi(argv[1]);
    char *log_file = argv[2];

    //Tao socket
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener != -1){
        printf("Socket created: %d\n", listener );
    } 
    else {
        printf("Failed to create socket.\n");
        exit(1);
    }

    //Khai bao cau truc dia chi sv

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    //Gan dia chi voi socket

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr))){
        printf("Bind failed.\n");
        exit(1);
    }

    if(listen(listener, 5)){
        printf("Listen failed.\n");
        exit(1);
    }

    printf("Waiting for a new client...\n");

    //Chap nhan ket noi
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);

    int client = accept(listener, (struct sockaddr*)&clientAddr , &clientAddrLen);
    if(client == -1){
        printf("Accept failed.\n");
        exit(1);
    }
    printf("Connected\n");

    char buf[256];
    FILE *f1 = fopen(log_file, "a");

    while(1){
        int res = recv(client, buf, sizeof(buf), 0);
        if (res <= 0){
            printf("Disconnected\n");
            break;
        }
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[20];
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", tm);
        char msg[1000];
        sprintf(msg, "%s %s %s\n",inet_ntoa(clientAddr.sin_addr),s,buf );
    
        fwrite(msg, 1, strlen(msg), f1);
        printf("%s\n",msg);       
        }



    //Dong ket noi
    fclose(f1);
    close(client);
    close(listener);
    
    return 0;
}
