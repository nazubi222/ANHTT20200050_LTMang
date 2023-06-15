#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
    if( argc != 3){
        printf("Error");
        exit(1);
    }

    
    // Tao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client != -1){
        printf("Socket created:");
    } 
    else {
        printf("Failed to create socket.\n");
        exit(1);
    }

    char *ipServer = argv[1];
    int port = atoi(argv[2]);

    
    //Khai bao dia chi cua server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ipServer);
    addr.sin_port = htons(port);

    //Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if(res == -1){
        perror("Connect failed.\n");
        exit(1);
    } 
    else 
    {
        printf("Connected to server.\n");
    }

    char buf[256];
    int ret = recv(client, buf, sizeof(buf), 0);
    if(ret == -1){
        printf("Connection closed\n");
    }
    printf("Server phan hoi: %s", buf);

    while(1){
        printf("Enter string: ");
        fgets(buf, sizeof(buf), stdin);
        if(strncmp(buf, "exit", 4) == 0)
            break;

        send(client, buf, strlen(buf), 0);

        
    }

    close(client);

    return 0;
}