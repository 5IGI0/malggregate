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
#ifndef SIG_XOR_DYNCRYPTED_FUNC_H
#define SIG_XOR_DYNCRYPTED_FUNC_H 1

#define DYNCRYPT_XOR_FUNC_SUFFIX        __fncx0r_pr0t
#define DYNCRYPT_XOR_FUNC_END_SUFFIX    __endx0r_pr0t
#define DYNCRYPT_XOR_SECTION            ".x0r_pr0t"

#define DECL__XOR_PROTECTED_SUB_SUB(_ret,_func_name,_fnc,_end,...)                      \
    __attribute__((section(DYNCRYPT_XOR_SECTION))) _ret _func_name ##_fnc __VA_ARGS__   \
    __attribute__((section(DYNCRYPT_XOR_SECTION))) void _func_name ##_end () {}
#define DECL__XOR_PROTECTED_SUB(_ret,_func_name,_fnc,_end,...) \
    DECL__XOR_PROTECTED_SUB_SUB(_ret,_func_name,_fnc,_end,__VA_ARGS__)
#define DECL_XOR_PROTECTED(_ret,_func_name,...)         \
    DECL__XOR_PROTECTED_SUB(_ret,_func_name,            \
        DYNCRYPT_XOR_FUNC_SUFFIX,                       \
        DYNCRYPT_XOR_FUNC_END_SUFFIX,__VA_ARGS__)

#define DECL__PROTOTYPE_XOR_PROTECTED_SUB_SUB(_ret,_func_name,_fnc,_end,...)    \
    _ret _func_name ##_fnc __VA_ARGS__;                                         \
    void _func_name ##_end ();
#define DECL__PROTOTYPE_XOR_PROTECTED_SUB(_ret,_func_name,_fnc,_end,...) \
    DECL__PROTOTYPE_XOR_PROTECTED_SUB_SUB(_ret,_func_name,_fnc,_end,__VA_ARGS__)
#define DECL_PROTOTYPE_XOR_PROTECTED(_ret,_func_name,...)   \
    DECL__PROTOTYPE_XOR_PROTECTED_SUB(_ret,_func_name,      \
        DYNCRYPT_XOR_FUNC_SUFFIX,                           \
        DYNCRYPT_XOR_FUNC_END_SUFFIX,__VA_ARGS__)

static inline
__attribute__((always_inline))
void dyncrypt__xor_from_to(unsigned char *from, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        from[i] ^= 0x5A;
    }
}

#define CALL__XOR_PROTECTED_SUB_SUB(_func_name,_fnc,...)    \
    _func_name ##_fnc (__VA_ARGS__)
#define CALL__XOR_PROTECTED_SUB(_func_name,_fnc,...) \
    CALL__XOR_PROTECTED_SUB_SUB(_func_name,_fnc,__VA_ARGS__)

#define CALL__XOR_XOR_PROTECTED_SUB_SUB(_func_name,_fnc,_end) \
    dyncrypt__xor_from_to((unsigned char *)_func_name##_fnc,(unsigned char *)_func_name##_end - (unsigned char *)_func_name##_fnc)
#define CALL__XOR_XOR_PROTECTED_SUB(_func_name,_fnc,_end) \
    CALL__XOR_XOR_PROTECTED_SUB_SUB(_func_name,_fnc,_end)

#define CALL_XOR_PROTECTED(_func_name,...)                                                          \
    CALL__XOR_XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,DYNCRYPT_XOR_FUNC_END_SUFFIX);  \
    CALL__XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,__VA_ARGS__);                       \
    CALL__XOR_XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,DYNCRYPT_XOR_FUNC_END_SUFFIX);

#define CALL_XOR_PROTECTED_RET(_ret,_func_name,...)                                                 \
    CALL__XOR_XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,DYNCRYPT_XOR_FUNC_END_SUFFIX);  \
    _ret = CALL__XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,__VA_ARGS__);                \
    CALL__XOR_XOR_PROTECTED_SUB(_func_name,DYNCRYPT_XOR_FUNC_SUFFIX,DYNCRYPT_XOR_FUNC_END_SUFFIX);

#endif