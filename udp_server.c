#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

struct Person {
    int age;
    char name[50];
};

int main() {
    int sockfd, clilen;
    struct sockaddr_in seraddr, cliaddr;
    struct Person person;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.48.22");
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        clilen = sizeof(cliaddr);
        int n = recvfrom(sockfd, &person, sizeof(person), 0, (struct sockaddr*)&cliaddr, (socklen_t *)&clilen);
        
        printf("Received data: Name = %s, Age = %d\n", person.name, person.age);

        n = sendto(sockfd, &person, sizeof(person), 0, (struct sockaddr*)&cliaddr, (socklen_t *)&clilen);
    }

    close(sockfd);
    return 0;
}

