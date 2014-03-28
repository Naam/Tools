/*
xor is a small to to apply the binary addition with a choosen key
onto a stream.
Copyright (C) 2014 Naam

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xor.h"

#define     BUFFER_SIZE     1024


int
main    (int argc, char *argv[])
{
    FILE    *input, *output;

    if (argc != 2) {
        if (argc != 4) {
            fprintf(stderr,
                    "Usage: %s [input_file] [output_file] <key>\n",
                    argv[0]
                    );
            exit(1);
        }
    }
    input   = (argc > 2)?fopen(argv[2], "r"):stdin;
    output  = (argc > 2)?fopen(argv[3], "w"):stdout;
    if (!(input && output)) {
        fprintf(stderr, "Input/Output file error\n");
        exit(1);
    }
    myxor(input, output, argv[1]);
    fclose(input);
    fclose(output);

    return 0;
}

unsigned int
myxor     (FILE *input, FILE *output, char *key)
{
    unsigned        counter, size;
    char            buffer[BUFFER_SIZE], key_item;
    size_t          key_len;

    fseek(input, 0L, SEEK_END);
    size = ftell(input);
    rewind(input);
    key_len = strlen(key);
    setbuf(output, NULL);
    do {
        counter = fread(buffer, 1, BUFFER_SIZE, input);
        for (int i = 0; i < counter; i++) {
            key_item = key[i % key_len];
            buffer[i] ^= key_item;
        }
        fwrite(buffer, counter, 1, output);
    } while (counter > 0);

    return counter;
}
