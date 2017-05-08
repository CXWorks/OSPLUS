//
// Created by st0001 on 2017/5/6.
//

#ifndef LRU_INT_H
#define LRU_INT_H

#include "type.h"
#include "bottom.h"


    int getINT16(p_address address1){
        int val=0;
        for (int i = 0; i < 2; ++i) {
            val<<=8;
            val+=mem_read(address1+i);
        }
        return val;
    }
    p_address saveINT16(p_address address1,int val){
        mem_write((data_unit)val,address1+1);
        mem_write((data_unit)(val>>8),address1);
        return address1+2;
    }



    int getINT32(p_address address1){
        int val=0;
        for (int i = 0; i < 4; ++i) {
            val<<=8;
            val+=mem_read(address1+i);
        }
        return val;
    }
    p_address saveINT32(p_address address1,int val){
        for (int i = 0; i < 4; ++i) {
            int p=3-i;
            mem_write((data_unit)(val>>(8*i)),address1+p);
        }
        return address1+4;
    }


typedef struct tcb{
    int pid;
    int declared;
    int used;
    int duan;
    int duan_p[128][2];

} TCB;

p_address getTCB(TCB* tcb,p_address address){
    tcb->pid=getINT16(address);
    tcb->declared=getINT16(address+2);
    tcb->used=getINT16(address+4);
    tcb->duan=getINT16(address+6);
    address+=6;
    for (int i = 0; i < tcb->duan; ++i) {
        tcb->duan_p[i][0]=getINT16(address);
        tcb->duan_p[i][1]=getINT16(address+2);
        address+=4;
    }
    return address;
}

void saveTCB(TCB* tcb,p_address address){
    saveINT16(address,tcb->pid);
    saveINT16(address+2,tcb->declared);
    saveINT16(address+4,tcb->used);
    saveINT16(address+6,tcb->duan);
    address+=6;
    for (int i = 0; i < tcb->duan; ++i) {
        saveINT16(address,tcb->duan_p[i][0]);
        saveINT16(address+2,tcb->duan_p[i][1]);
        address+=4;
    }
}

int exist(p_address address){
    int pid=getINT16(address);
    return pid>0&&pid<1000;
}

void readMAP(char * arr){
    int addr=MAP_START;
    for (int i = 0; i < MAP_SIZE; ++i) {
        arr[i]=mem_read(addr);
        addr++;
    }
}
#endif //LRU_INT_H
