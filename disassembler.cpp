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
        case 0x01: break;
        case 0x02: break;
        case 0x03: break;
        case 0x04: break;
        case 0x05: break;
        case 0x06: break;
        case 0x07: break;
        case 0x08: break;
        case 0x09: break;
        case 0x0a: break;
        case 0x0b: break;
        case 0x0c: break;
        case 0x0d: break;
        case 0x0e: break;
        case 0x0f: break;
        case 0x10: break;
        case 0x11: break;
        case 0x12: break;
        case 0x13: break;
        case 0x14: break;
        case 0x15: break;
        case 0x16: break;
        case 0x17: break;
        case 0x18: break;
        case 0x19: break;
        case 0x1a: break;
        case 0x1b: break;
        case 0x1c: break;
        case 0x1d: break;
        case 0x1e: break;
        case 0x1f: break;
        case 0x20: break;
        case 0x21: break;
        case 0x22: break;
        case 0x23: break;
        case 0x24: break;
        case 0x25: break;
        case 0x26: break;
        case 0x27: break;
        case 0x28: break;
        case 0x29: break;
        case 0x2a: break;
        case 0x2b: break;
        case 0x2c: break;
        case 0x2d: break;
        case 0x2e: break;
        case 0x2f: break;
        case 0x30: break;
        case 0x31: break;
        case 0x32: break;
        case 0x33: break;
        case 0x34: break;
        case 0x35: break;
        case 0x36: break;
        case 0x37: break;
        case 0x38: break;
        case 0x39: break;
        case 0x3a: break;
        case 0x3b: break;
        case 0x3c: break;
        case 0x3d: break;
        case 0x3e: break;
        case 0x3f: break;
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
        case 0x76: break;
        case 0x77: printf("MOV/tM,A");    break; //move register A to memory location at (H)(L)
        case 0x78: printf("MOV/tA,B");    break; //move register B to register A
        case 0x79: printf("MOV/tA,C");    break; //move register C to register A
        case 0x7a: printf("MOV/tA,D");    break; //move register D to register A
        case 0x7b: printf("MOV/tA,E");    break; //move register E to register A
        case 0x7c: printf("MOV/tA,H");    break; //move register H to register A
        case 0x7d: printf("MOV/tA,L");    break; //move register L to register A
        case 0x7e: printf("MOV/tA,M");    break; //move memory location (H)(L) to register A
        case 0x7f: printf("MOV/tA,A");    break; //move register A to register A
        case 0x80: break;
        case 0x81: break;
        case 0x82: break;
        case 0x83: break;
        case 0x84: break;
        case 0x85: break;
        case 0x86: break;
        case 0x87: break;
        case 0x88: break;
        case 0x89: break;
        case 0x8a: break;
        case 0x8b: break;
        case 0x8c: break;
        case 0x8d: break;
        case 0x8e: break;
        case 0x8f: break;
        case 0x90: break;
        case 0x91: break;
        case 0x92: break;
        case 0x93: break;
        case 0x94: break;
        case 0x95: break;
        case 0x96: break;
        case 0x97: break;
        case 0x98: break;
        case 0x99: break;
        case 0x9a: break;
        case 0x9b: break;
        case 0x9c: break;
        case 0x9d: break;
        case 0x9e: break;
        case 0x9f: break;
        case 0xa0: break;
        case 0xa1: break;
        case 0xa2: break;
        case 0xa3: break;
        case 0xa4: break;
        case 0xa5: break;
        case 0xa6: break;
        case 0xa7: break;
        case 0xa8: break;
        case 0xa9: break;
        case 0xaa: break;
        case 0xab: break;
        case 0xac: break;
        case 0xad: break;
        case 0xae: break;
        case 0xaf: break;
        case 0xb0: break;
        case 0xb1: break;
        case 0xb2: break;
        case 0xb3: break;
        case 0xb4: break;
        case 0xb5: break;
        case 0xb6: break;
        case 0xb7: break;
        case 0xb8: break;
        case 0xb9: break;
        case 0xba: break;
        case 0xbb: break;
        case 0xbc: break;
        case 0xbd: break;
        case 0xbe: break;
        case 0xbf: break;
        case 0xc0: break;
        case 0xc1: break;
        case 0xc2: break;
        case 0xc3: printf("JMP/t$%02x%02x", code[2], code[1]);    opbytes = 3;   break; //jump unconditional
        case 0xc4: break;
        case 0xc5: break;
        case 0xc6: break;
        case 0xc7: break;
        case 0xc8: break;
        case 0xc9: break;
        case 0xca: break;
        case 0xcb: break;
        case 0xcc: break;
        case 0xcd: break;
        case 0xce: break;
        case 0xcf: break;
        case 0xd0: break;
        case 0xd1: break;
        case 0xd2: break;
        case 0xd3: break;
        case 0xd4: break;
        case 0xd5: break;
        case 0xd6: break;
        case 0xd7: break;
        case 0xd8: break;
        case 0xd9: break;
        case 0xda: break;
        case 0xdb: break;
        case 0xdc: break;
        case 0xdd: break;
        case 0xde: break;
        case 0xdf: break;
        case 0xe0: break;
        case 0xe1: break;
        case 0xe2: break;
        case 0xe3: break;
        case 0xe4: break;
        case 0xe5: break;
        case 0xe6: break;
        case 0xe7: break;
        case 0xe8: break;
        case 0xe9: break;
        case 0xea: break;
        case 0xeb: break;
        case 0xec: break;
        case 0xed: break;
        case 0xee: break;
        case 0xef: break;
        case 0xf0: break;
        case 0xf1: break;
        case 0xf2: break;
        case 0xf3: break;
        case 0xf4: break;
        case 0xf5: break;
        case 0xf6: break;
        case 0xf7: break;
        case 0xf8: break;
        case 0xf9: break;
        case 0xfa: break;
        case 0xfb: break;
        case 0xfc: break;
        case 0xfd: break;
        case 0xfe: break;
        case 0xff: break;
        default:
    }
    cout << '/n';
    return opbytes;
}