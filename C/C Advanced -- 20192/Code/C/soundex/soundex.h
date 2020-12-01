#ifndef __SOUNDEX_H__
#define __SOUNDEX_H__

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const char* soundex(const char *s);
const char* Autocorrect(const char *s);

#endif