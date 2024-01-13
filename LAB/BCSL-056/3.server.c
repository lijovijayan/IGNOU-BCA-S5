#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c, read_size, *num;
    struct sockaddr_in server, client;
    int message[10], i, sum = 0, size;

    struct sample
    {
        int sampleArray[10];
        int sampleSize;

    } a;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8880);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        // print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    // Receive a message from client
    while ((read_size = recv(client_sock, (struct sample *)&a, sizeof(a), 0)) > 0)
    {
        // print client msg at server side
        for (i = 0; i < a.sampleSize; ++i)
        {
            sum = sum + a.sampleArray[i];
        }
        // printf("%d\n", sum);
        write(client_sock, &sum, 1 * sizeof(int));
    }

    if (read_size == 0)
    {
        puts("Client disconnected");
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}
