#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int sockfd;
	char buf[1024];
	struct sockaddr_in server;
	sockfd=socket(AF_INET, SOCK_DGRAM,0);
	if(sockfd < 0){
		perror("\nError in Opening Socket ...");
		exit(1);}
		
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));
	while(1)
	{
		printf("Enter Message:");
		scanf(" %[^\n]",buf);
		sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server, sizeof(server));
		}
		
	close(sockfd);
	return 0;
	}