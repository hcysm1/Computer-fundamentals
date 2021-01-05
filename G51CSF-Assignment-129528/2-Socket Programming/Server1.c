//////////////////////////  Server1.c ////////////////

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
	int i,j,temp;
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
	
	while (1)
	{	struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);
		
        //to reset buffer we will use memset function to avoid junk values.
        memset(buffer,0,MAXBUF);
		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
		
		//receiving request from client.
        recv(clientfd, buffer, MAXBUF, 0);
        //reversing the message recieved from client
      i = 0;                 //initializing it to zero because index starts at zero
      j = strlen(buffer)-1;  //index ends at n-1 so that's why strlen(buffer)-1
      while(i<j)             //continue looping until all the alphabets are swapped in reversed order. 
      { 
         temp = buffer[i]; 
         buffer[i] = buffer[j]; 
         buffer[j] = temp; 
         i++; 
         j--;
       }
       //using for loop to convert all the alphabets to uppercase.
       for (i=0;i<strlen(buffer);i++){
          buffer[i] = toupper(buffer[i]);
        }
        //sending back the response to client.
       send(clientfd, buffer,strlen(buffer) , 0);
       
		/*---close connection---*/
		close(clientfd);
	}

	/*---clean up (should never get here!)---*/
	close(sockfd);
        WSACleanup();
	return 0;
}

