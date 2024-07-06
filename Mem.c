#include "Mem.h"

int getPid(char* name){
    char cmd[50];

    sprintf(cmd, "pidof -s %s", name);

    FILE* cmdPipe = popen(cmd, "r");
    char buffer[10];
    fgets(buffer, sizeof(buffer), cmdPipe);
    fclose(cmdPipe);

    if (strcmp("", buffer) == 0){
        return -1;
    }

    return atoi(buffer);
}

Process* OpenProcess(char* name){
    int pid = getPid(name);
    if (pid == -1){ return NULL; }

    Process* proc = (Process*)malloc(sizeof(Process));
    proc->id=pid;
    char path[20];
    sprintf(path, "/proc/%d/mem", pid);
    proc->fStream=fopen(path, "rb+");

    return proc;
}

void CloseProcess(Process* proc){
    fclose(proc->fStream);
    free(proc);
}

void readBytes(Process* proc, unsigned long long address, unsigned char* buffer, int size){
    fseek(proc->fStream, address, SEEK_SET);
    fread(buffer, size, 1, proc->fStream);
}

int readInt(Process* proc, unsigned long long address){
    unsigned char buffer[sizeof(int)];
    readBytes(proc, address, buffer, sizeof(buffer));
    return *(int*)buffer;
}

void writeBytes(Process* proc, unsigned long long address, unsigned char* buffer, int size){
    fseek(proc->fStream, address, SEEK_SET);
    fwrite(buffer, size, 1, proc->fStream);
}

void writeInt(Process* proc, unsigned long long address, int data){
    unsigned char buffer[sizeof(data)];
    for (int i=0; i<sizeof(int); i++){
        buffer[i]=(255<<(8*i) & data)>>8*i;
    }
    writeBytes(proc, address, buffer, sizeof(buffer));
}
