#include <stdio.h>

#include "../include/ppath.h"

int main(void) {
	char a[] = "/../foo/bar///.././baz.txt";
	printf("before: %s\n", a);
	ppath_normalize(a);
	printf("after: %s\n", a);
}
