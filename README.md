<p align="center"><img width=256 height=256 src=resources/logo/pokem.png></p>  

# PokéM - Pokémon Mystery Dungeon Mail Generator

*Copyright 2018-2020 Carlos Enrique Pérez Sánchez.*  
*Based on the tools written by Peter O.*

**Pokémon Mystery Dungeon Mail Generator, *PokéM* for short is a library to make your own Wonder Mail and SOS Mail, also allowing you to convert a SOS Mail into a A-OK Mail and a Thank-You Mail.**  

Currently, only *Red & Blue Rescue Teams* are supported.

-----------------------------------------------------------------------------------------------------------------------------------

## Usage
This is a library. To use it just link it with your application and then you can call its routines and access its data.

-----------------------------------------------------------------------------------------------------------------------------------

## Building from sources

### Requirements
The only build requirement is a C Compiler. You can use the [Makefile](Makefile) that comes along with this project.  
Most **Linux** distros already comes with a basic equipment for developers that includes GCC, or at least a C and a C++ compiler set, and also a `make` tool. If not, to install `make` and a C compiler, use the package manager of your distribution.  

* **Debian** (*apt*):  
```sh
$ sudo apt install build-essential  
```

* **Fedora**/**RHEL**/**CentOS** (*yum*):  
```sh
$ sudo yum groupinstall "C Development Tools and Libraries"
```
  
* **openSUSE** (*zypper*):  
```sh
$ sudo zypper install -t pattern devel_basis
```

These are just examples. If you use a different package manager, you must search for the corresponding package in your distribution.

That will install a C and a C++ compiler, and also the tool `make`.  

### Building
Then you can run `make` by opening the terminal on the project's directory to build the application:  
`$ make`  

This will execute `make all` that builds the library as well as the examples.

Type `help` to see the available targets:
`$ make help`

On **MacOS**, if you don't have GCC installed, you can install it through X-Code, it's free on the Apple Store.

On **Windows**, you can install GCC and use `mingw32-make` to build the project.

-----------------------------------------------------------------------------------------------------------------------------------

## Known bugs
* Currently, the `Makefile` is only fully supported on **UNIX**. On **Windows**, you will be able to build the static library and examples, but you must manually erase all leftovers prior to rebuild, since `clean` is not available, as it fails due to **Windows** paths conventions. Also, some text outputs are buggy.

-----------------------------------------------------------------------------------------------------------------------------------

## License
This program is under the *General Public License* (version 2).  

-----------------------------------------------------------------------------------------------------------------------------------

## For developers and contributors
The author uses **Linux** for development. You should do as well.  

This is a library. I'm currently developing a GUI for it. The purpose of maintain this library is to have the main algorithm separated from any other module. GUI applications are, from their very nature, big and complicated, and I consider that they are not the appropriate environment for developing new algorithms. So, all the development of Mail Generators will take place here. GUI applications should use a library of ***PokéM*** (available through `$ make staticlib`), instead of using the source code directly because then will be easier to update the related algorithms when a new version of ***PokéM*** is released.

### Portability tips
* Avoid using fast assembler instructions, compiler's built-in functions and others things that can reduce portability.
* Use pure and neutral ANSI C Standard Library.

### Good programming practices
* Follow the whole program indentation style and brackets:
    1. Indent using spaces instead of tabs. Moderns code editor allows you to setting that.
    2. Use 4 spaces indentation.
    3. In functions, the opening bracket is located at the beginning of the line next to the function signature.
    4. In for loops, switches, if statements, etc., the opening bracket is located after a space next to the respective statement.
    5. Warnings must be errors for you.
* Follow the Model-View-Controller (MVC) design pattern.
* In a function that reads from one or more parameters and writes to one or more, receive the read-only parameters last, and the write-only parameters first. This keeps the logic pattern consistent with the rest of the code.

### General suggestions
* Calling performance is not everything. You must focus on maintenance, re-usability and portability.

-----------------------------------------------------------------------------------------------------------------------------------

***Contact info:*** [*thecrowporation@gmail.com*](mailto:thecrowporation@gmail.com)
