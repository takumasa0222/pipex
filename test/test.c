
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 1)
		printf("hello 42 c programing\n");
	else
	{
		for (int i = 0; i < argc; i++)
			printf("the argument is {%s}\n", argv[i]);
	}
}
