#ifndef INCLUDEGUARD_PPATH
#define INCLUDEGUARD_PPATH
#define NS_NAME(symbol) com_6e5d_ppath_##symbol

size_t NS_NAME(normalize)(char* path);
void NS_NAME(rel)(char **result, char *abs, char *rel);
char* NS_NAME(rel_new)(char *abs, char *rel);
char *NS_NAME(abs_new)(char *rel);

#endif
