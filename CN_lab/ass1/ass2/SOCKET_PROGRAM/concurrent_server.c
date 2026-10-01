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

int main()
{
    int soc, chpid,msgsock;
    socklen_t len;
    char buf[1024],buf1[1024];
    struct sockaddr_in server,client;
    socklen_t addrlen = sizeof(client);
    // portno = 5001;
    
    // First call
    soc = socket(AF_INET,SOCK_STREAM,0);
    
    if (soc < 0){
    	perror("ERROR opening socket");
    	exit(1);
	}
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 0;
    
    
    if (bind(soc,(struct sockaddr *) &server, sizeof(server)) < 0){
    	perror("ERROR on binding");
    	exit(1);
    }
    
    len = sizeof(server);
    if(getsockname(soc,(struct sockaddr *)&server,&len))
    {
    	perror("\n Error in getting port..");
    	exit(3);
    }
    printf("\n Socket has port no: %hd\n",ntohs(server.sin_port));
//htons(	    
    listen(soc,5);
    signal(SIGCHLD,SIG_IGN);
    do
    {
    	msgsock = accept(soc,(struct sockaddr *)&client,(socklen_t*) &addrlen);
    	if(msgsock == -1){
    		perror("Error in accept..");
    		exit(0);
    	}
    	else{
    		if((chpid = fork())==0){
    			close(soc);
    			do{
    			  						read(msgsock,buf,1024);
printf("\n Message from client: %s\n",buf);
printf("\n Message to client:");
scanf("%[^\n]",buf1);
write(msgsock,buf1,1024);
}while(strcmp(buf1,"bye")!=0);
close(msgsock);
exit(0);
}
else
	close(msgsock);
}
}while(TRUE);
close(soc);
return 0;
}