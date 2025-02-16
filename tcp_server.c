#include <stdio.h>
#include <st    ring.h>
#include <unistd.h>
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
    int sockfd, newsockfd, clilen;
    struct sockaddr_in seraddr, cliaddr;
    struct Person person;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("192.168.0.198"); 
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0) {
        perror("Error on binding");
        close(sockfd);
        return 1;
    }

    listen(sockfd, 5);

    while (1) {
        clilen = sizeof(cliaddr);


        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        
        int n = recv(newsockfd, &person, sizeof(person), 0);
       
        printf("Received data: Name = %s, Age = %d, Height = %.2f\n", person.name, person.age, person.height);
        printf("Scores = ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", person.scores[i]);
        }
        printf("\n");
        
        n = send(newsockfd, &person, sizeof(person), 0);

        close(newsockfd);
    }
    close(sockfd);
    return 0;
}

