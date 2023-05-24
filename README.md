# ARBUHP
A programming language and a source-to-source compiler for those who find ABAP frustrating.

## Index

- [Install from source](#install-from-source)
    - [Dependencies](#dependencies)
    - [Common steps](#common-steps)
- [Roadmap](#roadmap)
    - [Compiler](#compiler)
    - [Basic ABAP functionalities](#basic-abap-functionalities)

## Install from source

### Dependencies
In order to compile ABRUHP you need to have at least this tools installed on your machine.

**Windows**
- [CMake](https://cmake.org/download/) (v3.26.3 or higher)
- [Visual Studio Build Tools 2019](https://visualstudio.microsoft.com/downloads/) (v16.11.25 or higher)


### Common steps
```bash
git clone https://github.com/moresdavidewayan/ABRUHP.git
cd ABRUHP
cmake -S . -B build
```

## Roadmap
### Compiler
- [x] lexer
- [x] parser
- [ ] code generation
- [ ] compile-time optimizations
- [ ] runtime optimizations

### Basic ABAP functionalities
- [x] PRINT statement
- [x] SKIP statement
- [x] LINE statement
- [x] line comments
- [ ] inline comments
- [ ] global variables
- [ ] forms
- [ ] functions
- [ ] type inference
- [ ] internal tables
- [ ] structures
- [ ] transparent tables
- [ ] ...
