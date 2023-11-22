#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/ppath.h"

// normalize an absolute path will never increase its length,
// so we just over write the char*, return the new string length
size_t ppath_normalize(char* path) {
	assert(*path == '/');
	size_t prev_pos = 1;
	size_t i = 1;
	size_t j = 1;
	for (;; i += 1) {
		bool last = false;
		if (path[i] == 0) {
			last = true;
		} else if (path[i] != '/') {
			continue;
		}
		if (
			(i == prev_pos) ||
			((i == prev_pos + 1) && path[prev_pos] == '.')
		) { } else if (
			(i == prev_pos + 2) &&
			(path[prev_pos] == '.') &&
			(path[prev_pos + 1] == '.')
		) {
			// go parent
			if (j >= 3) {
				j -= 2;
				for (;; j -= 1) {
					if (path[j] == '/') {
						j += 1;
						break;
					}
					if (j == 1) {
						break;
					}
				}
			}
		} else if (prev_pos > j) {
			// do copy
			while (prev_pos < i) {
				path[j] = path[prev_pos];
				j += 1;
				prev_pos += 1;
			}
			path[j] = '/';
			j += 1;
		} else {
			// new and old paths are still aligned
			j = i + 1;
		}
		prev_pos = i + 1;
		if (last) {
			break;
		}
	}
	// j always points to next position after slash
	// but if lenth is 1 we have to add a slash
	if (j >= 2) {
		path[j - 1] = '\0';
	} else {
		path[1] = '\0';
	}
	return i;
}

char* ppath_rel(char *abs, char *rel) {
	size_t len1 = strlen(abs);
	size_t len2 = strlen(rel);
	char *result = malloc(len1 + len2 + 2);
	strcpy(result, abs);
	*(result + len1) = '/';
	strcpy(result + len1 + 1, rel);
	ppath_normalize(result);
	return result;
}

char *ppath_abs(char *rel) {
	if (*rel == '/') {
		return strdup(rel);
	}
	char *cwd = malloc(4096);
	assert(NULL != getcwd(cwd, 4096));
	char *result = ppath_rel(cwd, rel);
	free(cwd);
	return result;
}
