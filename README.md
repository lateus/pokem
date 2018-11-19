# Pokémon Mystery Dungeon Mail Generator

*Copyright (C) 2018 - Carlos Enrique Pérez Sánchez*

**Pokémon Mystery Dungeon Mail Generator (*MailGen* for short) is a tool to make your own Wonder Mail and SOS Mail, allowing you to convert a SOS Mail into a A-OK Mail and a Thank-You Mail.**

-----------------------------------------------------------------------------------------------------------------------------------

## Build instructions
The only requirement is a C Compiler. You can use the makefile that comes along with this project.  
Most Linux distros already comes with a basic equipment for developers that includes at least a C and a C++ compiler set, and also a `make` tool. If not, to install `make` and a C compiler, use the package manager of your distribution. For example, on Debian:  
`sudo apt install build-essential`  
will install a C and a C++ compiler, and also the tool `make`.  
Then you can run `make` on the directory where the project resides to build the application.  

On Mac, if you don't have GCC installed, you can install it through X-Code, it's free on the Apple Store.

On Windows, you can install GCC and use `mingw32-make` to build the project.

### More build methods
#### Qt
The project comes with a project file for Qt5. Open it in Qt Creator and click the *Build* button, or pass the project to the `qmake` tool.
#### Manual
You can manually build it by passing to a C compiler all source files. For example:
`cc -o app source1.c source2.c...`
will build an application named `app` by compiling the source files passed.

-----------------------------------------------------------------------------------------------------------------------------------

## Usage
This is a console application. To use it just open it in a terminal and pass the required parameters.  
Open it without arguments to request the *Help* menu. It's does not aim to be user-friendly, but it does aim to be as simple as possible in order to be easily readable and understandable so any developer can use it on their own projects, like, for example, building a GUI for it (I'm on it right now).

-----------------------------------------------------------------------------------------------------------------------------------

## For developers and contributors
The author uses Linux for development. You should do as well.

This is a command-line tool, also not easy to use. I'm currently developing a GUI for it. The purpose of maintain this console application is to have the main algorithm separated from any other module. GUI applications are, from their very nature, bigs and complicated, and I consider that they are not the appropriate environment for developing new algorithms. So, all the development of Mail Generators will take place here.

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
* In a function that reads from one or more parameters and writes to one or more, receive the read-only parameters last, and the write-only parameters first. This follows a world-wide logic convention pattern that anyone can understand and keep in mind while working in the code of someone else.

### General suggestions
* Calling performance is not everything. You must focus on maintenance, re-usability and portability.

-----------------------------------------------------------------------------------------------------------------------------------

***Contact info:*** `thecrowporation@gmail.com`