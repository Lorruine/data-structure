//
//  main.c
//  doublelinkedlist
//
//  Created by 吴若翎 on 2018/3/7.
//  Copyright © 2018年 吴若翎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct d{
    int data;
    struct d *prior;
    struct d *next;
};
typedef struct d dnode;
typedef struct d *dlinked;
;
dlinked create(void);
void delete(dlinked p,int e);
void travel(dlinked p);
bool isempty(dlinked p);
int getlength(dlinked phead);
void insert(dlinked phead,int e,int p);
void delete(dlinked phead,int p);
int main(int argc, const char * argv[]) {
    dlinked phead;
    phead=create();
    insert(phead,8,2);
    travel(phead);
    delete(phead,3);
    travel(phead);
   
    return 0;
}

dlinked create(void){
    dlinked phead;
    int length=0,d=0;
    dlinked tail=NULL,new=NULL;
     phead=malloc(sizeof(dnode));
    if(phead==NULL){
        printf("fail");
        exit(0);
    }
    phead->data=0;
    phead->next=NULL;
    phead->prior=NULL;
    tail=phead;
    printf("enter the length:");
    scanf("%d",&length);
    for (int i=1; i<length+1; i++) {
        new=malloc(sizeof(dnode));
        if(new==NULL){
            printf("fail");
            exit(0);
        }
        printf("enter %d node:",i);
        scanf("%d",&d);
        new->data=d;
        new->next=NULL;
        new->prior=tail;
        tail->next=new;
        tail=new;
    }
    printf("\n\n");
    return phead;
    
}
void travel(dlinked phead){
    dlinked pt=phead->next;
    while (pt!=NULL) {
        printf("%d",pt->data);
        pt=pt->next;
    }
    printf("\n\n");
}

bool isempty(dlinked phead){
    if((phead->next)==NULL)
        return true;
    else
        return  false;
}
int getlength(dlinked phead){
    dlinked p;
    int i=0;
    p=phead;
    while ((p->next)!=NULL) {
        p=p->next;
        i++;
    }
    return i;
}
void insert(dlinked phead,int e,int p){
    dlinked new=NULL;int i=0;
    if((p>0)&&(p<getlength(phead))+2){
        new=malloc(sizeof(dnode));
        new->prior=phead;
        while (i<p) {
            
              new->prior=new->prior->next;
                i++;
            }
            }
        new->data=e;
    new->next=new->prior->next;
    new->prior->next=new;
    }
    
void delete(dlinked phead,int p){
    dlinked new=NULL;
    int i=0;
    if((p>0)&&(p<getlength(phead))+2){
        new=malloc(sizeof(dnode));
        new=phead;
        while (i<p) {
            new=new->next;
            i++;
        }
        new->prior->next=new->next;
        free(new);
        new=NULL;
        
    }
}


