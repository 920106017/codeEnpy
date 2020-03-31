#include <stdio.h>

void main()
{
	char count[7];
	memset(count, 0 , sizeof(count));

	int bitSum = 0;
	for (int i=0; i<16; i++) {
		printf("%d: ", i);
		bitSum = 0;
		for (char bit=3; bit>=0; bit--) {
			bitSum +=( (1<<bit)&i ? bit : 0 ) ;
			printf("%d ", (1<<bit)&i ? 1 : 0);
		}
		printf("sum=%d\n", bitSum);
		count[bitSum] += 1;
	}

	for (int i=0; i<sizeof(count); i++) {
		printf("bitSum=%d occur %d times.\n", i, count[i]);
	}
}
