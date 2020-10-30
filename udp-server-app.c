/*
    UDP-Server Implementation
    maintained by : <bhupendra.jmd@gmail.com>
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAXLINE 1024  
// Driver code 
int main(int argc, char* argv[]) 
{ 
     if(argc < 2)
    {
        printf("Enter the Port Number after object file (*.out) \n");
        exit(0);
    }
    int sockfd, portnumber;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr; 
    portnumber = atoi(argv[1]);      //port number through command line
    if(argc < 2)
    {
        printf("Enter the Port Number \n");
        exit(0);
    }

    // Create a Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if ( sockfd < 0) 
    { 
        perror("socket creation failed"); 
        exit(0); 
    } 
    else
    {
        printf("Socket Created Successfully\n");
    }
    
    //Clear the server/client structure buffer
    
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    //Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(portnumber); 
    
    // Bind the socket with the server address 
    int ret = bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    if ( ret < 0 ) 
    { 
        perror("Server failed to bind with port/IP and protocol"); 
        exit(1); 
    } 
    else
    {
        printf("Server started at port number: %d\n",portnumber);
    }
    int clilen = sizeof(cliaddr);

    int nbytes = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL,(struct sockaddr*)&cliaddr,&clilen); 
    
    buffer[nbytes] = '\0';   //To avoid garbage value
    
    printf("Msg from Client : %s", buffer); 
    bzero(buffer,sizeof(buffer));
    printf("Msg to client : ");
    fgets(buffer,sizeof(buffer),stdin);
    sendto(sockfd, buffer, strlen(buffer)+1,MSG_CONFIRM, (const struct sockaddr *) &cliaddr,clilen);     
    close(sockfd);
    return 0; 
} 
