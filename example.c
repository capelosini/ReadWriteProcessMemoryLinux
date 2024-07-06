#include "Mem.h"

int main(){

    Process* proc = OpenProcess("Discord");

    if (proc == NULL){
        printf("Cannot open the target Process\n");
        return -1;
    }

    printf("Opened Discord (%d)\n", proc->id);

    printf("0x5b6604706300 -> %d\n", readInt(proc, 0x5b6604706300));

    writeInt(proc, 0x5b6604706300, 2001);

    CloseProcess(proc);
    return 0;
}
