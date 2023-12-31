#include <unistd.h>
#include "../include/ppath.h"

static size_t parent_dir_idx(char *path, size_t j) {
	// skip the slash
	j -= 2;
	// goto next slash
	for (;;j -= 1) {
		if (path[j] == '/') {
			j += 1;
			break;
		}
		if (j == 1) {
			break;
		}
	}
	return j;
}

// normalize an absolute path will never increase its length,
// so we just over write the char*, return the new string length
size_t ppath(normalize)(char *path) {
	assert(*path == '/');
	size_t prev_pos = 1;
	size_t i = 0;
	size_t j = 0;
	for (;;i += 1) {
		bool last = false;
		if (path[i] == 0) {
			last = true;
		} else if (path[i] != '/') {
			continue;
		}
		if (
			(i == prev_pos) ||
			((i == prev_pos + 1) && (path[prev_pos] == '.'))
		) { } else if (
			(i == prev_pos + 2) &&
			(path[prev_pos] == '.') &&
			(path[prev_pos + 1] == '.')
		) {
			// go parent
			if (j >= 3) {
				j = parent_dir_idx(path, j);
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

void ppath(rel)(char **result, char *abs, char *rel) {
	size_t len1 = strlen(abs);
	size_t len2 = strlen(rel);
	*result = realloc(*result, len1 + len2 + 2);
	char *p = *result;
	assert(p != NULL);
	strcpy(p, abs);
	*(p + len1) = '/';
	strcpy(p + len1 + 1, rel);
	ppath(normalize)(p);
}

char *ppath(rel_new)(char *abs, char *rel) {
	char *result = NULL;
	ppath(rel)(&result, abs, rel);
	return result;
}

char *ppath(abs_new)(char *rel) {
	if (*rel == '/') {
		char *new = malloc(strlen(rel) + 1);
		strcpy(new, rel);
		return new;
	}
	char *cwd = malloc(4096);
	assert(NULL != getcwd(cwd, 4096));
	char *result = ppath(rel_new)(cwd, rel);
	free(cwd);
	return result;
}
