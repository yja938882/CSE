#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#define LENGTH 512
int main(int argc, char*argv[]){
	int sock_fd;	//server socket fd
	int clnt_fd;	//client socket fd
	int port_num;	//prot number
	struct sockaddr_in serv_addr;	//server addr
	char buf[100];	//buffer for recv file

	//argv[1] = port
	if(argc!=2){
		printf("error -wrong argument\n");
		printf("arg format : %s [PORT]\n");
		return -1;
	}

	port_num = atoi(argv[1]);

	if( (sock_fd = socket(AF_INET,SOCK_STREAM, 0))==-1){//open socket
		printf("error -socket();");
		return -1;
	}
	memset(&serv_addr, '0' , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port_num);
	
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//bind socket
	listen(sock_fd, 10);//set socket to listen state

	if( (clnt_fd = accept(sock_fd, (struct sockaddr*)NULL,NULL)) ==-1){//accept connect.
		printf("error -accept();");
		return -1;
	}
	while(recv(clnt_fd,buf,LENGTH,0)>0){//recv file from client socket
		printf(buf);
	}

	close(clnt_fd);
	close(sock_fd);
	return 0;
}
