#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>


struct Student
{
    char MSSV[20];
    char HoTen[50];
    int NgaySinh;
    int ThangSinh;
    int NamSinh;
    float DiemTBC;
};

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

    while(1){
        struct Student student;
        printf("\n\n**Nhập thông tin sinh viên:\n\n");

        printf("Nhap MSSV: ");
        scanf("%s", student.MSSV);
        printf("Nhap ho ten: ");
        scanf(" %[^\n]", student.HoTen);

        printf("Nhap ngay sinh: ");
        scanf("%d", &student.NgaySinh);

        printf("Nhap thang sinh: ");
        scanf("%d", &student.ThangSinh);

        printf("Nhap nam sinh: ");
        scanf("%d", &student.NamSinh);

        printf("Nhap diem trung binh: ");
        scanf("%f", &student.DiemTBC);
        
        char message[256];
        sprintf(message, "%s %s %d-%02d-%02d %.2f", student.MSSV, student.HoTen, student.NamSinh, student.ThangSinh, student.NgaySinh, student.DiemTBC);
        send(client, message, strlen(message), 0);

        
    }

    close(client);

    return 0;
}