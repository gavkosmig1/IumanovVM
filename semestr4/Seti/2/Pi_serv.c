
/* A simple echo UDP server */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


double func(double x) {
    return sqrt(4 - x * x);
}

double area(int i, double segment) {
    return (func(segment * i) + func(segment * (i+1))) * (segment / 2.0);
}

int main()
{

    int  sockfd, clilen, n;
   char line[1000];
    struct sockaddr_in servaddr, cliaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
       printf("Can\'t create socket, errno = %d\n", errno);
       exit(1);
    }

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t bind socket, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    while(1) {
       
      clilen = sizeof(cliaddr);

      int* rec = malloc(sizeof(int)*3);
       
      if((n = recvfrom(sockfd, rec, 1000, 0, (struct sockaddr *) &cliaddr, 
      &clilen)) < 0){
         printf("Can\'t receive request, errno = %d\n", errno);
         close(sockfd);
         exit(1);
      }
       
      int N = rec[0];
      int i_beg = rec[1];
      int i_end = rec[2];
      printf("%d %d %d", N, i_beg, i_end);

      double seg = 2.0 / N;
      double pi = 0.0;

      for (int i = i_beg; i <= i_end; ++i) {
         pi += area(i, seg);
      }
      printf("from %s %s\n", inet_ntoa(cliaddr.sin_addr), line);
      if(sendto(sockfd, &pi, sizeof(double), 0, (struct sockaddr *) &cliaddr,
      clilen) < 0){
         printf("Can\'t send answer, errno = %d\n", errno);
         close(sockfd);
         exit(1);
      }
      return 0;
   }
}

