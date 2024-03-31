/**
 * Copyright (c) 2024 5IGI0 / Ethan. L. C. Lorenzetti
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
#include <string.h>
#include <assert.h>

#include <elf.h>

#ifdef ELF64
#define Elf(x) Elf64_##x
#else
#define Elf(x) Elf32_##x
#endif

int main(int argc, char **argv) {
    assert(argc == 3);

    FILE *fp = fopen(argv[1], "rb");
    assert(fp);

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    uint8_t *elf = malloc(size);
    assert(elf);

    fread(elf, 1, size, fp);
    fclose(fp);

    Elf(Ehdr)   *ehdr       = (void*)elf;
    Elf(Shdr)   *shdr       = (void*)(elf+ehdr->e_shoff);
    Elf(Phdr)   *phdr       = (void*)(elf+ehdr->e_phoff);
    Elf(Addr)   sec_vaddr   = (Elf(Addr))-1;
    char        *sec_names  = (char *)(elf+shdr[ehdr->e_shstrndx].sh_offset);

    for (size_t i = 0; i < ehdr->e_shnum; i++) {
        if (strcmp(sec_names+shdr[i].sh_name,".x0r_pr0t") == 0) {
            sec_vaddr = shdr[i].sh_addr;
            shdr[i].sh_flags |=SHF_WRITE;
            for (size_t y = 0; y < shdr[i].sh_size; y++) {
                (elf+shdr[i].sh_offset)[y] ^= 0x5A;
            }
        }
    }

    assert(sec_vaddr != (Elf(Addr))-1 && ".x0r_pr0t not found");

    int suc = 0;
    for (size_t i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_vaddr <= sec_vaddr && (phdr[i].p_vaddr + phdr[i].p_memsz) >= sec_vaddr) {
            phdr[i].p_flags |= PF_W|PF_X|PF_R;
            suc = 1;
        }
    }
    assert(suc && ".x0r_pr0t-related program header not found");
    
    fp = fopen(argv[2], "wb");
    assert(fp);
    fwrite(elf, 1, size, fp);
    fclose(fp);
}
