#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

// TCP server implementation
int main()
{
    int sockfd;
    char *message = "hello there my dear server!";
    char buffer[1024];

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(PORT);
    client_address.sin_addr.s_addr = inet_addr("192.168.1.7");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.13");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Socket opening error\n");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection Failed\n");
        return -1;
    }

    // finally we can send the message
    send(sockfd, message, strlen(message), 0);

    if (recv(sockfd, &buffer, strlen(buffer), 0) == -1)
    {
        perror("Received message error\n");
        return -1;
    }

    printf("Hello message sent successfully!\n");
    // close the client socket
    close(sockfd);
    return 0;
}