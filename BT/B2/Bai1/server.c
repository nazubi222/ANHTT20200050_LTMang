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
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1){
        printf("Socket failed.\n");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr))== -1){
        printf("Bind failed.\n");
        exit(1);
    }

    if(listen(listener, 5)){
        printf("Listen failed.\n");
        exit(0);
    }
    printf("Waiting for a new client...\n");

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);

    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("Client connected: %s:%d\n", inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port));

    char buf[2048];
    
    int ret;
    while (1){
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <=0)         
            break;
        if (ret < sizeof(buf))
            {
            buf[ret] = 0;
            }
        char *str = strtok(buf,"\n");
        printf("Tên máy tính: %s\n", str);
        str = strtok(NULL,"\n");
        int n = atoi(str);
        printf("So o cung: %d\n", n);

        for(int i = 0;i<n; i++){
            str = strtok(NULL,"\n");
            printf("%s-",str);
            str = strtok(NULL,"\n");
            printf("%s",str);
            printf("GB\n");
        }
    }


    close(listener);
    close(client);

    return 0;
}
