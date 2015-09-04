#include <stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "test.txt";
  char *str = "Hello World\nThe C Programming Language\nTest Test\n";
  int i, j;
  char c = 'A';

   while(1){
    fp = fopen( fname, "a+" );
    for( i=0; i<26; i++){
      for( j=0; j<100 ; j++ ){
        fprintf(fp, "%c", c);
      }
      c++;
      fprintf(fp, "%c", '\n');
    }
      fclose( fp );
    c='A';
   }

  printf( "%s, OK\n", fname );
  return 0;
}
