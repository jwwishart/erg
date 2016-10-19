#clang++ -S -c erg.cpp -std=c++14 -masm=intel -o bin/erg.s
objdump --disassemble bin/erg -w -l -Mintel-mnemonic > bin/erg.asm