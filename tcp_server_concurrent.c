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
    int sockfd, newsockfd, clilen; 
    struct sockaddr_in seraddr, cliaddr;
    struct Person person;
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("192.168.0.198");  
    seraddr.sin_port = htons(PORTNO);
  
    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("Unable to bind");
        close(sockfd);
        exit(1);
    }
    
    listen(sockfd, 5);
  
    while (1) {
        clilen = sizeof(cliaddr);
        
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        
        if (fork() == 0) {  
            close(sockfd); 

            int n = recv(newsockfd, &person, sizeof(person), 0);
          
            printf("Received data:\n Age = %d, Name = %s\n", person.age, person.name);
            
            n = send(newsockfd, &person, sizeof(person), 0);
          
            close(newsockfd);  
            exit(0);           
        } else {
            close(newsockfd);  
        }
    }
    
    close(sockfd);
    return 0;
}

