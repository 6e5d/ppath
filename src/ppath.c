#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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
		// printf("%zu %zu %zu %s\n", i, j, prev_pos, path);
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
			if (!last) {
				path[j] = '/';
				j += 1;
			}
		} else {
			// new and old paths are still aligned
			j = i + 1;
		}
		prev_pos = i + 1;
		if (last) {
			break;
		}
	}
	path[j] = '\0';
	return i;
}

char* ppath_rel_new(char* abs, char* rel) {
	char* result = malloc(strlen(abs) + strlen(rel) + 2);
	strcpy(result, abs);
	strcat(result, "/");
	strcat(result, rel);
	ppath_normalize(result);
	return result;
}
