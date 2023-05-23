# Install from source

## Dependencies
In order to compile ABRUHP you need to have at least this tools installed on your machine
- cmake (v3.26.3 or higher)
- a C++20 compiler supported by cmake

## Common steps
```bash
git clone https://github.com/moresdavidewayan/ABRUHP.git
cd ABRUHP
cmake -S . -B build
```

## Roadmap
### Compiler
- [x] lexer
- [ ] parser
- [ ] code generation

### Basic ABAP functionalities
- [x] PRINT statement
- [x] SKIP statement
- [x] LINE statement
- [ ] global variables
- [ ] forms
- [ ] functions
- [ ] type inference
- [ ] internal tables
- [ ] structures
- [ ] transparent tables
- [ ] ...
