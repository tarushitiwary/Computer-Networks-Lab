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
    int sockfd;
    struct sockaddr_in seraddr;
    struct Person person;

    printf("Enter name: ");
    scanf("%49s", person.name);

    printf("Enter age: ");
    scanf("%d", &person.age);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.48.22");
    seraddr.sin_port = htons(PORTNO);

    int n = sendto(sockfd, &person, sizeof(person), 0, (struct sockaddr*)&seraddr, sizeof(seraddr));
    
    n = recvfrom(sockfd, &person, sizeof(person), 0, (struct sockaddr*)&seraddr, (socklen_t *)&seraddr);

    printf("Received echo: Name = %s, Age = %d\n", person.name, person.age);

    close(sockfd);
    return 0;
}

