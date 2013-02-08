#ifndef _STRING_H
#define _STRING_H

struct _str_ {
    // Members
    char *__string;
    // Functions
    void (*print)(void);
};
typedef struct _str_ Str;

struct _str_ref_ {
    int sz;
    Str **__refCount;
};
typedef struct _str_ref_ String;


unsigned int init(String *, char *);
String* newString(char *s);

void __print(void);

#endif /*String.h */
