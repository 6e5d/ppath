#ifndef INCLUDEGUARD_PPATH
#define INCLUDEGUARD_PPATH

size_t ppath(normalize)(char* path);
void ppath(rel)(char **result, char *abs, char *rel);
char* ppath(rel_new)(char *abs, char *rel);
char *ppath(abs_new)(char *rel);

#endif
