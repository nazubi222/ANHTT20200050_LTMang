#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


struct disk{

int name;
int capacity;

};


int main(int argc, char *argv[])
{

    int port = atoi(argv[1]);

    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);

    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));


    char hello[256]=" Xin chao cac ban!";
    send(client, hello, strlen(hello), 0);

    char buf[256];

    int res = recv(client, buf, sizeof(buf), 0);
    if (res <= 0)
    {
        printf("Ket noi bi dong.\n");
        return 1;
    }
    else printf("Ten may tinh la: %s\n", buf);
    if (res < sizeof(buf))
        buf[res] = 0;
    
    printf("Thong tin o dia:\n");
    while (1)
    {
        res = recv(client, buf, sizeof(buf), 0);
        if (res <= 0)
        {
            printf("Ket noi bi dong.\n");
            break;
        }

        char * p = strtok(buf, "-");
        printf("Ten o dia: %s\n", p);
        p = strtok(NULL, "-");
        printf("Dung luong: %s\n", p);
        printf("----------------------\n");
        if (res < sizeof(buf))
            buf[res] = 0;
     
    
    }
    close(client);
    close(listener);
}