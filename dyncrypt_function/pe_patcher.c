/**
 * Copyright (c) 2024 0xC_M0NK3Y / Timothee Escandell
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>

#include <windows.h>

#include "include/xor_dyncrypted.h"

int main(int argc, char **argv) {
    assert(argc == 3);

    assert(sizeof(DYNCRYPT_XOR_SECTION) <= 8 && "xored section name too long for PE");
    
    FILE *fp = fopen(argv[1], "rb");
    assert(fp);

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    uint8_t *pe = malloc(size);
    assert(pe);

    fread(pe, 1, size, fp);
    fclose(fp);

    PIMAGE_DOS_HEADER     dos   = (void *)pe;
    PIMAGE_NT_HEADERS     nt    = (void *)(pe + dos->e_lfanew);
    PIMAGE_SECTION_HEADER sec   = (void *)(IMAGE_FIRST_SECTION(nt));
    int                   found = 0;
    
    for (size_t i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        if (strcmp((char *)sec[i].Name, DYNCRYPT_XOR_SECTION) == 0) {
            found = 1;
            sec[i].Characteristics |= IMAGE_SCN_MEM_WRITE;
            for (size_t j = 0; j < sec[i].SizeOfRawData; j++)
                (pe + sec[i].PointerToRawData)[j] ^= DYNCRYPT_XOR_KEY;
        }
    }

    assert(found && "xored section not found");
    
    fp = fopen(argv[2], "wb");
    assert(fp);
    fwrite(pe, 1, size, fp);
    fclose(fp);    
    
    return 0;
}
