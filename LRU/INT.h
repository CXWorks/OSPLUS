//
// Created by st0001 on 2017/5/6.
//

#ifndef LRU_INT_H
#define LRU_INT_H

#include "type.h"
#include "bottom.h"
typedef struct intt{
    int val;
    intt(p_address address1){
        this->val=0;
        for (int i = 0; i < 2; ++i) {
            this->val<<=8;
            this->val+=mem_read(address1+i);
        }
    }
    p_address save(p_address address1){
        mem_write((data_unit)val,address1+1);
        mem_write((data_unit)(val>>8),address1);
        return address1+2;
    }
} INT16;

typedef struct intt32{
    int val;
    intt32(p_address address1){
        this->val=0;
        for (int i = 0; i < 4; ++i) {
            this->val<<=8;
            this->val+=mem_read(address1+i);
        }
    }
    p_address save(p_address address1){
        for (int i = 0; i < 4; ++i) {
            int p=3-i;
            mem_write((data_unit)(val>>(8*i)),address1+p);
        }
        return address1+4;
    }
} INT32;

typedef struct tcb{
    INT16 pid;
    INT16 declared;
    INT16 used;
    INT16 duan;
    INT16 duan_p[128][2];

} TCB;

int getDeclared();


#endif //LRU_INT_H
