#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // Include this for the close function

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];
    const char *message = "Hello, Server!";

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Send message to server
    sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr*)&server_addr, server_len);

    // Receive acknowledgement
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&server_addr, &server_len);
    printf("Received acknowledgement from server: %s\n", buffer);

    // Receive length from server
    int msg_length;
    recvfrom(sockfd, &msg_length, sizeof(int), 0,
             (struct sockaddr*)&server_addr, &server_len);
    printf("Received message length from server: %d\n", msg_length);

    // Send acknowledgement to server
    const char *ack_msg = "Response acknowledged";
    sendto(sockfd, ack_msg, strlen(ack_msg), 0,
           (struct sockaddr*)&server_addr, server_len);

    // Close the socket before exiting
    close(sockfd);

    return 0;
}
