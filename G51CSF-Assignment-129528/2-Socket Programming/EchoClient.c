//////////////////////////echoclient ////////////////

#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<ctype.h>

#define MY_PORT		8989
#define MAXBUF		256

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET sockfd , clientfd;
   	struct sockaddr_in self;
   	struct sockaddr_in serv_addr;
	char buffer[MAXBUF];
	printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");

	/*---create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

        printf("Socket created.\n");

	/*---initialize address/port structure---*/
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(MY_PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//connect funtion to connect with the server.
if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
for(;;)
{
	   memset(buffer,0,MAXBUF); //clearing the buffer
       printf("\nClient message:  ");
	   gets(buffer);  //get input from client
	   if(strcmp(buffer,"QUIT")==0||strcmp(buffer,"quit")==0) //if client enters QUIT or quit 
	   return -1; //then client will terminate.
   	   send(sockfd, buffer,strlen(buffer) , 0); //send the message from client to server
       recv(sockfd, buffer, MAXBUF, 0); //receive the response from server
       printf("Server Reply : %s",buffer); //print the response on server window.
	   
}//infinite for loop to handle multiple requests
close (clientfd);
WSACleanup();
return 0;
}
