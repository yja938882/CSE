#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <time.h>

#define DIR_COLOR 36 	// Cyan
#define REG_COLOR 33 	// Yellow
#define LNK_COLOR 36	// Cyan

#define LINE_MAX 8

struct finfo{
	char *name;	// 파일 이름
	struct stat *fstat; // 파일 정보
	struct finfo* next; // 다음 struct finfo 
};

void *chk_malloc( ssize_t );
char *chk_strdup( char*);
int get_color( char );
struct finfo* read_dir( char *);
void print_dir( struct finfo* , int );
void print_mode( mode_t mode );
void print_bsize( off_t size );
void print_ctime( time_t time );
void print_dir( struct finfo* front , int op);

int main( int argc, char *argv[] ){
	struct finfo * f;
	int op =0;
	if( argc == 1 )
		f =read_dir("./");
	else if( argc >= 2 ){
		if( argv[1][0] == '-'){
			op = 1;
			if( argc == 2 ) f= read_dir("./");
			else f = read_dir( argv[2] );
		}else{
			f = read_dir( argv[1] );
		}
		
	}
	print_dir(f, op);	
	return 0;
}

// 파일 타입에 따른 색상 반환
int get_color( char type ){
	switch( type ){
		case DT_DIR :	return DIR_COLOR;
		case DT_REG :	return REG_COLOR;
		case DT_LNK :	return LNK_COLOR;
	}
	return 0;
}

// finfo structure 생성
struct finfo* create_finfo(struct dirent* dir_entry){
	struct finfo* f = (struct finfo*) chk_malloc( sizeof( struct finfo) );
	f->name = chk_strdup( dir_entry->d_name );
	f->fstat = (struct stat*) chk_malloc( sizeof( struct stat ) );
	stat( f->name , f->fstat );
	f->next = NULL;
	return f;
}

/*
* 디렉토리내 파일을 linked list 형태로 생성, list 의 front 반환
*/
struct finfo* read_dir( char* dir_name){
	struct finfo* front_f;
	struct finfo* f;
	DIR *dir_ptr;
	struct dirent *dir_entry;

	if( !(dir_ptr = opendir( dir_name )) ){
		fprintf( stderr, "cannot open %s\n", dir_name );
		exit( -1 ); 
	}

	// create front of linked list
	dir_entry = readdir( dir_ptr );
	front_f = create_finfo( dir_entry );
	f = front_f;
	
	while( (dir_entry = readdir( dir_ptr )) ){
		f->next = create_finfo( dir_entry);
		f = f->next;
	}

	return front_f; 
}

// 에러 검사된 strdup
char* chk_strdup( char* str ){
	char* ptr = (char*)chk_malloc( strlen(str)+1 );
	strcpy(ptr, str);
	return ptr;
}

// 에러 검사된 malloc
void *chk_malloc( ssize_t size ){
	void* ptr = malloc( size );
	if( !ptr ){	
		fprintf(stderr,"Fatal : failed to allocate memory.\n");
		abort();
	}
	return ptr;
}

// 모드 출력
void print_mode( mode_t mode ){
	char str[11];

	int ftype = mode & S_IFMT;
	if(ftype == S_IFREG) str[0] = '-';
	else if( ftype == S_IFSOCK) str[0] ='s';
	else if( ftype == S_IFLNK ) str[0] = 'l';
	else if( ftype == S_IFBLK ) str[0] = 'b';
	else if( ftype == S_IFDIR ) str[0] = 'd';
	else if( ftype == S_IFCHR ) str[0] = 'c';
	else if( ftype == S_IFIFO ) str[0] = 'p';
	else str[0] = '?';

	str[1] = (mode & S_IRUSR) ? 'r':'-';
	str[2] = (mode & S_IWUSR) ? 'w':'-';
	str[3] = (mode & S_IXUSR) ? 'x':'-';
	str[4] = (mode & S_IRGRP) ? 'r':'-';
	str[5] = (mode & S_IWGRP) ? 'w':'-';
	str[6] = (mode & S_IXGRP) ? 'x':'-';
	str[7] = (mode & S_IROTH) ? 'r':'-';
	str[8] = (mode & S_IWOTH) ? 'w':'-';
	str[9] = (mode & S_IXOTH) ? 'x':'-';
	str[10] = '\0';
	printf("%s\t",str);
}

// uid 에 해당하는 user name 출력
void print_uname( uid_t uid ){
	struct passwd* pwd = getpwuid( uid );
	printf("%s\t",pwd->pw_name);
}

// 파일의 바이트 사이즈 출력
void print_bsize( off_t size ){
	printf(" %lld\t",size);
}

// 마지막 수정시간 출력
void print_ctime( time_t time ){
	struct tm * ts = localtime( &time );
	printf( "%d:%d\t",ts->tm_hour, ts->tm_min );
}

// finfo 링크드 리스트의 처음부터 끝까지 출력
void print_dir( struct finfo* front , int op){
	struct finfo* f = front;

	while(f){
		printf("%-15s\t",f->name );
		if( op == 1){
			print_mode(f->fstat->st_mode);
			print_uname(f->fstat->st_uid);
			print_bsize(f->fstat->st_size);
			print_ctime( f->fstat->st_ctime );
			printf("\n");
		}
		f = f->next;
	}
	printf("\n");
}


