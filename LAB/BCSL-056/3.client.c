// Write a client server Program for sum of numbers
#include <stdio.h>      //printf
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     // for close function

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    int server_reply;
    int number[10], i, temp, num = 0;

    struct sample
    {
        int sampleArray[10];
        int sampleSize;

    } a;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8880);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    printf("Enter the limit : ");
    scanf("%d", &num);

    printf("Enter numbers : \n");
    a.sampleSize = num;
    for (i = 0; i < num; i++)
    {
        scanf("%d", &temp);
        a.sampleArray[i] = temp;
    }

    if (send(sock, (struct sample *)&a, sizeof(a), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    // Receive a reply from the server
    if (recv(sock, &server_reply, 1 * sizeof(int), 0) < 0)
    {
        puts("recv failed");
        return 1;
    }

    printf("Sum is %d\n", server_reply);
    close(sock);
    return 0;
}
