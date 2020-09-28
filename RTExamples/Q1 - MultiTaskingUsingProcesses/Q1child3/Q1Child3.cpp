#include "..\..\rt.h"

int main(int argc, char *argv[])
{
	int i ;

/*	printf("argc = %d\n", argc);
	for( i = 0; i < argc; i ++) 
		printf("arg[%d] = %s\n", i, argv[i]) ;

	getch() ;
*/
	for( i = 0; i < 300; i ++) {
		cout << "Hello from child process 3....\n";
		Sleep(50);
	}

	return 0 ;		// exit child program by returning status value 0
				// Note we could also call exit(0) to achieve the same thing
}