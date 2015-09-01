#include <stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "test.txt";
  char *str = "Hello World\nThe C Programming Language\nTest Test\n";
  int i;
  fp = fopen( fname, "w" );

  for( i=0; i<100 ; i++ ){
    fputc( str[i], fp );
  }
  fclose( fp );
  printf( "%sOK\n", fname );
  return 0;
}
