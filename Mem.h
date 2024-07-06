#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Process Process;
struct Process{
    FILE* fStream;
    int id;
};

int getPid(char* name);
Process* OpenProcess(char* name);
void CloseProcess(Process* proc);
void readBytes(Process* proc, unsigned long long address, unsigned char* buffer, int size);
int readInt(Process* proc, unsigned long long address);
void writeBytes(Process* proc, unsigned long long address, unsigned char* buffer, int size);
void writeInt(Process* proc, unsigned long long address, int data);
