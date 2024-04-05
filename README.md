# Malggregate

## Description
Malggregate is a repository containing various malware and/or game-protection techniques.\
The provided code serves as proof of concept (POC) and is intended for educational and research purposes only.\
It is important to note that the code in this repository is not reliable for production use and may require significant modification and testing to be deemed reliable and safe for real-world applications.

## Index of Techniques

technique | short description
-|-
[dyncrypt_function](dyncrypt_function/) | decrypt / encrypt function at runtime
[r_debug_hook](r_debug_hook/) | use _r_debug to hook process' imported function(s)

## Contribution Guidelines
Contributions to Malggregate are welcome as long as they are relevant to the repository's focus.\
Pull requests that align with the goals of the project will be considered for merging.

Since I primarily work on Linux, most of the techniques provided in this repository are made for [ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format).\
However, contributors interested in adding support for other formats, such as [PE](https://en.wikipedia.org/wiki/Portable_Executable), are welcome to do so.

## Licensing Information
Malggregate is licensed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License).\
You are free to use, modify, and distribute the code in this repository, provided you include the appropriate copyright notice and disclaimer.\
See the [LICENSE](LICENSE) file for more details.

## Disclaimer
The code provided in this repository is for educational and research purposes only.\
It is not intended for malicious use.\
Any actions taken with the code in this repository are solely the responsibility of the user.\
The author(s) of Malggregate are not liable for any damages or legal consequences resulting from the use or misuse of the code.
