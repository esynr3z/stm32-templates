//-- Includes ------------------------------------------------------------------
#include "retarget_conf.h"

//-- Functions -----------------------------------------------------------------
#if defined(USE_RETARGET) || defined(USE_RETARGET_ITM)

#if defined(__GNUC__)

int _write(int fd, char* ptr, int len)
{
    (void)fd;
    int i = 0;

    while (ptr[i] && (i < len)) {
        retarget_put_char((int)ptr[i]);
        if (ptr[i] == '\n') {
            retarget_put_char((int)'\r');
        }
        i++;
    }

    return len;
}

void _ttywrch(int ch)
{
    retarget_put_char(ch);
}

int _read(int file, char* ptr, int len)
{
    (void)file;
    int i = 0;

    for (/* Empty */; len > 0; --len) {
        char c = (char)retarget_get_char();
        *ptr++ = c;
        ++i;
        if (c == '\n')
            break;
    }

    return i;
}

#elif defined(__ICCARM__)

#include <yfuns.h>

size_t __write(int handle, const unsigned char* buffer, size_t size)
{
    size_t nChars = 0;

    if (buffer == 0) {
        return 0;
    }

    if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR) {
        return _LLIO_ERROR;
    }

    for (; size != 0; --size) {
        if (retarget_put_char(*buffer++) < 0) {
            return _LLIO_ERROR;
        }

        ++nChars;
    }
    return nChars;
}

size_t __read(int handle, unsigned char* buffer, size_t size)
{
    int nChars = 0;

    if (handle != _LLIO_STDIN) {
        return _LLIO_ERROR;
    }

    for (; size > 0; --size) {
        int c = retarget_get_char();
        if (c < 0)
            break;

        *buffer++ = c;
        ++nChars;
    }

    return nChars;
}

#elif defined(__CC_ARM)

#include <rt_misc.h>
#include <stdio.h>

#pragma import(__use_no_semihosting_swi)

#ifdef __DBG_ITM
volatile int ITM_RxBuffer = ITM_RXBUFFER_EMPTY; /*  CMSIS Debug Input        */
#endif

struct __FILE {
    int handle; /* Add whatever you need here */
};
FILE __stdout;
FILE __stdin;

int fputc(int c, FILE* f)
{
#ifdef __DBG_ITM
    ITM_SendChar(c);
    return 0;
#else
    return (retarget_put_char(c));
#endif
}

int fgetc(FILE* f)
{
    return (retarget_get_char());
}

int ferror(FILE* f)
{
    /* Your implementation of ferror */
    return EOF;
}

void _ttywrch(int c)
{
#ifdef __DBG_ITM
    ITM_SendChar(c);
#else
    retarget_put_char(c);
#endif
}

void _sys_exit(int return_code)
{
label:
    goto label; /* endless loop */
}

#endif

#endif //USE_RETARGET
