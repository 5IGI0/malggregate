# Dyncrypt Function

This technique utilizes encryption to conceal its code from reverse engineers, decrypting it only when necessary.\
In our implementation, we employ a simple [XOR encryption](https://en.wikipedia.org/wiki/Exclusive_or) method to streamline the code.

## Summary

The implementation follows these steps:

- XOR-encrypted functions are stored in a designated section (`.x0r_pr0t`).
- An auxiliary function is added alongside to facilitate determining the length of the function.
- The special section is encrypted using a provided [patcher](patcher.c).
- Upon calling the function, we XOR the function's code, execute it, and then XOR it again to restore its original state.

## Improvements for Production

For production use, several enhancements can be considered:

- Employ stronger encryption algorithms (such as [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)) for improved security.
- Utilize a different encryption key for each function or compilation to enhance security.
- Ensure thread safety if the technique is to be used in multi-threaded environments.