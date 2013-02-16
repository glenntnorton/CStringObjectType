/*
#
# Year47 Software Library Resource
# Copyright (C) 2010-2012 Year47. All Rights Reserved.
# 
# Author: Glenn T Norton
# Contact: glenn@year47.com
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
# 
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.
#
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "String.h"

#define SZ 10240

/* --------------------------------------------------------------- */
unsigned int init(String *__string__, char *s) {
  
    unsigned int sz = 0;
    for(; *s != '\0'; s++) {
        sz = *s + 31 * sz;
    }
    return sz % __string__->sz;
}
/* --------------------------------------------------------------- */
String* newString(char *s) {
  
    String *__string__ = NULL;
    unsigned int sz = 0;

    if ((__string__ = malloc(sizeof(String))) == NULL) {
        fprintf(stderr, "newString() - No String Memory");
        return NULL;
    }
    if ((__string__->__refCount = malloc(sizeof(Str) * SZ)) == NULL) {
        fprintf(stderr, "newString() - No String Memory");
        return NULL;
    }
    __string__->__string = s;
    __str->print = &__print;
    
    
    return __str;
}
/* --------------------------------------------------------------- */
void __print(void) {
    printf("%s", __str->__string);
}
/* --------------------------------------------------------------- */
#if 0
char* getValue(Template *t, char *key) {
  
    TemplateList *list;
    unsigned int hashval = initTemplate(t, key);
	
    for(list = t->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(key, list->key) == 0) {
            return list->value;
        }
    }
    return NULL;
}
/* --------------------------------------------------------------- */
void setTemplateValue(Template *t, char *key, char *value) {
  
    TemplateList *new_list;
    unsigned int hashval = initTemplate(t, key);

    if((new_list = malloc(sizeof(TemplateList))) == NULL) {
        fprintf(stderr, "No Memory");
        exit(-1);
    }

    new_list->key   = strdup(key);
    new_list->value = strdup(value);
    new_list->next  = t->table[hashval];
    t->table[hashval] = new_list;
}
/* ---------------------------------------------------------------- */
void setTemplateVars(Template *t, char fb[]) {
  
    int i;
    char *TMPL_VAR_HEAD = "<TMPL_VAR NAME=\"";
    char *TMPL_VAR_TAIL = "\">";
    char *varHeadFind, *varBuffer;
    TemplateList *list = NULL;

    // Get the TMPL_VAR's
    for(i = 0; i < t->size; i++) {
        if((list = t->table[i]) != NULL) {
            varBuffer = (char*) malloc(
                strlen(TMPL_VAR_HEAD)+strlen(list->key)+strlen(TMPL_VAR_TAIL)
            );
            strcat(varBuffer, TMPL_VAR_HEAD);
            strcat(varBuffer, list->key);
            strcat(varBuffer, TMPL_VAR_TAIL);
            if((varHeadFind = (strstr(fb, varBuffer)))) {
                dataReplace(fb, varBuffer, list->value);
            }       
            free(varBuffer);
            varBuffer = NULL;
            list = list->next;
        }
    }
}
/* ---------------------------------------------------------------- */
void setTemplateIf(Template *t, char fb[]) {
  
    int i, j, start, end;
    char *TMPL_IF_HEAD  = "<TMPL_IF NAME=\"";
    char *TMPL_IF_TAIL  = "\">";
    char *TMPL_IF_CLOSE = "</TMPL_IF>";
    char *find1, *find2;
    char *varHeadIfFind, *ifBuffer, *buffer;
    TemplateList *list = NULL;
    
    for(i = 0; i < t->size; i++) {      
        if((list = t->table[i]) != NULL) {
            //build the tmp if buffer
            ifBuffer = (char*) malloc(
                strlen(TMPL_IF_HEAD)+strlen(list->key)+strlen(TMPL_IF_TAIL)
            );
            strcat(ifBuffer, TMPL_IF_HEAD);
            strcat(ifBuffer, list->key);
            strcat(ifBuffer, TMPL_IF_TAIL);
            
            if((varHeadIfFind = (strstr(fb, ifBuffer)))) {
                if(strcmp(list->value, NONE)) {
                    dataReplace(fb, ifBuffer, "");
                    free(ifBuffer);
                    ifBuffer = NULL;
                    
                    ifBuffer = (char*) malloc(
                        strlen(TMPL_IF_HEAD)+strlen(list->key)+strlen(TMPL_IF_TAIL)
                    );
                    strcat(ifBuffer, TMPL_IF_CLOSE);
                    dataReplace(fb, ifBuffer, "");
                    free(ifBuffer);
                    ifBuffer = NULL;
                    i = 0;
                }
                else {
                    find1 = strstr(fb, TMPL_IF_HEAD);
                    find2 = strstr(fb, TMPL_IF_CLOSE);
                    
                    start = abs(fb - find1);
                    end   = abs(fb - find2);
                    end   += strlen(TMPL_IF_CLOSE);
                    
                    buffer = (char*) malloc(SZ - 1);
                    for(i = start, j = 0; i < end; i++, j++) {
                        buffer[j] = fb[i];
                    }
                    buffer[j] = '\0';
                    dataReplace(fb, buffer, "");
                    i = 0;
                }
            }

            list = list->next;
        }
    }
}
/* ---------------------------------------------------------------- */

void destroyTemplate(Template *t) {
  
	int i;
	TemplateList *list, *temp;

	if (t == NULL) {
            return;
        }

	for(i = 0; i < t->size; i++) {
	    list = t->table[i];
	    while(list!=NULL) {
	        temp = list;
		list = list->next;
		free(temp->key);
		free(temp);
	    }
	}

	/* Free the table itself */
	free(t->table);
	free(t);
}
/* ---------------------------------------------------------------- */

void dataReplace(char string[], char *oldtext, char *newtext) {
  
    int oldLength = strlen(oldtext);
    int newLength = strlen(newtext);
    char *start, *p1, *p2;
  
    for(start = string; *start != '\0'; start++) {
        
        p1 = oldtext;
        p2 = start;
        while(*p1 != '\0') {
            if(*p1 != *p2) {
              break;
            }
            p1++;
            p2++;
        }
        if(*p1 == '\0') {
            if(oldLength > newLength) {
                /* move rest of string left */
                p2 = start + newLength;
                for(p1 = start + oldLength; *p1 != '\0'; p1++) {
                    *p2++ = *p1;
                }
                *p2 = '\0';
            }
            else if(oldLength < newLength) {
                /* move rest of string right */
                int leftover = strlen(start);
                p2 = start + leftover + (newLength - oldLength);
                *p2-- = '\0';
                for(p1 = start + leftover - 1;
                    p1 >= start + oldLength; p1--)
                *p2-- = *p1;
            }
            
            for(p1 = newtext; *p1 != '\0'; p1++)
                *start++ = *p1;
            return;
        }
    }
}
/* ---------------------------------------------------------------- */
char* templateFile(const char *name) {

    FILE *fin;
    char *b;
    register int i;
    int ch;

    b = (char*) malloc(sizeof(char) * (BUFSIZE - 1));

    fin = fopen(name, "r");
    if(!fin) {
      fprintf(stderr, "Could not open file %s.", name);
      exit(-1);
    }
    for(i = 0; ((ch = fgetc(fin)) != EOF); i++) {
      b[i] = ch;
    }
    b[BUFSIZE]  = '\0';

    return b;
}

/* ---------------------------------------------------------------- */

void getCgiValues(Template *t) {
  
    char *cl;
    int i, contentLength;
    TemplateList *head = NULL;
    TemplateList *current = NULL;
    TemplateList *tail = NULL;
  
    
    cl = getenv("CONTENT_LENGTH");
    sscanf(cl, "%d", &contentLength);
    
    for(i = 0; contentLength && (!feof(stdin)); i++) {
        current = (TemplateList*) malloc(sizeof(TemplateList));
        if(!current) {
            fprintf(stderr, "No memory.");
            exit(-1);
        }

        if(head == NULL) { head = current; }
        else { tail->next = current; }
        
        current->value = fmakeword(stdin, '&', &contentLength);
        plustospace(current->value);
        unescape_url(current->value);
        current->key = makeword(current->value,'=');
        tail = current;
    }

    current = head;
    while(current != NULL) {
        setTemplateValue(t, current->key, current->value);
        current = current->next;
    }
}

/* ---------------------------------------------------------------- */

/*
int Delete(Template *hashtable, char *str)
{
	int i;
	TemplateList *list, *prev;
	unsigned int hashval = initTemplate(hashtable, str);

	for(prev=NULL, list=hashtable->table[hashval];
		list != NULL && strcmp(str, list->key);
		prev = list,
		list = list->next);
	
	if (list==NULL) return 1;

	if (prev==NULL) {
            hashtable[hashval] = list->next;
        }
	else {
            prev->next = list->next; 
        }
	
	free(list->key);
	free(list->value);
	free(list);

	return 0;
}

int Count(Template *hashtable)
{
	int i, count = 0;
	TemplateList *list;

	if (hashtable==NULL) return -1;

	for(i=0; isize; i++) {
		for(list=hashtable[i]; list != NULL; list = list->next) count++;
	}

	return count;
}

TemplateList* Search(Template *hashtable, char *str) {
  
	TemplateList *list;
	unsigned int hashval = initTemplate(hashtable, str);
	
        for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
		if (strcmp(str, list->key) == 0) return list;
	}
	return NULL;
}
*/
/* ---------------------------------------------------------------- */
/*
int addParam(Template *t, char *key, char *value) {
  
	TemplateList *new_list;
	TemplateList *current_list;
	unsigned int hashval = initTemplate(t, key);

	if((new_list = malloc(sizeof(TemplateList))) == NULL) {
            return -1;
        }

        // No search for now...
	//current_list = Search(t, key);
	if(current_list != NULL) {
            return -1;
        }
        new_list->key   = strdup(key);
        new_list->value = strdup(value);
	new_list->next  = t->table[hashval];
	t->table[hashval] = new_list;

	return 0;
}
*/
/* SAVE!!!
void setParams(char fileBuffer[], CGI *cgi, int sz) {

    int j;
    char *find;
    char *TMPL_HEAD = "<TMPL_NAME=\"";
    char *TMPL_TAIL = "\">";
    char dataBuffer[sz];
  
    while(cgi != NULL) {
        strcat(dataBuffer, TMPL_HEAD);
        strcat(dataBuffer, cgi->key);
        strcat(dataBuffer, TMPL_TAIL);
        
        if(find = strstr(fileBuffer, dataBuffer)) {
            dataReplace(fileBuffer, dataBuffer, cgi->value);
        }

        for(j = 0; j < strlen(dataBuffer); j++) {
            dataBuffer[j] = '\0';
        }

        cgi = cgi->next;
    }
}
*/
#endif
