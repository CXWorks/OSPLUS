//
// Created by st0001 on 2017/5/6.
//
#include "call.h"
#include "INT.h"
#define MAXMEM ((512+128)*1024*1024)
#define M4B (4*1024*1024)
#define MEM_P_NUM (7936)
#define PAGE (16*1024)
#define TCB_SIZE (520)

void init(){
    for (int i = 0; i < M4B; ++i) {
        mem_write(0,i);
    }
}



int read(data_unit *data, v_address address, m_pid_t pid){
    TCB tcb;
    int addr=6;
    addr+=(pid-1)*TCB_SIZE;
    getTCB(&tcb,addr);
    int index=address/PAGE,in=-1;
    for (int i = 0; i < tcb.duan; ++i) {
        int len=tcb.duan_p[i][1]-tcb.duan_p[i][0];
        if(index<=len){
            in=i;
        }
        else{
            index-=len;
        }
    }
    if(in!=-1){
        int real_address=tcb.duan_p[in][0]*PAGE+index*PAGE+address%PAGE;
        if(tcb.duan_p[in][0]+index>MEM_P_NUM){

        }
        else
            data[0]=mem_read(real_address);
        return 1;
    }
    else{ return 0;}
}

int write(data_unit data, v_address address, m_pid_t pid){
    TCB tcb;
    int addr=6;
    addr+=(pid-1)*TCB_SIZE;
    getTCB(&tcb,addr);
    int index=address/PAGE,in=-1;
    for (int i = 0; i < tcb.duan; ++i) {
        int len=tcb.duan_p[i][1]-tcb.duan_p[i][0];
        if(index<=len){
            in=i;
        }
        else{
            index-=len;
        }
    }
    if(in!=-1){
        int real_address=tcb.duan_p[in][0]*PAGE+index*PAGE+address%PAGE;
        if(tcb.duan_p[in][0]+index>MEM_P_NUM){

        }
        else
            mem_write(data,real_address);
        return 1;
    }
    else{ return 0;}
}

int allocate(v_address *address, m_size_t size, m_pid_t pid){
    int de=getINT32(0);
    if(size+de>MEM_P_NUM) return -1;
    de+=size;
    saveINT32(0,de);
    int addr=6;
    addr+=(pid-1)*TCB_SIZE;

    TCB tcb;
    if(exist(addr))
        getTCB(&tcb,addr);
    else{
        tcb.pid=pid;
        tcb.declared=0;
        tcb.used=0;
        tcb.duan=0;
    }

    int page=(size/PAGE)+(size%PAGE==0?0:1);
    int retu=tcb.declared;
    int success=0;
    int start=0,end=0,t=0;
    int array[1000][2];
    for (int i = 0; i < 999; ++i) {
        int adre=6+(i)*TCB_SIZE;
        if(exist(adre)){
            TCB tcb1;
            getTCB(&tcb1,adre);
            for (int j = 0; j < tcb1.duan; ++j) {
                array[t][0]=tcb1.duan_p[j][0];
                array[t++][1]=tcb1.duan_p[j][1];
            }
        }
    }
    for (int i = 0; i < t; ++i) {
        int ind=i;
        int mmin=array[i][0];
        for (int j = i+1; j < t; ++j) {
            if(array[j][0]<mmin){
                mmin=array[j][0];
                ind=j;
            }
        }
        int temp=array[i][0];
        array[i][0]=array[ind][0];
        array[ind][0]=temp;
        temp=array[i][1];
        array[i][1]=array[ind][1];
        array[ind][1]=temp;
    }

    for (int i = 0; i < t-1; ++i) {
        if(array[i+1][0]-array[i][1]>=page){
            success=1;
            start=array[i][1];
            end=start+page;
        }
    }
    if(!success){
        if(array[t-1][1]+page<NUM_OF_PAGE){
            success=1;
            start=array[t-1][1];
            end=start+page;
        }
    }
    if(success){
        tcb.duan++;
        tcb.declared+=page*PAGE;
        tcb.duan_p[tcb.duan][0]=start;
        tcb.duan_p[tcb.duan][1]=end;
        saveTCB(&tcb,addr);

        address[0]=retu;
        return 0;
    }
    else{
        return -1;
    }


}

int free(v_address address, m_pid_t pid){
    int addr=6;
    addr+=(pid-1)*TCB_SIZE;

    TCB tcb;
    if(exist(addr))
        getTCB(&tcb,addr);
    else
        return 0;
    int index=address/PAGE,in=-1;
    for (int i = 0; i < tcb.duan; ++i) {
        int len=tcb.duan_p[i][1]-tcb.duan_p[i][0];
        if(index<=len){
            in=i;
        }
        else{
            index-=len;
        }
    }
    if(in!=-1){
        for (int i = in; i < tcb.duan-1; ++i) {
            tcb.duan_p[i][0]=tcb.duan_p[i+1][0];
            tcb.duan_p[i][1]=tcb.duan_p[i+1][1];
        }
        tcb.duan--;
        saveTCB(&tcb,addr);
        return 1;
    }
    else{ return 0;}
}




