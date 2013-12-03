
int main()
{
        int list[7] = {4, 5, 3, 6, 1, 8, 2};

        int r5 = 0;
        int r6 = -1;

        do
        {
			if( list[r5] > r6 )
				r6 = list[r5];
        } while( r5++ < 7 );

		int* addr = (int *)0x6000;
		*addr = r6;
		return( 0 );
}


