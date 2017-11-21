#include "types.h"
#include "x86.h"
#include "fs.h"

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

int
memcmp(const void *v1, const void *v2, uint n)
{
  const uchar *s1, *s2;

  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void*
memmove(void *dst, const void *src, uint n)
{
  const char *s;
  char *d;

  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  } else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}

// memcpy exists to placate GCC.  Use memmove.
void*
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

char*
strncpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
}

// Like strncpy but guaranteed to NUL-terminate.
char*
safestrcpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  if(n <= 0)
    return os;
  while(--n > 0 && (*s++ = *t++) != 0)
    ;
  *s = 0;
  return os;
}

int
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

int
findKeyInBlock(uchar* key, uchar* data)
{
  int i;
  for (i = 0; i < BSIZE; i += 32){ // 32 is the size of a tag
    int j;
    for (j = 0; j < 10 && i + j < BSIZE; j++){
      if (key[j] && data[i + j] && key[j] == data[i + j]){
        continue;
      }
      if (j == strlen((char*)key) && !key[j] && !data[i + j]){
        return i;
      }
    }
  }
  return -1;
}

int
tagFullInBlock(uchar* data)
{
  int i;
  for (i = 0; i < BSIZE && data[i]; i += 32);
  if (i == BSIZE) return -1;
  return i;
}
