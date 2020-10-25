/*
TCP based continuously running server Application
Bi-Directional Half Duplex Communication with the Client Application
Maintained by : Bhupendra Pratap Singh <bhupendra.jmd@gmail.com>
*/

/*
Socket Header files
*/

#include <stdio.h>			//Printf and Scanf
#include <sys/types.h>   	//Socket System call       
#include <sys/socket.h>		//Socket System Call
#include <strings.h>		//bzero API(s)
#include <unistd.h>		//read system call
#include <stdlib.h>		//exit
#include <netinet/in.h>		//structure member - man 7 ip
#include <string.h>
/*
Error Handler/routine
*/
void error(char *msg)
{
	perror(msg);
	exit(1);
}

/* main function - driver code */
int main(int argc, char *argv[])
{
	/*
	master socket descriptor - responsible for connection establishment between client and server
	*/	
	int sockfd; 
	char inputmessage[1024];
	/*	Socket descriptor for accept system call to perform read and write operations
		connfd descriptor will be used for data exchange between client and Server
	*/
	int connfd; 
	
	/* server port number and client address len declaration */	

	int portnumber, clilen;  
	
	/* buffer to read and write the data between client & server 
	   Ensure to clear the buffer once you perform read/write and subsequently needs read/write operations
	*/		
	char buffer[1024];
	
	/* server/client structure declaration */
	
	struct sockaddr_in serv_addr, cli_addr;
	/* Declarations for bytes read at the server end written by the client */	
	   int readbytes;

	/* 	condition check for commandline arguments	*/
	if (argc < 2)
	{
		error("Error !! Enter the Port Number while running the program - ./a.out <portnumber> \n");
	}

	/* Creation of Master Socket for bind, listen and accept system calls
	-> refer man socket(2) for details
	AF_INET - IPv4 Internetprotocols         
	SOCK_STREAM - TCP based stream 
	0 - protcol (decided by system/kernel/OS) (important to mention if TCP/UDP protcol  is not used for socket type
 	*/
	
	sockfd = socket(AF_INET,SOCK_STREAM, 0);   //sockfd is socket descriptor
	/* condition check for socket return type*/
	if(sockfd < 0)
	{
		error("Socket is not created");
	}
	else
	{
		printf("Socket is created successfully\n");
	}

	/* clear/clean the structure buffer with - either bzero or memset to avoid any garbage value */
	bzero((char *)&serv_addr, sizeof(serv_addr));
	/*
		port number - integer - atoi()) - > entred from command line ./filename <portnumber>
		argv[1] - is first argument
	*/
		
	portnumber = atoi(argv[1]);

	/*
		Initialize the members of stuructures
	*/

	serv_addr.sin_family = AF_INET; //IPV4 Internet family

/*
	INADDR_ANY - binds to all the available
	interfaces of host machine/work station
	else specific interfaces can be initialized
	like :
	localhost
	127.0.0.1
	Wifi - interface - eg. "192.168.75.1"
	layman termi: client can connect to server with all interfaces of server
*/
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	/* htons - host to network byte order(short)
	   network byte order - BigEndian
	*/
	
	serv_addr.sin_port = htons(portnumber);
	/* bind the socket with server address/domain with bind system call 
	  As socket gets created but initially it doesn't bind to any domain or ip address
	*/

	int ret = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	if (ret < 0)	
	{
		error("Error in binding the socket");
	}
	else
	{
		printf("Socket Binding is Successful !!\n");
	}
/* listen to maximum backlog connections
	-> listen system call
*/
int backlog = 5;
int ret1 = listen(sockfd, backlog);
if(ret1 < 0)
{
	error("listen failed to accept requests to keep it in pending queues");
}

else
{
	printf("server started successfully\n");
}

/*  calculate the size of client structure */

clilen = sizeof(cli_addr);

/* Accept system call - to fetch pending requests from the queues */

connfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

if (connfd < 0 )
{
	error("error in Accepting the request");
}
else
{
	printf("request accepted successflly with connefd :  %d\n",connfd);

}

/*

exchange of Information between client and server:

Avialble options:
1. read and write
2. send and receive

*/

while(1)
{

	/*Clean the buffer to avoid any garbage value */
	
	bzero(buffer, sizeof(buffer));

	/* Read data from the client application */

	readbytes = read(connfd, buffer, sizeof(buffer)); 

	if(readbytes < 0)
	{
		error("No data is read from the client Application");
	}
   printf("Msg from client: %s", buffer);
   printf("Msg to Client : ");
   fgets(inputmessage, 1024, stdin); 
   //printf("%s", inputmessage); 
	int writebytes;

	writebytes = write(connfd,inputmessage,strlen(inputmessage)+1);
	if (writebytes < 0)
	{
		error("Error in Writing the Data");
	}

}

//close the socket file descriptor
close(sockfd);

}




