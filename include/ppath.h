#include <stddef.h>

size_t ppath_normalize(char* path);
void ppath_rel(char **result, char *abs, char *rel);
char* ppath_rel_new(char* abs, char* rel);
char *ppath_abs(char *rel);
