#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define BUF_SZ 512

int main( int argc, char * argv[] ){
    int src_fd, dst_fd;
    char buf[BUF_SZ];
    int read_sz = 0;
    
    if( argc != 3 ){
        fprintf( stderr, "argument error \n" );
        exit( -1 );
    }
    
    if( ( src_fd = open( argv[1] , O_RDONLY ) ) == -1 ){
        fprintf( stderr, "open error \n" );
        exit( -1 );
    }
    if( ( dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , 0644 ) ) == -1 ){
        fprintf( stderr, "open error \n" );
        exit( -1 );
    }
    while( ( read_sz = read( src_fd , buf, BUF_SZ ) ) > 0 ){
        write( dst_fd, buf, read_sz);
    }
    close( src_fd );
    close( dst_fd );
    
    return 0;
}
