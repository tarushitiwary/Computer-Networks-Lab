#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

struct Person{
  int age;
  char name[50];
};

int main(){
  int sockfd;
  struct sockaddr_in seraddr;
  struct Person person;
  
  printf("Enter age: ");
  scanf("%d", &person.age);
  printf("Enter name: ");
  scanf("%49s", person.name);
    
  sockfd = socket(AF_INET, SOCK_STREAM,0);
  
  seraddr.sin_family = AF_INET;
  seraddr.sin_addr.s_addr = inet_addr("192.168.0.198");
  seraddr.sin_port = htons(PORTNO);
  
  if(connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0){
    perror("Unable to connect");
    exit(1);
  }
  
  int n = send(sockfd, &person, sizeof(person), 0);
  
  n = recv(sockfd, &person, sizeof(person),0);
  
  printf("\nReceived echo: Age = %d, Name = %s\n", person.age, person.name);
  
  close(sockfd);
  return 0;
}
  
  

