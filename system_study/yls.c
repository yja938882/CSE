#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#define DIR_COLOR 31 	// Red
#define REG_COLOR 33 	// Yellow
#define LNK_COLOR 36	// Cyan
int getColor( char type ){
	switch( type ){
		case DT_DIR :	return DIR_COLOR;
		case DT_REG :	return REG_COLOR;
		case DT_LNK :	return LNK_COLOR;
	}
	return 0;
}

void print_dir( char* dir_name ){
	DIR *dir_ptr;
	struct dirent *dir_entry;

	if( !(dir_ptr = opendir( dir_name )) ){
		fprintf(stderr," cannot open %s\n",dir_name);
		exit(-1);
	}

	while( (dir_entry = readdir( dir_ptr)) ){
		int color = getColor( dir_entry->d_type );
		printf("\033[0;%dm %s\t",color, dir_entry -> d_name );
	}

	closedir( dir_ptr );
	printf("\n");
}

int main(int argc , char *argv[] ){

	print_dir("./");
	return 0;
}
