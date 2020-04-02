#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

int Disassemble8080Op(char*, int);

int main(int argc, char* argv[])
{
    ifstream fin;
    streampos size;
    char* characterBuffer;

    fin.open(argv[1], ios::binary|ios::ate);    //open file at end
    if(fin.is_open())
    {
        size = fin.tellg();
        characterBuffer = new char[size];
        fin.seekg(0, fin.beg);
        fin.read(characterBuffer, size);        //copy file into charcater buffer
        fin.close();
    }else{
        cout << "File " << argv[1] << " unable to be opened";
    }

    int pc = 0;

    while(pc < size)
    {
        pc += Disassemble8080Op(characterBuffer, pc);
    }

    delete[] characterBuffer;
    return 0;
}

int Disassemble8080Op(char* characterBuffer, int pc)
{
    char* code = &characterBuffer[pc];
    int opbytes = 1;
    printf("%04x ", pc);
    switch(*code)
    {
        case 0x00: break;
        case 0x01: printf("LXI/tB,#$%20x%20x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair BC
        case 0x02: printf("STAX/tB");   break;//store value in register A at address in register pair BC
        case 0x03: printf("INX/tB");    break;//increment register pair BC NO FLAG SET
        case 0x04: printf("INR/tB");    break;//increment register B by 1 CARRY FLAG NOT SET
        case 0x05: printf("DCR/tB");    break;//decrement register B by 1 CARRY FLAG NOT SET
        case 0x06: printf("MVI/tB,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register B
        case 0x07: printf("RLC");   break;//register A is rotated left where the carry bit and low order bit are set to the previous high order bit ONLY CARRY FLAG IS SET
        case 0x08: break;
        case 0x09: printf("DAD/tB");    break;//add register pair BC to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x0a: printf("LDAX/tB");   break;//load value at address in register pair BC to register A
        case 0x0b: printf("DCX/tB");    break;//decrement register pair BC NO FLAG SET
        case 0x0c: printf("INR/tC");    break;//increment register C by 1 CARRY FLAG NOT SET
        case 0x0d: printf("DCR/tC");    break;//decrement register C by 1 CARRY FLAG NOT SET
        case 0x0e: printf("MVI/tC,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register C
        case 0x0f: printf("RRC");   break;//register A is rotated right where the carry bit and high order bit are set to the previous low order bit ONLY CARRY FLAG IS SET

        case 0x10: break;
        case 0x11: printf("LXI/tD,#$%20x%20x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair DE
        case 0x12: printf("STAX/tD");   break;//store value in register A at address in register pair DE
        case 0x13: printf("INX/tD");    break;//increment register pair DE NO FLAG SET
        case 0x14: printf("INR/tD");    break;//increment register D by 1 CARRY FLAG NOT SET
        case 0x15: printf("DCR/tD");    break;//decrement register D by 1 CARRY FLAG NOT SET
        case 0x16: printf("MVI/tD,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register D
        case 0x17: printf("RAL");   break;//register A is rotated left through carry where the low order bit is set to previous carry and carry is set to previous high order bit ONLY CARRY FLAG IS SET
        case 0x18: break;
        case 0x19: printf("DAD/tD");    break;//add register pair DE to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x1a: printf("LDAX/tD");   break;//load value at address in register pair DE to register A
        case 0x1b: printf("DCX/tD");    break;//decrement register pair DE NO FLAG SET
        case 0x1c: printf("INR/tE");    break;//increment register E by 1 CARRY FLAG NOT SET
        case 0x1d: printf("DCR/tE");    break;//decrement register E by 1 CARRY FLAG NOT SET
        case 0x1e: printf("MVI/tE,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register E
        case 0x1f: printf("RAR");   break;//register A is rotated left through carry where the high order bit is set to previous carry and carry is set to previous low order bit ONLY CARRY FLAG IS SET

        case 0x20: break;
        case 0x21: printf("LXI/tH,#$%20x%20x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair HL
        case 0x22: printf("SHLD/t$%20x%20x", code[2], code[1]); opbytes = 3;    break;//store value of register L at address and value of register H at address + 1
        case 0x23: printf("INX/tH");    break;//increment register pair HL NO FLAG SET
        case 0x24: printf("INR/tH");    break;//increment register H by 1 CARRY FLAG NOT SET
        case 0x25: printf("DCR/tH");    break;//decrement register H by 1 CARRY FLAG NOT SET
        case 0x26: printf("MVI/tH,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register H
        case 0x27: printf("DAA");   break;//adjust accumulator to form 2 four bit binary coded decimal digits
        case 0x28: break;
        case 0x29: printf("DAD/tH");    break;//add register pair HL to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x2a: printf("LHLD/t$%20x%20x", code[2], code[1]);    opbytes = 3;    break;//load value at address to register L and value at address + 1 to register H
        case 0x2b: printf("DCX/tH");    break;//decrement register pair HL NO FLAG SET
        case 0x2c: printf("INR/tL");    break;//increment register L by 1 CARRY FLAG NOT SET
        case 0x2d: printf("DCR/tL");    break;//decrement register L by 1 CARRY FLAG NOT SET
        case 0x2e: printf("MVI/tL,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register L
        case 0x2f: printf("CMA");   break;//register A is set to complement (0<->1) NO FLAGS ARE SET

        case 0x30: break;
        case 0x31: printf("LXI/tSP,#$%20x%20x", code[2], code[1]);    opbytes = 3;    break;//load data into register pair SP (Stack pointer)
        case 0x32: printf("STA/t$%20x20x", code[2], code[1]);   opbytes = 3;    break;//store value in register A at address
        case 0x33: printf("INX/tSP");   break;//increment register pair SP (Stack pointer) NO FLAG SET
        case 0x34: printf("INR/tM");    break;//increment memory location (H)(L) by 1 CARRY FLAG NOT SET
        case 0x35: printf("DCR/tM");    break;//decrement memory location (H)(L) by 1 CARRY FLAG NOT SET
        case 0x36: printf("MVI/tM,#$%02x", code[1]);  opbytes = 2;    break;//move data value to memory location (H)(L)
        case 0x37: printf("STC");   break;//set carry flag to 1 NO OTHER FLAGS ARE SET
        case 0x38: break;
        case 0x39: printf("DAD/tSP");   break;//add register pair SP (Stack poiinter) to register pair HL ONLY CARRY FLAG IS SET OUT OF DOUBLE PRECISION ADD OTHERWISE RESET
        case 0x3a: printf("LDA/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//load value at address to register A
        case 0x3b: printf("DCX/tSP");   break;//decrement register pair BSP(Stack pointer) NO FLAG SET
        case 0x3c: printf("INR/tA");    break;//increment register A by 1 CARRY FLAG NOT SET
        case 0x3d: printf("DCR/tA");    break;//decrement register A by 1 CARRY FLAG NOT SET
        case 0x3e: printf("MVI/tA,#$%02x", code[1]);  opbytes = 2;    break;//move data value to register A
        case 0x3f: printf("CMC");   break;//carry flag is set to complement (0<->1) NO OTHER FLAGS ARE SET

        case 0x40: printf("MOV/tB,B");    break; //move register B to register B
        case 0x41: printf("MOV/tB,C");    break; //move register C to register B
        case 0x42: printf("MOV/tB,D");    break; //move register D to register B
        case 0x43: printf("MOV/tB,E");    break; //move register E to register B
        case 0x44: printf("MOV/tB,H");    break; //move register H to register B
        case 0x45: printf("MOV/tB,L");    break; //move register L to register B
        case 0x46: printf("MOV/tB,M");    break; //move memory location (H)(L) to register B
        case 0x47: printf("MOV/tB,A");    break; //move register A to register B
        case 0x48: printf("MOV/tC,B");    break; //move register B to register C
        case 0x49: printf("MOV/tC,C");    break; //move register C to register C
        case 0x4a: printf("MOV/tC,D");    break; //move register D to register C
        case 0x4b: printf("MOV/tC,E");    break; //move register E to register C
        case 0x4c: printf("MOV/tC,H");    break; //move register H to register C
        case 0x4d: printf("MOV/tC,L");    break; //move register L to register C
        case 0x4e: printf("MOV/tC,M");    break; //move memory location (H)(L) to register C
        case 0x4f: printf("MOV/tC,A");    break; //move register A to register C

        case 0x50: printf("MOV/tD,B");    break; //move register B to register D
        case 0x51: printf("MOV/tD,C");    break; //move register C to register D
        case 0x52: printf("MOV/tD,D");    break; //move register D to register D
        case 0x53: printf("MOV/tD,E");    break; //move register E to register D
        case 0x54: printf("MOV/tD,H");    break; //move register H to register D
        case 0x55: printf("MOV/tD,L");    break; //move register L to register D
        case 0x56: printf("MOV/tD,M");    break; //move memory location (H)(L) to register D
        case 0x57: printf("MOV/tD,A");    break; //move register A to register D
        case 0x58: printf("MOV/tE,B");    break; //move register B to register E
        case 0x59: printf("MOV/tE,C");    break; //move register C to register E
        case 0x5a: printf("MOV/tE,D");    break; //move register D to register E
        case 0x5b: printf("MOV/tE,E");    break; //move register E to register E
        case 0x5c: printf("MOV/tE,H");    break; //move register H to register E
        case 0x5d: printf("MOV/tE,L");    break; //move register L to register E
        case 0x5e: printf("MOV/tE,M");    break; //move memory location (H)(L) to register E
        case 0x5f: printf("MOV/tE,A");    break; //move register A to register E

        case 0x60: printf("MOV/tH,B");    break; //move register B to register H
        case 0x61: printf("MOV/tH,C");    break; //move register C to register H
        case 0x62: printf("MOV/tH,D");    break; //move register D to register H
        case 0x63: printf("MOV/tH,E");    break; //move register E to register H
        case 0x64: printf("MOV/tH,H");    break; //move register H to register H
        case 0x65: printf("MOV/tH,L");    break; //move register L to register H
        case 0x66: printf("MOV/tH,M");    break; //move memory location (H)(L) to register H
        case 0x67: printf("MOV/tH,A");    break; //move register A to register H
        case 0x68: printf("MOV/tL,B");    break; //move register B to register L
        case 0x69: printf("MOV/tL,C");    break; //move register C to register L
        case 0x6a: printf("MOV/tL,D");    break; //move register D to register L
        case 0x6b: printf("MOV/tL,E");    break; //move register E to register L
        case 0x6c: printf("MOV/tL,H");    break; //move register H to register L
        case 0x6d: printf("MOV/tL,L");    break; //move register L to register L
        case 0x6e: printf("MOV/tL,M");    break; //move memory location (H)(L) to register L
        case 0x6f: printf("MOV/tL,A");    break; //move register A to register L

        case 0x70: printf("MOV/tM,B");    break; //move register B to memory location at (H)(L)
        case 0x71: printf("MOV/tM,C");    break; //move register C to memory location at (H)(L)
        case 0x72: printf("MOV/tM,D");    break; //move register D to memory location at (H)(L)
        case 0x73: printf("MOV/tM,E");    break; //move register E to memory location at (H)(L)
        case 0x74: printf("MOV/tM,H");    break; //move register H to memory location at (H)(L)
        case 0x75: printf("MOV/tM,L");    break; //move register L to memory location at (H)(L)
        case 0x76: printf("HLT");         break; //processors stops and program is halted
        case 0x77: printf("MOV/tM,A");    break; //move register A to memory location at (H)(L)
        case 0x78: printf("MOV/tA,B");    break; //move register B to register A
        case 0x79: printf("MOV/tA,C");    break; //move register C to register A
        case 0x7a: printf("MOV/tA,D");    break; //move register D to register A
        case 0x7b: printf("MOV/tA,E");    break; //move register E to register A
        case 0x7c: printf("MOV/tA,H");    break; //move register H to register A
        case 0x7d: printf("MOV/tA,L");    break; //move register L to register A
        case 0x7e: printf("MOV/tA,M");    break; //move memory location (H)(L) to register A
        case 0x7f: printf("MOV/tA,A");    break; //move register A to register A

        case 0x80: printf("ADD/tB");    break;//add register B to register A
        case 0x81: printf("ADD/tC");    break;//add register C to register A
        case 0x82: printf("ADD/tD");    break;//add register D to register A
        case 0x83: printf("ADD/tE");    break;//add register E to register A
        case 0x84: printf("ADD/tH");    break;//add register H to register A
        case 0x85: printf("ADD/tL");    break;//add register L to register A
        case 0x86: printf("ADD/tM");    break;//add memory location at (H)(L) to register A
        case 0x87: printf("ADD/tA");    break;//add register A to register A
        case 0x88: printf("ADC/tB");    break;//add register B and carry bit to register A
        case 0x89: printf("ADC/tC");    break;//add register C and carry bit to register A
        case 0x8a: printf("ADC/tD");    break;//add register D and carry bit to register A
        case 0x8b: printf("ADC/tE");    break;//add register E and carry bit to register A
        case 0x8c: printf("ADC/tH");    break;//add register H and carry bit to register A
        case 0x8d: printf("ADC/tL");    break;//add register L and carry bit to register A
        case 0x8e: printf("ADC/tM");    break;//add memory location (H)(L) and carry bit to register A
        case 0x8f: printf("ADC/tA");    break;//add register A and carry bit to register A

        case 0x90: printf("SUB/tB");    break;//subtract register B from register A
        case 0x91: printf("SUB/tC");    break;//subtract register C from register A
        case 0x92: printf("SUB/tD");    break;//subtract register D from register A
        case 0x93: printf("SUB/tE");    break;//subtract register E from register A
        case 0x94: printf("SUB/tH");    break;//subtract register H from register A
        case 0x95: printf("SUB/tL");    break;//subtract register L from register A
        case 0x96: printf("SUB/tM");    break;//subtract memory location (H)(L) from register A
        case 0x97: printf("SUB/tA");    break;//subtract register A from register A
        case 0x98: printf("SBB/tB");    break;//subtract register B and carry bit from register A
        case 0x99: printf("SBB/tC");    break;//subtract register C and carry bit from register A
        case 0x9a: printf("SBB/tD");    break;//subtract register D and carry bit from register A
        case 0x9b: printf("SBB/tE");    break;//subtract register E and carry bit from register A
        case 0x9c: printf("SBB/tH");    break;//subtract register H and carry bit from register A
        case 0x9d: printf("SBB/tL");    break;//subtract register L and carry bit from register A
        case 0x9e: printf("SBB/tM");    break;//subtract memory location (H)(L) and carry bit from register A
        case 0x9f: printf("SBB/tA");    break;//subtract register A and carry bit from register A

        case 0xa0: printf("ANA/tB");    break;//AND register B with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa1: printf("ANA/tC");    break;//AND register C with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa2: printf("ANA/tD");    break;//AND register D with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa3: printf("ANA/tE");    break;//AND register E with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa4: printf("ANA/tH");    break;//AND register H with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa5: printf("ANA/tL");    break;//AND register L with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa6: printf("ANA/tM");    break;//AND data at memory location (H)(L) with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa7: printf("ANA/tA");    break;//AND register A with register A and store in register A CARRY FLAG IS CLEARED
        case 0xa8: printf("XRA/tB");    break;//exclusive OR register B with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xa9: printf("XRA/tC");    break;//exclusive OR register C with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xaa: printf("XRA/tD");    break;//exclusive OR register D with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xab: printf("XRA/tE");    break;//exclusive OR register E with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xac: printf("XRA/tH");    break;//exclusive OR register H with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xad: printf("XRA/tL");    break;//exclusive OR register L with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xae: printf("XRA/tM");    break;//exclusive OR data at memory location (H)(L) with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xaf: printf("XRA/tA");    break;//exclusive OR register A with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED

        case 0xb0: printf("ORA/tB");    break;//inclusive OR register B with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb1: printf("ORA/tC");    break;//inclusive OR register C with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb2: printf("ORA/tD");    break;//inclusive OR register D with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb3: printf("ORA/tE");    break;//inclusive OR register E with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb4: printf("ORA/tH");    break;//inclusive OR register H with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb5: printf("ORA/tL");    break;//inclusive OR register L with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb6: printf("ORA/tM");    break;//inclusive OR data at memory location (H)(L) with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb7: printf("ORA/tA");    break;//inclusive OR register A with register A and store in register A AUXILARY CARRY AND CARRY FLAG IS CLEARED
        case 0xb8: printf("CMP/tB");    break;//subtract register B from register A Z FLAG SET TO 1 IF A = B AND CARRY FLAG IS SET TO 1 IF A < B
        case 0xb9: printf("CMP/tC");    break;//subtract register C from register A Z FLAG SET TO 1 IF A = C AND CARRY FLAG IS SET TO 1 IF A < C
        case 0xba: printf("CMP/tD");    break;//subtract register D from register A Z FLAG SET TO 1 IF A = D AND CARRY FLAG IS SET TO 1 IF A < D
        case 0xbb: printf("CMP/tE");    break;//subtract register E from register A Z FLAG SET TO 1 IF A = E AND CARRY FLAG IS SET TO 1 IF A < E
        case 0xbc: printf("CMP/tH");    break;//subtract register H from register A Z FLAG SET TO 1 IF A = H AND CARRY FLAG IS SET TO 1 IF A < H
        case 0xbd: printf("CMP/tL");    break;//subtract register L from register A Z FLAG SET TO 1 IF A = L AND CARRY FLAG IS SET TO 1 IF A < L
        case 0xbe: printf("CMP/tM");    break;//subtract data at memory location (H)(L) from register A Z FLAG SET TO 1 IF A = M AND CARRY FLAG IS SET TO 1 IF A < M
        case 0xbf: printf("CMP/tA");    break;//subtract register A from register A Z FLAG SET TO 1 IF A = A AND CARRY FLAG IS SET TO 1 IF A < A

        case 0xc0: printf("RNZ/t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//bruh if zero flag is 0
        case 0xc1: break;
        case 0xc2: printf("JNZ/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//jump to address if zero flag is 0
        case 0xc3: printf("JMP/t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//jump unconditional
        case 0xc4: printf("CNZ/t$%02x%02x", code[2], code[1]);    opbytes = 3;  break;//bruh if zero flag is 0
        case 0xc5: break;
        case 0xc6: printf("ADI/t#$%20x", code[1]);  opbytes = 2;    break;//add data value to register A
        case 0xc7: printf("RST/t0");    break;//call instruction at address $00
        case 0xc8: printf("RZ/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if zero flag is 1
        case 0xc9: printf("RET");   break;//bruh
        case 0xca: printf("JZ/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//jump to address if zero flag is 1
        case 0xcb: break;
        case 0xcc: printf("CZ/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if zero flag is 1
        case 0xcd: printf("CALL/t$%20x%20x", code[2], code[1]); opbytes = 3;    break;//bruh
        case 0xce: printf("ACI/t#$%20x", code[1]);  opbytes = 2;    break;//add data value and carry bit to register A
        case 0xcf: printf("RST/t1");    break;//call instruction at address $08

        case 0xd0: printf("RNC/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if carry flag is 0
        case 0xd1: break;
        case 0xd2: printf("JNC/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//jump to address if carry flag is 0
        case 0xd3: break;
        case 0xd4: printf("CNC/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if carry flag is 0
        case 0xd5: break;
        case 0xd6: printf("SUI/t#$%20x", code[1]);  opbytes = 2;    break;//subtract data value from register A
        case 0xd7: printf("RST/t2");    break;//call instruction at address $10
        case 0xd8: printf("RC/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if carry flag is 1
        case 0xd9: break;
        case 0xda: printf("JC/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//jump to address if carry flag is 1
        case 0xdb: break;
        case 0xdc: printf("CC/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if carry flag is 1
        case 0xdd: break;
        case 0xde: printf("SBI/t#$%20x", code[1]);  opbytes = 2;    break;//subtract data value and carry bit from register A
        case 0xdf: printf("RST/t3");    break;//call instruction at address $18

        case 0xe0: printf("RPO/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 0
        case 0xe1: break;
        case 0xe2: printf("JPO/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//jump to address if parity flag is 0
        case 0xe3: break;
        case 0xe4: printf("CPO/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 0
        case 0xe5: break;
        case 0xe6: printf("ANI/t#$%20x", code[1]);  opbytes = 2;    break;//AND data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xe7: printf("RST/t4");    break;//call instruction at address $20
        case 0xe8: printf("RPE/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 1
        case 0xe9: printf("PCHL");  break;//set program counter to register pair HL (jump to HL)
        case 0xea: printf("JPE/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//jump to address if parity flag is 1
        case 0xeb: printf("XCHG");  break;//contents in register pair HL are swapped with register pair DE
        case 0xec: printf("CPE/t$%20x%20x", code[2], code[1]);  opbytes = 3;    break;//bruh if parity flag is 1
        case 0xed: break;
        case 0xee: printf("XRI/t#$%20x", code[1]);  opbytes = 2;    break;//exclusive OR data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xef: printf("RST/t5");    break;//call instruction at address $28
        
        case 0xf0: printf("RP/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 0
        case 0xf1: break;
        case 0xf2: printf("JP/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//jump to address if sign flag is 0
        case 0xf3: break;
        case 0xf4: printf("CP/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 0
        case 0xf5: break;
        case 0xf6: printf("ORI/t#$%20x", code[1]);  opbytes = 2;    break;//inclusive OR data with register A AUXILARY CARRY AND CARRY FLAG ARE CLEARED
        case 0xf7: printf("RST/t6");    break;//call instruction at address $30
        case 0xf8: printf("RM/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 1
        case 0xf9: break;
        case 0xfa: printf("JM/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//jump to address if sign flag is 1
        case 0xfb: break;
        case 0xfc: printf("CM/t$%20x%20x", code[2], code[1]);   opbytes = 3;    break;//bruh if sign flag is 1
        case 0xfd: break;
        case 0xfe: printf("CPI/t#$%20x", code[1]);  opbytes = 2;    break;//subtract data from register A Z FLAG SET TO 1 IF A = data AND CARRY FLAG IS SET TO 1 IF A < data
        case 0xff: printf("RST/t7");    break;//call instruction at address $38
        default:
    }
    cout << '/n';
    return opbytes;
}