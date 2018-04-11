#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#define DIR_COLOR 36 	// Cyan
#define REG_COLOR 33 	// Yellow
#define LNK_COLOR 36	// Cyan

#define LINE_MAX 8

struct finfo{
	char *name;
	struct stat *fstat;
	struct finfo* next;
};

void *chk_malloc( ssize_t );
char *chk_strdup( char*);
int get_color( char );
struct finfo* read_dir( char *);
void print_dir( struct finfo* );

int main( int argc, char *argv[] ){
	struct finfo * f;
	if( argc == 1 )
		f =read_dir("./");
	if( argc == 2 )
		f = read_dir(argv[1]);
	print_dir(f);	
	return 0;
}

int get_color( char type ){
	switch( type ){
		case DT_DIR :	return DIR_COLOR;
		case DT_REG :	return REG_COLOR;
		case DT_LNK :	return LNK_COLOR;
	}
	return 0;
}

struct finfo* create_finfo(struct dirent* dir_entry){
	struct finfo* f = (struct finfo*) chk_malloc( sizeof( struct finfo) );
	f->name = chk_strdup( dir_entry->d_name );
	f->fstat = NULL;
	f->next = NULL;
	return f;
}

struct finfo* read_dir( char* dir_name){
	struct finfo* front_f;
	struct finfo* f;
	DIR *dir_ptr;
	struct dirent *dir_entry;

	if( !(dir_ptr = opendir( dir_name )) ){
		fprintf( stderr, "cannot open %s\n", dir_name );
		exit( -1 ); 
	}

	dir_entry = readdir( dir_ptr );
	front_f = (struct finfo *)chk_malloc( sizeof( struct finfo ));
	front_f->name = chk_strdup( dir_entry->d_name );
	front_f->fstat = NULL;
	front_f->next = NULL;
	f = front_f;
	
	while( (dir_entry = readdir( dir_ptr )) ){
		f->next = create_finfo( dir_entry);
		f = f->next;
	}

	return front_f; 
}

char* chk_strdup( char* str ){
	char* ptr = (char*)chk_malloc( strlen(str)+1 );
	strcpy(ptr, str);
	return ptr;
}

void *chk_malloc( ssize_t size ){
	void* ptr = malloc( size );
	if( !ptr ){	
		fprintf(stderr,"Fatal : failed to allocate memory.\n");
		abort();
	}
	return ptr;
}

void print_dir( struct finfo* front ){
	struct finfo* f = front;

	while(f){
		printf("%s\t",f->name);
		f = f->next;
	}
	printf("\n");
}
