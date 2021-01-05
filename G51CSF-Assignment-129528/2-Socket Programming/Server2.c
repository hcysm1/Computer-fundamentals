//////////////////////////  Server2.c ////////////////

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
	char buffer[MAXBUF];
	int i,j,r,temp;
    int l=strlen(buffer);
    
    
    
    

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
	/* bzero(&self, sizeof(self));*/
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = inet_addr("127.0.0.1");

	/*---assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

        puts("Bind done");

	/*---make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
        
        puts("Waiting for incoming connections...");

	/*---forever... ---*/
	
	
	
 
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);
	
		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
  	  if (clientfd < 0){
	    	printf("error accepting connection!\n");
	    	exit(1);
           }
  	  printf("connection accepted\n");
      printf("Client connected, ip: %s , port: %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
do{
	  memset(buffer,0,MAXBUF); //clearing the buffer
      r = recv(clientfd, buffer, MAXBUF, 0); //receiving request from client
      if(r == -1 || r == 0)//if no message is received terminate the client. so that server can accept the other client.
      {
      printf("Number of bytes received : -1");
      printf("\nClient Terminated!!!");
      close(clientfd);//close the connection 
      clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);//accept a new connection
      printf("\n\nNew Connection accepted\n");
      printf("New Client connected, ip: %s , port: %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));//printing new clients port and IP
      r = (recv(clientfd, buffer, MAXBUF, 0)); //again receiving request from new client.
	  }
      //otherwise  display length of message and keep reversing and convert to uppercase.
	  if (strcmp(buffer,"\r\n")!=0)//this is to solve the issue with putytel it was continuously
                                   //printing 2 times the length and the second time continuously "2"
	  	{
             printf("Number of bytes received : %d\n",strlen(buffer));
	  	}
      //reversing the message recieved from client
      i = 0; 
      j = strlen(buffer)-1;
      while(i<j)//loop until all the alphabets are swapped in reverse order.
      { 
         temp = buffer[i]; 
         buffer[i] = buffer[j]; 
         buffer[j] = temp; 
         i++; 
         j--;
       }
       // for loop for converting to uppercase
       for (i=0;i<strlen(buffer);i++)
	   	{
          buffer[i] = toupper(buffer[i]);
        }
     send(clientfd, buffer,strlen(buffer) , 0); //sending back response to client.
}while(1); //loop to accept multiple requests from client.
close(clientfd);
/*---clean up (should never get here!)---*/
WSACleanup();
return 0;
}

