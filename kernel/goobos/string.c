#include <goobos/string.h>
#include <goobos/stddef.h>

size_t strlen(const char *s)
{
    size_t count = 0;
    while(s[count] != '\0') ++count;
    return count;
}
