// Program to fetch the date and time from server.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Sample {
    int sampleArray[10];
    int sampleSize;
};

int main(int argc, char *argv[]) {
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    struct Sample sampleData;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8880);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Prepare sample data
    sampleData.sampleSize = 5; // Set the size of the array
    for (int i = 0; i < sampleData.sampleSize; ++i) {
        sampleData.sampleArray[i] = i + 1; // Set values in the array
    }

    // Send sample data to the server
    write(sockfd, &sampleData, sizeof(sampleData));

    // Receive and print server's response
    int receivedSum;
    read(sockfd, &receivedSum, sizeof(int));
    printf("Sum received from server: %d\n", receivedSum);

    close(sockfd);

    return 0;
}
