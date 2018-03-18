#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#define MAXLINE 1000


int main(int argc, char **argv)
{
	struct addrinfo *p, *listp, hints;
	char buf[MAXLINE];
	int rc, flags;
	if(argc !=2 ){
		fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
		exit(0);
	}
	//获取域名详细信息
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //只获取ipv4地址
	hints.ai_socktype = SOCK_STREAM; //
	if((rc = getaddrinfo(argv[1], NULL, &hints, &listp))!=0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
		exit(1);
	}
	//遍历列表
	for(p = listp; p ; p = p->ai_next){
		getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, NI_NUMERICHOST);
		printf("%s\n", buf);
	}
	//clean up
	freeaddrinfo(listp);
	return 0;
}
