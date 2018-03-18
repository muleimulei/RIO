#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
size_t rio_readn(int fd, void *usrbuf, size_t n){
	size_t nleft = n;
	size_t nread;
	char *bufp = usrbuf;
	while(nleft>0){
		if((nread = read(fd, bufp, nleft))<0){
			if(errno == EINTR){
				nread = 0; // 被中断
			}else{
				return -1;
			}
		}else if(nread == 0){
			break;
		}
		nleft -= nread;
		bufp += nread;
	}
	return (n - nleft);
}

size_t rio_writen(int fd, void *usrbuf, size_t n){
	size_t nleft = n;
	size_t nwritten;
	char *bufp = usrbuf;

	while(nleft>0){
		if((nwritten = write(fd, bufp, nleft))<=0){
			if(errno == EINTR){
				nwritten = 0; // 被中断
			}else{
				return -1;
			}
		}
		nleft -= nwritten;
		bufp += nwritten;
	}

	return n;
}
