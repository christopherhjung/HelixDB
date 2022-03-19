#include "bitmap.h"
#include "round.h"
#include <limits.h>
#include <stdio.h>
#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#pragma once

void hex_dump (uintptr_t ofs, const void *buf_, size_t size, bool ascii)
{
    const uint8_t *buf = (const uint8_t *)buf_;
    const size_t per_line = 16; /* Maximum bytes per line. */

    while (size > 0)
    {
        size_t start, end, n;
        size_t i;

        /* Number of bytes on this line. */
        start = ofs % per_line;
        end = per_line;
        if (end - start > size)
            end = start + size;
        n = end - start;

        /* Print line. */
        printf ("%08jx  ", (uintmax_t) ROUND_DOWN (ofs, per_line));
        for (i = 0; i < start; i++)
            printf ("   ");
        for (; i < end; i++)
            printf ("%02hhx%c",
                    buf[i - start], i == per_line / 2 - 1? '-' : ' ');
        if (ascii)
        {
            for (; i < per_line; i++)
                printf ("   ");
            printf ("|");
            for (i = 0; i < start; i++)
                printf (" ");
            for (; i < end; i++)
                printf ("%c",
                        isprint (buf[i - start]) ? buf[i - start] : '.');
            for (; i < per_line; i++)
                printf (" ");
            printf ("|");
        }
        printf ("\n");

        ofs += n;
        buf += n;
        size -= n;
    }
}