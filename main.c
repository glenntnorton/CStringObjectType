#include "String.h"


int main(void) {
    
    String *s, *ss;
    s = newString("This is a new string");
    ss = newString("This is another new string");
    s->print();
    ss->print();

    return(0);
}
