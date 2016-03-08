#ifndef __UTIL
#define __UTIL

extern char *punctuation;
extern int punct_size;

extern char *blacklist;
extern int blacklist_size;

#define ALLOC_CHUNK_SIZE 10

char *getln(char *buff, FILE *stream);
wchar_t *wgetln(wchar_t *buff, FILE *stream);
int is_punct(int ch);
int is_blacklisted(int ch);

#endif
