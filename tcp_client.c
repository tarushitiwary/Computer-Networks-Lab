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
    float height;
    char name[50];
    int scores[5];
};

int main() {
    int sockfd;
    struct sockaddr_in seraddr;
    struct Person person;

    printf("Enter name: ");
    scanf("%49s", person.name);

    printf("Enter age: ");
    scanf("%d", &person.age);

    printf("Enter height: ");
    scanf("%f", &person.height);

    printf("Enter 5 scores: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &person.scores[i]);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("192.168.0.198");  
    seraddr.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0) {
        perror("Unable to connect");
        close(sockfd);
        exit(1);
    }
    
    int n = send(sockfd, &person, sizeof(person), 0);

    n = recv(sockfd, &person, sizeof(person), 0);

    printf("Received echo: Name = %s, Age = %d, Height = %.2f\n", person.name, person.age, person.height);
    printf("Scores = ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", person.scores[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}

