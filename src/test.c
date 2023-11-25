#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ppath.h"

int main(void) {
	char a[] = "/../foo/bar///.././baz.txt";
	printf("before: %s\n", a);
	ppath_normalize(a);
	printf("after: %s\n", a);
	assert(0 == strcmp(a, "/foo/baz.txt"));

	char b[] = "/foo/bar/baz.txt";
	printf("before: %s\n", b);
	ppath_normalize(b);
	printf("after: %s\n", b);
	assert(0 == strcmp(b, "/foo/bar/baz.txt"));

	char c[] = "/foo/..";
	printf("before: %s\n", c);
	ppath_normalize(c);
	printf("after: %s\n", c);
	assert(0 == strcmp(c, "/"));

	char d[] = "/foo/bar/..";
	printf("before: %s\n", d);
	ppath_normalize(d);
	printf("after: %s\n", d);
	assert(0 == strcmp(d, "/foo"));

	char *rel = ppath_abs_new("foo/bar/baz.tzt");
	printf("before: %s\n", rel);
	ppath_normalize(rel);
	printf("after: %s\n", rel);
	free(rel);
}
