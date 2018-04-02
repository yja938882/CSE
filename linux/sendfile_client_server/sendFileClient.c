#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#define LENGTH 512
int main(int argc, char* argv[]){
	int sock_fd;  		// socket file descriptor
	int file_fd;  		// sending file descriptor 
	char *ip_addr;		// server ip
	int port_num; 		// port number
	char *file_name; 	// file name 
	struct sockaddr_in serv_addr;
	off_t offset = 0; 	//offset for sendfile
	struct stat statbuf; 	//stat of file
	
	//argv[1] = ip , argv[2] = port , argv[3] = file_name
	if(argc!=4){
		printf("error -wrong argument\n");
		printf("arg format : %s [IP] [PORT] [FILE_NAME]\n",argv[0]);
		return -1;
	}
	ip_addr = argv[1];
	port_num = atoi(argv[2]);
	file_name = argv[3];
	
	if( (file_fd = open(file_name,O_RDONLY))==-1){//open file
		printf("error - open();\n");
		return -1;
	}

	if(stat(file_name,&statbuf) == -1){//get file stat
		printf("error - stat();\n");
		return -1;
	}
	
	if( (sock_fd = socket(AF_INET, SOCK_STREAM,0)) ==-1){//open socke
		printf("error -socekt();\n");
		return -1;
	}

	//setting socket addr
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_num);
	inet_pton(AF_INET,ip_addr,&serv_addr.sin_addr);
	bzero( &(serv_addr.sin_zero), 8);

	if( connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1){//connet to server
		printf("error - connect();\n");
		return -1;
	}
	printf("[Client] connected to server at Port %d \n",port_num);
	
	if(sendfile(sock_fd, file_fd, &offset,statbuf.st_size)<0){//sendfile to server
		printf("error - sendFile();\n");
	}
	
	close(file_fd);	
	close(sock_fd);
	return 0;
}
