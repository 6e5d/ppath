#ifndef INCLUDEGUARD_PPATH
#define INCLUDEGUARD_PPATH

size_t ppath_normalize(char* path);
void ppath_rel(char **result, char *abs, char *rel);
char* ppath_rel_new(char *abs, char *rel);
char *ppath_abs_new(char *rel);

#endif
