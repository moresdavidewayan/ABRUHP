<h1 align="center">ABRUHP</h1>

<div align="center">
<img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/moresdavidewayan/ABRUHP/main_branch.yml?style=for-the-badge">
<img alt="GitHub" src="https://img.shields.io/github/license/moresdavidewayan/ABRUHP?style=for-the-badge">
<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/moresdavidewayan/ABRUHP?style=for-the-badge">
</div>
A programming language and a source-to-source compiler aimed at fixing ABAP's horrible syntax.

## Install from source

### Dependencies
In order to compile ABRUHP you need to have at least this tools installed on your machine.

**Windows**
- [CMake](https://cmake.org/download/) (v3.26.3 or higher)
- [Visual Studio Build Tools 2019](https://visualstudio.microsoft.com/downloads/) (v16.11.25 or higher)

**Linux**
- [CMake](https://cmake.org/download/) (v3.26.3 or higher)
- [gcc](https://gcc.gnu.org/) (v13.1.1 or higher)


### Build

**Common steps**
```bash
git clone https://github.com/moresdavidewayan/ABRUHP.git
cd ABRUHP
cmake -S . -B build
```

**Linux**
```bash
cd build
make
```

## Roadmap
### Compiler
- [x] lexer
- [x] parser
- [x] code generation
- [ ] compile-time optimizations

### Basic ABAP functionalities
- [x] PRINT statement
- [x] SKIP statement
- [x] LINE statement
- [ ] variable declaration
- [ ] line comments
- [ ] inline comments
- [ ] global variables
- [ ] forms
- [ ] functions
- [ ] type inference
- [ ] internal tables
- [ ] structures
- [ ] transparent tables
- [ ] ...

### Data types
- [ ] byte field
- [ ] text field
- [ ] integer
- [ ] floating point
- [ ] packed number
- [ ] text string
