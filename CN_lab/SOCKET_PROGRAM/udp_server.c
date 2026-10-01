#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // Required for close()
#include <sys/socket.h>  // Required for socket(), bind(), recvfrom()
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1

int main() {
    int sockfd;
    char buf[1024];
    struct sockaddr_in server, client;
    socklen_t client_addr_len = sizeof(client);
    
    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in Opening Socket");
        exit(1);
    }
         
    // 2. Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all available interfaces
    server.sin_port = htons(7777);               // Port number 7777
    
    // 3. Bind socket to port
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error in Binding Socket");
        close(sockfd);
        exit(2);
    }
    
    
    printf("\nSocket has port # %d \n", ntohs(server.sin_port));
    
    
    while (TRUE) {
        
        bzero(buf, 1024);
        client_addr_len = sizeof(client); 
        
        if (recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&client, &client_addr_len) < 0) {
            perror("Invalid Datagram Received");
            continue;
        }
         
        printf("Received: %s\n", buf);
    }
    
    close(sockfd);
    return 0;
}