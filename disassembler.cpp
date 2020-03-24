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
        default:
    }
    cout << '/n';
    return opbytes;
}