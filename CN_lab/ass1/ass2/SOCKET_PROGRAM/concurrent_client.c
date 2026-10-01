#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<signal.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define TRUE 1

int main(int argc, char *argv[])
{
    int soc, chpid,msgsock;
    socklen_t len;
    char buf[1024],buf1[1024];
    struct sockaddr_in server,client;
    // portno = 5001;
    
    // First call
    soc = socket(AF_INET,SOCK_STREAM,0);
    
    if (soc < 0){
    	perror("ERROR opening socket");
    	exit(1);
	}
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(atoi(argv[1]));
    
    if(connect(soc,(struct sockaddr *)&server,sizeof(server))<0)
    {
    	perror("\nError in connection..");
    	exit(2);
    }
    
    do
    {
    	printf("\n Client input:");
    	scanf("%[^\n]",buf);
    	write(soc,buf,1024);
	printf("\n");
    	read(soc,buf1,1024);
    	printf("Message from the server: %s",buf1);
    } while(strcmp(buf,"bye")!= 0);
    return 0;
}