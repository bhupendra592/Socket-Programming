/*
    UDP-Client Implementation
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
#include <strings.h>

#define MAXLINE 1024 
  
// Driver code 
int main(int argc, char *argv[]) 
{ 
    /*
            Check whether the port number is entered through command line?
    */
    if(argc < 2)
    {
        printf("Enter the Port Number after object file (*.out) \n");
        exit(0);
    }
    
    int sockfd, portnumber, serverlen;
    portnumber = atoi(argv[1]); 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 
    // Create a Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sockfd < 0 ) 
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    else
    {
        printf("Socket Created Successfully \n");
    }
    
    //alternative - bzero
    memset(&servaddr, 0, sizeof(servaddr)); 
    bzero(buffer,sizeof(buffer));
    //Initialize Server Structure Members
    servaddr.sin_family = AF_INET;     //IPV4
    servaddr.sin_port = htons(portnumber);   //PORT in network byte order
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    
 
   int retval = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    if(retval < 0)
    {
        printf("Connection or Binding failed\n");
        exit(0);
    }
    else
    {
        printf("connection Successful\n");
    }
    
    printf("Msg to Client : ");
    
    fgets(buffer,sizeof(buffer),stdin);
    
    sendto(sockfd, buffer, strlen(buffer)+1, MSG_CONFIRM, (const struct sockaddr*)&servaddr,  
            sizeof(servaddr));      
    
    bzero(buffer,sizeof(buffer));
      int serv_len = sizeof(servaddr); 
    int recvbytes = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &serv_len); 

    buffer[recvbytes] = '\0';  // To avoid garbage value
    
    printf("Msg from Server: %s", buffer); 
    printf("Connection Closed\n");
    close(sockfd); 
    
    return 0; 
} 
