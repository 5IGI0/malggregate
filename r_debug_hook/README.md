# Hooking Function Using _r_debug

This technique utilizes the `_r_debug` symbol to trace back and locate the necessary relocation for hooking the desired function.\
By traversing `_r_debug`'s `link_map` to the current process's `_DYNAMIC`, it retrieves necessary information for performing the hook,\
such as symtab, strtab, and import-related relocations.

## Summary

The `_r_debug` symbol, alongside others like `_DYNAMIC`, is exported by the linker itself.\
The `_r_debug` symbol, according to the glibc [source code](https://github.com/bminor/glibc/blob/a4ed0471d71739928a0d0fa3258b3ff3b158e9b9/elf/link.h#L37), is a "legacy rendezvous point used by debuggers".\
Within `_r_debug`, there's a pointer to a `link_map`, which is essentially a list of all ELFs loaded by the linker.

The objective of this technique is to locate current process's ELF within this list and then find the relocation to modify the Global Offset Table ([GOT](https://en.wikipedia.org/wiki/Global_Offset_Table)).\
Which will allow us to point the function we aim to hook to our own function.\
It's important to note that each ELF has its own GOT table, meaning that to hook a function used in another library, it must be located within the list of loaded ELFs.
