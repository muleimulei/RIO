#include "rio_withbuf.c"
#include "rio_nobuf.c"
#include "socketfd.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#define MAXLINE 1000
void echo(int confd){
	size_t n;
	char buf[MAXLINE];
 	rio_t rio;
	rio_readinitb(&rio, confd);
	while((n = rio_readlineb(&rio, buf, MAXLINE))!=0){
		printf("server received %d bytes \n", (int)n);
		rio_writen(confd, buf,n);
	}
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[MAXLINE],client_port[MAXLINE];
	if(argc!=2){
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	listenfd = open_listenfd(argv[1]);
	printf("%d\n", listenfd);
	while(1){
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE,0);
		printf("Connenct to (%s, %s)\n", client_hostname, client_port);
		echo(connfd);
		close(connfd);
	}
	exit(0);
}

