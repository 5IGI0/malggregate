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