# Password generator

A very simple password generator with some customizability (Password length and choose what characters to use). For secure randomization is [LibSodium](https://doc.libsodium.org/) being used.

## Features

- Creation of libraries from memory, so no need to download any external files except the password generator.
- customizability
  - Password lenght
  - Choose charset e.g. a-b (lowercase) A-Z (capital) 0-9 (numbers) [=}' (other characters)
 
## Compiling

Before compiling you need to have [CMake](https://cmake.org/) and [Visual Studio](https://visualstudio.microsoft.com/) installed.

1. Open cmd and write `git clone https://github.com/Jason4225/Password-Generator.git`
2. Run `Build CLI.bat`
3. Enjoy!

## Usage

`PasswordGenCli.exe` + args

### Arguments
-len [length of your password] : Set the lenght of the password.
-caps : Use capital chars A-Z in your password.
-lower : Use lowercase chars a-z in your password.
-nums : Use numbers 0-9 in your password.
-other : Use other characters like []/*.!.

# Todo

1. Gui version
