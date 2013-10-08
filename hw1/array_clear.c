
#include <stdio.h>
#include <stdlib.h>

int main()
{
  short int M[256];
  int i = 0;
  for( i ; i < 256; ++i )
  {
    printf( "%d: %d / ", i, M[i] );
    M[i] = 0;
    printf( "%d\n", M[i] );
  }
}
