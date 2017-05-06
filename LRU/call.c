//
// Created by st0001 on 2017/5/6.
//
#include "call.h"
#include "INT.h"
#define MAXMEM ((512+128)*1024*1024)
#define MEM_P_NUM (3840)
void init(){
    INT32 de;
    de.val=0;
    de.save(0);
    INT16 pe;
    pe.val=0;
    pe.save(4);

}



int read(data_unit *data, v_address address, m_pid_t pid);

int write(data_unit data, v_address address, m_pid_t pid);

int allocate(v_address *address, m_size_t size, m_pid_t pid){

}

int free(v_address address, m_pid_t pid);




