#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // Include this for the close function

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error binding");
        close(sockfd); // Close the socket before exiting
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1)
    {
        // Receive data from client
        ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                    (struct sockaddr *)&client_addr, &client_len);
        if (recv_len < 0)
        {
            perror("Error receiving data");
            continue;
        }

        buffer[recv_len] = '\0'; // Null-terminate the received data
        printf("Received message from client: %s\n", buffer);

        // Send acknowledgement
        const char *ack_msg = "Acknowledgement";
        sendto(sockfd, ack_msg, strlen(ack_msg), 0,
               (struct sockaddr *)&client_addr, client_len);

        // Calculate length and send to client
        int msg_length = strlen(buffer);
        sendto(sockfd, &msg_length, sizeof(int), 0,
               (struct sockaddr *)&client_addr, client_len);

        // Wait for client's acknowledgement
        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client_addr, &client_len);
        printf("Client acknowledged: %s\n", buffer);
    }

    // Close the socket before exiting
    close(sockfd);

    return 0;
}
