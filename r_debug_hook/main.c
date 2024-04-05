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

#include <crypt.h>

/* cf. libprompt.c */
extern void easy_prompt(char const *prompt, char *out);

int main(void) {
                                    // supersecret123456789
    char const  *secret_password    = "$y$j75$oxKOUEr7VB56YJ56oJKPkB561186kJaQY7LNi.$h9xZtAcaGCxDxVY3Je0kioXiZvEYi1F/65nlRluRMO2";
    char        password_buff[40];

    /*  This call will hook `strcmp` with our custom `strcmp` function.
        Our custom `strcmp` will return 0 if the provided password is "ViveLaFrance!",
        thereby backdooring this dummy program. */
    easy_prompt("Password: ", password_buff);

    if (strcmp(secret_password, crypt(password_buff,secret_password)) == 0)
        puts("access granted!");
    else
        puts("access denied.");
}