#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

int Disassemble8080Op(unsigned char*, int);

int main(int argc, char* argv[])
{
    FILE *f= fopen(argv[1], "rb");
    if (f==NULL)
    {    
        printf("error: Couldn't open %s\n", argv[1]);
        exit(1);
    }
      
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);    

    unsigned char* characterBuffer = new unsigned char[fsize];

    fread(characterBuffer, fsize, 1, f);
    fclose(f);

    int pc = 0;

    while(pc < fsize)
    {
        pc += Disassemble8080Op(characterBuffer, pc);
    }

    delete[] characterBuffer;
    return 0;
}

int Disassemble8080Op(unsigned char* characterBuffer, int pc)
{
    unsigned char* code = &characterBuffer[pc];
    int opbytes = 1;
    printf("%04x\t", pc);
    switch(*code)
    {
        case 0x00: printf("NOP");   break;//no operation
        case 0x01: printf("LXI\t\tB,#$%02x%02x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair BC
        case 0x02: printf("STAX\tB");   break;//store value in register A at address in register pair BC
        case 0x03: printf("INX\t\tB");    break;//increment register pair BC NO FLAG SET
        case 0x04: printf("INR\t\tB");    break;//increment register B by 1 CARRY FLAG NOT SET
        case 0x05: printf("DCR\t\tB");    break;//decrement register B by 1 CARRY FLAG NOT SET
        case 0x06: printf("MVI\t\tB,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register B
        case 0x07: printf("RLC");   break;//register A is rotated left where the carry bit and low order bit are set to the previous high order bit ONLY CARRY FLAG IS SET
        case 0x08: printf("NOP");   break;//no operation
        case 0x09: printf("DAD\t\tB");    break;//add register pair BC to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x0a: printf("LDAX\tB");   break;//load value at address in register pair BC to register A
        case 0x0b: printf("DCX\t\tB");    break;//decrement register pair BC NO FLAG SET
        case 0x0c: printf("INR\t\tC");    break;//increment register C by 1 CARRY FLAG NOT SET
        case 0x0d: printf("DCR\t\tC");    break;//decrement register C by 1 CARRY FLAG NOT SET
        case 0x0e: printf("MVI\t\tC,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register C
        case 0x0f: printf("RRC");   break;//register A is rotated right where the carry bit and high order bit are set to the previous low order bit ONLY CARRY FLAG IS SET

        case 0x10: printf("NOP");   break;//no operation
        case 0x11: printf("LXI\t\tD,#$%02x%02x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair DE
        case 0x12: printf("STAX\tD");   break;//store value in register A at address in register pair DE
        case 0x13: printf("INX\t\tD");    break;//increment register pair DE NO FLAG SET
        case 0x14: printf("INR\t\tD");    break;//increment register D by 1 CARRY FLAG NOT SET
        case 0x15: printf("DCR\t\tD");    break;//decrement register D by 1 CARRY FLAG NOT SET
        case 0x16: printf("MVI\t\tD,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register D
        case 0x17: printf("RAL");   break;//register A is rotated left through carry where the low order bit is set to previous carry and carry is set to previous high order bit ONLY CARRY FLAG IS SET
        case 0x18: printf("NOP");   break;//no operation
        case 0x19: printf("DAD\t\tD");    break;//add register pair DE to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x1a: printf("LDAX\tD");   break;//load value at address in register pair DE to register A
        case 0x1b: printf("DCX\t\tD");    break;//decrement register pair DE NO FLAG SET
        case 0x1c: printf("INR\t\tE");    break;//increment register E by 1 CARRY FLAG NOT SET
        case 0x1d: printf("DCR\t\tE");    break;//decrement register E by 1 CARRY FLAG NOT SET
        case 0x1e: printf("MVI\t\tE,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register E
        case 0x1f: printf("RAR");   break;//register A is rotated left through carry where the high order bit is set to previous carry and carry is set to previous low order bit ONLY CARRY FLAG IS SET

        case 0x20: printf("NOP");   break;//no operation
        case 0x21: printf("LXI\t\tH,#$%02x%02x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair HL
        case 0x22: printf("SHLD\t$%02x%02x", code[2], code[1]); opbytes = 3;    break;//store value of register L at address and value of register H at address + 1
        case 0x23: printf("INX\t\tH");    break;//increment register pair HL NO FLAG SET
        case 0x24: printf("INR\t\tH");    break;//increment register H by 1 CARRY FLAG NOT SET
        case 0x25: printf("DCR\t\tH");    break;//decrement register H by 1 CARRY FLAG NOT SET
        case 0x26: printf("MVI\t\tH,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register H
        case 0x27: printf("DAA");   break;//adjust accumulator to form 2 four bit binary coded decimal digits
        case 0x28: printf("NOP");   break;//no operation
        case 0x29: printf("DAD\t\tH");    break;//add register pair HL to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x2a: printf("LHLD\t$%02x%02x", code[2], code[1]);    opbytes = 3;    break;//load value at address to register L and value at address + 1 to register H
        case 0x2b: printf("DCX\t\tH");    break;//decrement register pair HL NO FLAG SET
        case 0x2c: printf("INR\t\tL");    break;//increment register L by 1 CARRY FLAG NOT SET
        case 0x2d: printf("DCR\t\tL");    break;//decrement register L by 1 CARRY FLAG NOT SET
        case 0x2e: printf("MVI\t\tL,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register L
        case 0x2f: printf("CMA");   break;//register A is set to complement (0<->1) NO FLAGS ARE SET

        case 0x30: printf("NOP");   break;//no operation
        case 0x31: printf("LXI\t\tSP,#$%02x%02x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair SP (Stack pointer)
        case 0x32: printf("STA\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//store value in register A at address
        case 0x33: printf("INX\t\tSP");   break;//increment register pair SP (Stack pointer) NO FLAG SET
        case 0x34: printf("INR\t\tM");    break;//increment memory location (H)(L) by 1 CARRY FLAG NOT SET
        case 0x35: printf("DCR\t\tM");    break;//decrement memory location (H)(L) by 1 CARRY FLAG NOT SET
        case 0x36: printf("MVI\t\tM,#$%02x", code[1]);  opbytes = 2;    break;//move data value to memory location (H)(L)
        case 0x37: printf("STC");   break;//set carry flag to 1 NO OTHER FLAGS ARE SET
        case 0x38: printf("NOP");   break;//no operation
        case 0x39: printf("DAD\t\tSP");   break;//add register pair SP (Stack poiinter) to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x3a: printf("LDA\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//load value at address to register A
        case 0x3b: printf("DCX\t\tSP");   break;//decrement register pair BSP(Stack pointer) NO FLAG SET
        case 0x3c: printf("INR\t\tA");    break;//increment register A by 1 CARRY FLAG NOT SET
        case 0x3d: printf("DCR\t\tA");    break;//decrement register A by 1 CARRY FLAG NOT SET
        case 0x3e: printf("MVI\t\tA,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register A
        case 0x3f: printf("CMC");   break;//carry flag is set to complement (0<->1) NO OTHER FLAGS ARE SET

        case 0x40: printf("MOV\t\tB,B");    break; //move register B to register B
        case 0x41: printf("MOV\t\tB,C");    break; //move register C to register B
        case 0x42: printf("MOV\t\tB,D");    break; //move register D to register B
        case 0x43: printf("MOV\t\tB,E");    break; //move register E to register B
        case 0x44: printf("MOV\t\tB,H");    break; //move register H to register B
        case 0x45: printf("MOV\t\tB,L");    break; //move register L to register B
        case 0x46: printf("MOV\t\tB,M");    break; //move memory location (H)(L) to register B
        case 0x47: printf("MOV\t\tB,A");    break; //move register A to register B
        case 0x48: printf("MOV\t\tC,B");    break; //move register B to register C
        case 0x49: printf("MOV\t\tC,C");    break; //move register C to register C
        case 0x4a: printf("MOV\t\tC,D");    break; //move register D to register C
        case 0x4b: printf("MOV\t\tC,E");    break; //move register E to register C
        case 0x4c: printf("MOV\t\tC,H");    break; //move register H to register C
        case 0x4d: printf("MOV\t\tC,L");    break; //move register L to register C
        case 0x4e: printf("MOV\t\tC,M");    break; //move memory location (H)(L) to register C
        case 0x4f: printf("MOV\t\tC,A");    break; //move register A to register C

        case 0x50: printf("MOV\t\tD,B");    break; //move register B to register D
        case 0x51: printf("MOV\t\tD,C");    break; //move register C to register D
        case 0x52: printf("MOV\t\tD,D");    break; //move register D to register D
        case 0x53: printf("MOV\t\tD,E");    break; //move register E to register D
        case 0x54: printf("MOV\t\tD,H");    break; //move register H to register D
        case 0x55: printf("MOV\t\tD,L");    break; //move register L to register D
        case 0x56: printf("MOV\t\tD,M");    break; //move memory location (H)(L) to register D
        case 0x57: printf("MOV\t\tD,A");    break; //move register A to register D
        case 0x58: printf("MOV\t\tE,B");    break; //move register B to register E
        case 0x59: printf("MOV\t\tE,C");    break; //move register C to register E
        case 0x5a: printf("MOV\t\tE,D");    break; //move register D to register E
        case 0x5b: printf("MOV\t\tE,E");    break; //move register E to register E
        case 0x5c: printf("MOV\t\tE,H");    break; //move register H to register E
        case 0x5d: printf("MOV\t\tE,L");    break; //move register L to register E
        case 0x5e: printf("MOV\t\tE,M");    break; //move memory location (H)(L) to register E
        case 0x5f: printf("MOV\t\tE,A");    break; //move register A to register E

        case 0x60: printf("MOV\t\tH,B");    break; //move register B to register H
        case 0x61: printf("MOV\t\tH,C");    break; //move register C to register H
        case 0x62: printf("MOV\t\tH,D");    break; //move register D to register H
        case 0x63: printf("MOV\t\tH,E");    break; //move register E to register H
        case 0x64: printf("MOV\t\tH,H");    break; //move register H to register H
        case 0x65: printf("MOV\t\tH,L");    break; //move register L to register H
        case 0x66: printf("MOV\t\tH,M");    break; //move memory location (H)(L) to register H
        case 0x67: printf("MOV\t\tH,A");    break; //move register A to register H
        case 0x68: printf("MOV\t\tL,B");    break; //move register B to register L
        case 0x69: printf("MOV\t\tL,C");    break; //move register C to register L
        case 0x6a: printf("MOV\t\tL,D");    break; //move register D to register L
        case 0x6b: printf("MOV\t\tL,E");    break; //move register E to register L
        case 0x6c: printf("MOV\t\tL,H");    break; //move register H to register L
        case 0x6d: printf("MOV\t\tL,L");    break; //move register L to register L
        case 0x6e: printf("MOV\t\tL,M");    break; //move memory location (H)(L) to register L
        case 0x6f: printf("MOV\t\tL,A");    break; //move register A to register L

        case 0x70: printf("MOV\t\tM,B");    break; //move register B to memory location at (H)(L)
        case 0x71: printf("MOV\t\tM,C");    break; //move register C to memory location at (H)(L)
        case 0x72: printf("MOV\t\tM,D");    break; //move register D to memory location at (H)(L)
        case 0x73: printf("MOV\t\tM,E");    break; //move register E to memory location at (H)(L)
        case 0x74: printf("MOV\t\tM,H");    break; //move register H to memory location at (H)(L)
        case 0x75: printf("MOV\t\tM,L");    break; //move register L to memory location at (H)(L)
        case 0x76: printf("HLT");         break; //processors stops and program is halted
        case 0x77: printf("MOV\t\tM,A");    break; //move register A to memory location at (H)(L)
        case 0x78: printf("MOV\t\tA,B");    break; //move register B to register A
        case 0x79: printf("MOV\t\tA,C");    break; //move register C to register A
        case 0x7a: printf("MOV\t\tA,D");    break; //move register D to register A
        case 0x7b: printf("MOV\t\tA,E");    break; //move register E to register A
        case 0x7c: printf("MOV\t\tA,H");    break; //move register H to register A
        case 0x7d: printf("MOV\t\tA,L");    break; //move register L to register A
        case 0x7e: printf("MOV\t\tA,M");    break; //move memory location (H)(L) to register A
        case 0x7f: printf("MOV\t\tA,A");    break; //move register A to register A

        case 0x80: printf("ADD\t\tB");    break;//add register B to register A
        case 0x81: printf("ADD\t\tC");    break;//add register C to register A
        case 0x82: printf("ADD\t\tD");    break;//add register D to register A
        case 0x83: printf("ADD\t\tE");    break;//add register E to register A
        case 0x84: printf("ADD\t\tH");    break;//add register H to register A
        case 0x85: printf("ADD\t\tL");    break;//add register L to register A
        case 0x86: printf("ADD\t\tM");    break;//add memory location at (H)(L) to register A
        case 0x87: printf("ADD\t\tA");    break;//add register A to register A
        case 0x88: printf("ADC\t\tB");    break;//add register B and carry bit to register A
        case 0x89: printf("ADC\t\tC");    break;//add register C and carry bit to register A
        case 0x8a: printf("ADC\t\tD");    break;//add register D and carry bit to register A
        case 0x8b: printf("ADC\t\tE");    break;//add register E and carry bit to register A
        case 0x8c: printf("ADC\t\tH");    break;//add register H and carry bit to register A
        case 0x8d: printf("ADC\t\tL");    break;//add register L and carry bit to register A
        case 0x8e: printf("ADC\t\tM");    break;//add memory location (H)(L) and carry bit to register A
        case 0x8f: printf("ADC\t\tA");    break;//add register A and carry bit to register A

        case 0x90: printf("SUB\t\tB");    break;//subtract register B from register A
        case 0x91: printf("SUB\t\tC");    break;//subtract register C from register A
        case 0x92: printf("SUB\t\tD");    break;//subtract register D from register A
        case 0x93: printf("SUB\t\tE");    break;//subtract register E from register A
        case 0x94: printf("SUB\t\tH");    break;//subtract register H from register A
        case 0x95: printf("SUB\t\tL");    break;//subtract register L from register A
        case 0x96: printf("SUB\t\tM");    break;//subtract memory location (H)(L) from register A
        case 0x97: printf("SUB\t\tA");    break;//subtract register A from register A
        case 0x98: printf("SBB\t\tB");    break;//subtract register B and carry bit from register A
        case 0x99: printf("SBB\t\tC");    break;//subtract register C and carry bit from register A
        case 0x9a: printf("SBB\t\tD");    break;//subtract register D and carry bit from register A
        case 0x9b: printf("SBB\t\tE");    break;//subtract register E and carry bit from register A
        case 0x9c: printf("SBB\t\tH");    break;//subtract register H and carry bit from register A
        case 0x9d: printf("SBB\t\tL");    break;//subtract register L and carry bit from register A
        case 0x9e: printf("SBB\t\tM");    break;//subtract memory location (H)(L) and carry bit from register A
        case 0x9f: printf("SBB\t\tA");    break;//subtract register A and carry bit from register A

        case 0xa0: printf("ANA\t\tB");    break;//AND register B with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa1: printf("ANA\t\tC");    break;//AND register C with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa2: printf("ANA\t\tD");    break;//AND register D with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa3: printf("ANA\t\tE");    break;//AND register E with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa4: printf("ANA\t\tH");    break;//AND register H with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa5: printf("ANA\t\tL");    break;//AND register L with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa6: printf("ANA\t\tM");    break;//AND data at memory location (H)(L) with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa7: printf("ANA\t\tA");    break;//AND register A with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa8: printf("XRA\t\tB");    break;//exclusive OR register B with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xa9: printf("XRA\t\tC");    break;//exclusive OR register C with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xaa: printf("XRA\t\tD");    break;//exclusive OR register D with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xab: printf("XRA\t\tE");    break;//exclusive OR register E with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xac: printf("XRA\t\tH");    break;//exclusive OR register H with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xad: printf("XRA\t\tL");    break;//exclusive OR register L with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xae: printf("XRA\t\tM");    break;//exclusive OR data at memory location (H)(L) with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xaf: printf("XRA\t\tA");    break;//exclusive OR register A with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED

        case 0xb0: printf("ORA\t\tB");    break;//inclusive OR register B with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb1: printf("ORA\t\tC");    break;//inclusive OR register C with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb2: printf("ORA\t\tD");    break;//inclusive OR register D with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb3: printf("ORA\t\tE");    break;//inclusive OR register E with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb4: printf("ORA\t\tH");    break;//inclusive OR register H with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb5: printf("ORA\t\tL");    break;//inclusive OR register L with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb6: printf("ORA\t\tM");    break;//inclusive OR data at memory location (H)(L) with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb7: printf("ORA\t\tA");    break;//inclusive OR register A with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb8: printf("CMP\t\tB");    break;//subtract register B from register A Z FLAG SET TO 1 IF A = B AND CARRY FLAG IS SET TO 1 IF A < B
        case 0xb9: printf("CMP\t\tC");    break;//subtract register C from register A Z FLAG SET TO 1 IF A = C AND CARRY FLAG IS SET TO 1 IF A < C
        case 0xba: printf("CMP\t\tD");    break;//subtract register D from register A Z FLAG SET TO 1 IF A = D AND CARRY FLAG IS SET TO 1 IF A < D
        case 0xbb: printf("CMP\t\tE");    break;//subtract register E from register A Z FLAG SET TO 1 IF A = E AND CARRY FLAG IS SET TO 1 IF A < E
        case 0xbc: printf("CMP\t\tH");    break;//subtract register H from register A Z FLAG SET TO 1 IF A = H AND CARRY FLAG IS SET TO 1 IF A < H
        case 0xbd: printf("CMP\t\tL");    break;//subtract register L from register A Z FLAG SET TO 1 IF A = L AND CARRY FLAG IS SET TO 1 IF A < L
        case 0xbe: printf("CMP\t\tM");    break;//subtract data at memory location (H)(L) from register A Z FLAG SET TO 1 IF A = M AND CARRY FLAG IS SET TO 1 IF A < M
        case 0xbf: printf("CMP\t\tA");    break;//subtract register A from register A Z FLAG SET TO 1 IF A = A AND CARRY FLAG IS SET TO 1 IF A < A

        case 0xc0: printf("RNZ\t\t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//bruh if zero flag is 0
        case 0xc1: printf("POP\t\tB");   break;//pop contents off of stack into register pair BC and adjust stack pointer
        case 0xc2: printf("JNZ\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//jump to address if zero flag is 0
        case 0xc3: printf("JMP\t\t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//jump unconditional
        case 0xc4: printf("CNZ\t\t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//bruh if zero flag is 0
        case 0xc5: printf("PUSH\tB");   break;//push contents of register pair BC onto stack and adjust stack pointer
        case 0xc6: printf("ADI\t\t#$%02x", code[1]);  opbytes = 2;    break;//add data value to register A
        case 0xc7: printf("RST\t\t0");    break;//call instruction at address $00
        case 0xc8: printf("RZ\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if zero flag is 1
        case 0xc9: printf("RET");   break;//bruh
        case 0xca: printf("JZ\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//jump to address if zero flag is 1
        case 0xcb: break;
        case 0xcc: printf("CZ\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if zero flag is 1
        case 0xcd: printf("CALL\t$%02x%02x", code[2], code[1]); opbytes = 3;    break;//bruh
        case 0xce: printf("ACI\t\t#$%02x", code[1]);  opbytes = 2;    break;//add data value and carry bit to register A
        case 0xcf: printf("RST\t\t1");    break;//call instruction at address $08

        case 0xd0: printf("RNC\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if carry flag is 0
        case 0xd1: printf("POP\t\tD");   break;//pop contents off of stack into register pair DE and adjust stack pointer
        case 0xd2: printf("JNC\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//jump to address if carry flag is 0
        case 0xd3: printf("OUT\t\t#$%02x", code[1]);  opbytes = 2;    break;//register A is moved to data bus
        case 0xd4: printf("CNC\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if carry flag is 0
        case 0xd5: printf("PUSH\tD");   break;//push contents of register pair DE onto stack and adjust stack pointer
        case 0xd6: printf("SUI\t\t#$%02x", code[1]);  opbytes = 2;    break;//subtract data value from register A
        case 0xd7: printf("RST\t\t2");    break;//call instruction at address $10
        case 0xd8: printf("RC\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if carry flag is 1
        case 0xd9: break;
        case 0xda: printf("JC\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//jump to address if carry flag is 1
        case 0xdb: printf("IN\t\t#$%02x", code[1]);   opbytes = 2;    break;//data on bus is moved to register A
        case 0xdc: printf("CC\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if carry flag is 1
        case 0xdd: break;
        case 0xde: printf("SBI\t\t#$%02x", code[1]);  opbytes = 2;    break;//subtract data value and carry bit from register A
        case 0xdf: printf("RST\t\t3");    break;//call instruction at address $18

        case 0xe0: printf("RPO\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 0
        case 0xe1: printf("POP\t\tH");   break;//pop contents off of stack into register pair HL and adjust stack pointer
        case 0xe2: printf("JPO\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//jump to address if parity flag is 0
        case 0xe3: printf("XTHL");  break;//swap register pair HL with SP (Stack pointer)
        case 0xe4: printf("CPO\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 0
        case 0xe5: printf("PUSH\tH");   break;//push contents of register pair HL onto stack and adjust stack pointer
        case 0xe6: printf("ANI\t\t#$%02x", code[1]);  opbytes = 2;    break;//AND data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xe7: printf("RST\t\t4");    break;//call instruction at address $20
        case 0xe8: printf("RPE\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 1
        case 0xe9: printf("PCHL");  break;//set program counter to register pair HL (jump to HL)
        case 0xea: printf("JPE\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//jump to address if parity flag is 1
        case 0xeb: printf("XCHG");  break;//contents in register pair HL are swapped with register pair DE
        case 0xec: printf("CPE\t\t$%02x%02x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 1
        case 0xed: break;
        case 0xee: printf("XRI\t\t#$%02x", code[1]);  opbytes = 2;    break;//exclusive OR data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xef: printf("RST\t\t5");    break;//call instruction at address $28
        
        case 0xf0: printf("RP\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 0
        case 0xf1: printf("POP\t\tPSW");  break;//pop register A and status word[S|Z|0|AC|0|P|1|CY] off of stack and adjust stack pointer
        case 0xf2: printf("JP\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//jump to address if sign flag is 0
        case 0xf3: printf("DI");    break;//disable interrupts after instruction
        case 0xf4: printf("CP\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 0
        case 0xf5: printf("PUSH\tPSW"); break;//push register A and status word[S|Z|0|AC|0|P|1|CY] onto stack and adjust stack pointer
        case 0xf6: printf("ORI\t\t#$%02x", code[1]);  opbytes = 2;    break;//inclusive OR data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xf7: printf("RST\t\t6");    break;//call instruction at address $30
        case 0xf8: printf("RM\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 1
        case 0xf9: printf("SPHL");  break;//move register pair HL to SP (Stack pointer)
        case 0xfa: printf("JM\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//jump to address if sign flag is 1
        case 0xfb: printf("EI");    break;//enable interrupts after instruction
        case 0xfc: printf("CM\t\t$%02x%02x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 1
        case 0xfd: break;
        case 0xfe: printf("CPI\t\t#$%02x", code[1]);  opbytes = 2;    break;//subtract data from register A Z FLAG SET TO 1 IF A = data AND CARRY FLAG IS SET TO 1 IF A < data
        case 0xff: printf("RST\t\t7");    break;//call instruction at address $38
        default:
            break;
    }
    cout << endl;
    return opbytes;
}