
/* A simple echo UDP client */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    int  sockfd, n, len, err;
    struct sockaddr_in servaddr, cliaddr;
    unsigned short port;
    
    if(argc < 2 || argc > 3){
       printf("Usage: a.out <IP address> <port - default 51000>\n");
       exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;

    if(argc == 3){
       err = sscanf(argv[2], "%d", &port);
       if(err != 1 || port == 0){
           printf("Invalid port\n");
           exit(-1);
       }
    } else {
       port = 51000;
    }

    printf("Port set to %d\n", port);

    servaddr.sin_port   = htons(port);
    
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
       printf("Invalid IP address\n");
       exit(-1);
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
       printf("Can\'t create socket, errno = %d\n", errno);
       exit(1);
    }

    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family      = AF_INET;
    cliaddr.sin_port        = htons(0);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0){
       printf("Can\'t bind socket, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    int N, k;
    printf("Enter N, k\n");
    scanf("%d %d", &N, &k);
    printf("N = %d, k = %d\n", N, k);
    
    int seg = N/k;
    double pi = 0;

    for (int i = 0; i < k; ++i)
    {
        int i_beg = seg * i;
        int i_end = seg * (i+1) - 1;
        
        if (i == k-1)
        {
            i_end = N-1;
        }

        int send[] = {N, i_beg, i_end};
        if(sendto(sockfd, send, 3*sizeof(int), 0, (struct sockaddr *) &servaddr,
        sizeof(servaddr)) < 0)
        {
            printf("Can\'t send request, errno = %d\n", errno);
            close(sockfd);
            exit(1);
        }

        double a = 0;

        if((n = recvfrom(sockfd, &f, sizeof(double), 0, (struct sockaddr *) NULL, NULL)) < 0)
        {
            printf("Can\'t receive answer, errno = %d\n", errno);
            close(sockfd);
            exit(1);
        }
        pi += f;
    }

    printf("pi = %f\n", pi);
    close(sockfd);
    return 0;
}
