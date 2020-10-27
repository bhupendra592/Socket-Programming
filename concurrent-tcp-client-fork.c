#include <stdio.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <netinet/in.h>  //Structure
#include <arpa/inet.h>  //inet_addr
#include <unistd.h> // read and write
#include <stdlib.h> //exit
#include <strings.h>  //bzero
#include <string.h> 
#define BUFFER_SIZE 1024  //buffer for read and write operations
char sendbuffer[1024];
char recvbuffer[1024];
/*-----------fork system call return type---*/

pid_t ret;

/*
Error Handler/routine
*/
void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd,portnumber;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE];
	/*
	detailed information about
	Socket Structure - Refer:
	man 7 ip
	*/
	//Creation of Socket
if (argc < 2)
	{
		printf("Error !! Enter Port Number\n");
		exit(1);
	}
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
	error("Socket creation failed");
}
else
{
	printf("socket Created Successfully\n");
}

//clear/flush the strucrure memory
bzero(&serv_addr, sizeof(serv_addr));
portnumber = atoi(argv[1]);
/*Assigning IP address and PORT */
serv_addr.sin_family = AF_INET;
/*
man 3 inet_addr
inet_addr : converts IPV4 dotted decimal format
into binary (network byte order)
*/

serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

serv_addr.sin_port = htons(portnumber);

/*
connect the client socket to the server Socket
*/

int retcon = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
if(retcon < 0 )
{
	error("Connection to server Socket Failed");
}
else
{
	printf("Connected to Server successfully \n");
}

/* fork system call to create child process */

ret = fork();
if(ret == 0)
{
   while(1)
   {
	bzero(&sendbuffer, sizeof(sendbuffer));
	// Send the data from from client to server
    printf("Msg to Server : ");	
	fgets(sendbuffer,1024,stdin);
	send(sockfd,sendbuffer,strlen(sendbuffer)+1,0);
 }
}
else if (ret > 0)
{
  while(1)
  {
	
	bzero(&recvbuffer, sizeof(recvbuffer));
	// Receive the data from client and print 
	recv(sockfd,recvbuffer,sizeof(recvbuffer),0);
    printf("Msg from Server : %s\t",recvbuffer);

  }
}
else
{
	printf("failed to create child process\n");
}

//close the socket file descriptor
close(sockfd);
return 0;
}




