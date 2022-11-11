#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

int main()
{
    int sockfd, newsockfd;
    char *message = "hello there, client!";
    char buffer[8000];

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.13");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Socket opening error");
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding error");
        return -1;
    }

    listen(sockfd, 3);

    int socksize = sizeof(struct sockaddr_in);
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&server_address, &socksize)) < 0)
    {
        perror("Connection accept error");
        return -1;
    }

    recv(newsockfd, &buffer, sizeof(buffer), 0);
    printf("Client message: %s\n", buffer);

    send(newsockfd, message, strlen(message), 0);

    close(newsockfd);
    close(sockfd);
    return 0;
}