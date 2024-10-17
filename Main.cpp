#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <fstream>

#include "LibSodium.h"

typedef uint32_t(__stdcall* randombytes_uniform_t)(const uint32_t upper_bound);
randombytes_uniform_t RandomBytesUniform = nullptr;

struct CharsetArgs_t
{
    bool caps = false;
    bool lower = false;
    bool numbers = false;
    bool other = false;
};

// Generates a charset based on the configuration of the user.
char* GenerateCharset(CharsetArgs_t* args)
{
    const char* lower = "abcdefghijklmnopqrstuvwxyz";
    const char* caps = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* nums = "0123456789";
    const char* others = "~!<>[{}]|;_=()";

    char* tmpCharset = new char[strlen(lower) + strlen(caps) + strlen(nums) + strlen(others) + 1];

    size_t offset = 0;
    if (args->lower)
    {
        strcpy(tmpCharset, lower);
        offset += strlen(lower);
    }
    if (args->caps)
    {
        strcpy(tmpCharset + offset, caps);
        offset += strlen(caps);
    }
    if (args->numbers)
    {
        strcpy(tmpCharset + offset, nums);
        offset += strlen(nums);
    }
    if (args->other)
    {
        strcpy(tmpCharset + offset, others);
        offset += strlen(others);
    }

    char* charset = new char[offset + 1];
    strcpy(charset, tmpCharset);
    delete[] tmpCharset;

    return charset;
}

int main(int argc, char *argv[])
{
    int length = 0;
    CharsetArgs_t charsetArgs;
    
#ifdef CLI_BUILD
    if (argc < 2)
    {
        printf("Invalid usage. Use -help for help.");
        return 1;
    } 
    else 
    {
        for (int i = 1; i < argc; ++i)
        {
            if (argv[i][0] != '-')
                continue;
            
            if (!strcmp("-help", argv[i]))
            {
                printf("-len [length of your password] : Set the lenght of the password.\n");
                printf("-caps : Use capital chars A-Z in your password.\n");
                printf("-lower : Use lowercase chars a-z in your password.\n");
                printf("-nums : Use numbers 0-9 in your password.\n");
                printf("-other : Use other characters like []/*.!.\n");
                return 0;
            } 
            else if (!strcmp("-len", argv[i]))
            {
                length = atoi(argv[i + 1]);
                continue;
            }
            else if (!strcmp("-caps", argv[i]))
            {
                charsetArgs.caps = true;
                continue;
            }
            else if (!strcmp("-lower", argv[i]))
            {
                charsetArgs.lower = true;
                continue;
            }
            else if (!strcmp("-nums", argv[i]))
            {
                charsetArgs.numbers = true;
                continue;
            }
            else if (!strcmp("-other", argv[i]))
            {
                charsetArgs.other = true;
                continue;
            }
        }
    }
#endif

    const char* charset = GenerateCharset(&charsetArgs);

    HMODULE libSodium = LoadLibraryA("libsodium.dll");
    if (libSodium == NULL) // If the dll is missing we gonna create it from the memory
    {
        std::ofstream file("libsodium.dll", std::ios::binary);
        file.write(reinterpret_cast<const char*>(libSodiumData), sizeof(libSodiumData));
        file.close();

        libSodium = LoadLibraryA("libsodium.dll");
    }

    RandomBytesUniform = reinterpret_cast<randombytes_uniform_t>(GetProcAddress(libSodium, "randombytes_uniform"));

    // allocate space for our password
    char* password = new char[length + 2];
    
    // Generating the password;
    for (int i = 0; i < length; ++i)
    {
        password[i] = charset[RandomBytesUniform(strlen(charset))];
    }

    printf("Your Password: %s", password);
    delete[] password;
    return 0;
}
