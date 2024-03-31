#!/bin/bash

echo "x86_64:"
echo "Creating sample and patching it"
x86_64-w64-mingw32-gcc -Wall -Wextra src/main.c src/secret_code.c -o sample.exe
x86_64-w64-mingw32-gcc -Wall -Wextra pe_patcher.c -o patcher.exe
wine patcher.exe sample.exe patched.exe
echo "Testing patched sample"
wine patched.exe
rm patched.exe patcher.exe  sample.exe 
echo ""

echo "x86:"
echo "Creating sample and patching it"
i686-w64-mingw32-gcc -Wall -Wextra src/main.c src/secret_code.c -o sample.exe
i686-w64-mingw32-gcc -Wall -Wextra pe_patcher.c -o patcher.exe
wine patcher.exe sample.exe patched.exe
echo "Testing patched sample"
wine patched.exe
rm patched.exe patcher.exe  sample.exe

echo "Done"
