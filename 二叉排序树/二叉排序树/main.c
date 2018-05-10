//
//  main.c
//  二叉排序树
//
//  Created by 吴若翎 on 2018/5/10.
//  Copyright © 2018年 吴若翎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node{
    int key;
    int data;
    struct node*lchild,*rchild;
};
typedef  struct  node bstnode;//创建二叉排序树的节点类型
bool insert(bstnode**bt,int k);
bstnode*createbst(int a[ ],int n);
bstnode*search(bstnode*bt,int k);//查找关键字为k的节点，返回该节点的指针
bool deletebst(bstnode**bt,int k);
void delete(bstnode**p);
void deletel(bstnode*p,bstnode**r);//若要删除的节点的左右子树都非空，则左最大节点节点值替代法
int main(int argc, const char * argv[]) {
    int a[6]={1,2,3,4,5,6};
    bstnode*bt,*bt1;
    bt=createbst(a, 6);
    bt1=search(bt, 2);
    printf("%d",bt1->key);
    deletebst(&bt, 3);
    
    return 0;
}
bool insert(bstnode**bt,int k){
    if((*bt)==NULL){
        (*bt)=malloc(sizeof(bstnode));
        (*bt)->key=k;
        (*bt)->lchild=(*bt)->rchild=NULL;
        return  true;
    }//初始化操作
    else if(k==(*bt)->key)
        return false;
    else if(k>(*bt)->key)
        return insert(&(*bt)->rchild, k);//递归创建插入左和右子树
    else
        return insert(&(*bt)->lchild, k);
}
bstnode*createbst(int a[ ],int n){
    bstnode*bt=NULL;
    int i=0;
    while (i<n) {
        insert(&bt, a[i]);
        i++;
    }
    return bt;
}
bstnode*search(bstnode*bt,int k){
    if(bt==NULL||bt->key==k)
        return bt;
    if(k<bt->key)
        return search(bt->lchild, k);//递归在左右子树中查找该节点
    else{
        return search(bt->rchild, k);
    }
}
bool deletebst(bstnode**bt,int k){
    if((*bt)==NULL)
        return false;
    else if(k<(*bt)->key)
        return  deletebst(&(*bt)->lchild, k);
    else if (k>(*bt)->key)
        return deletebst(&(*bt)->rchild, k);
    else {
        delete(bt);
        printf("sucess");
        return true;
    }
}
void delete(bstnode**p){
    bstnode*q;
    if((*p)->rchild==NULL){
        q=*p;
        *p=(*p)->lchild;
        free(q);
        q=NULL;
    }
    else if((*p)->lchild==NULL){
        q=*p;
        *p=(*p)->rchild;
        free(q);
    }
    else{
        deletel(*p, &(*p)->lchild);
    }
}
void deletel(bstnode*p,bstnode**r){
    bstnode*q;
    if((*r)->rchild!=NULL)
        deletel(p, &((*r)->rchild));//找到左子树中的最右下节点
    else{
        p->key=(*r)->key;
        q=(*r);
        (*r)=(*r)->lchild;
        free(q);
    }
}

