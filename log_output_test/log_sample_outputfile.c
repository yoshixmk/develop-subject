#include <stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "test.txt";
  char *str = "Hello World¥nThe C Programming Language¥nTest Test";
  int i;

  fp = fopen( fname, "w" );
  if( fp == NULL ){
    printf( "%sファイルが開けません¥n", fname );
    return -1;
  }

  for( i=0; ; i++ ){
    fputc( str[i], fp );
  }

  fclose( fp );

  printf( "%sファイル書き込みが終わりました¥n", fname );
  return 0;
}