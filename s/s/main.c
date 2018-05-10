//
//  main.c
//  s
//
//  Created by 吴若翎 on 2018/5/10.
//  Copyright © 2018年 吴若翎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct num{
    int data[20];
    int top;//定义运算数
};
typedef struct num num_node;
struct sym{
    char symbol[20];//定义存储运算符的栈
    int top;
};
typedef struct sym sym_node;
void initoperator(sym_node*opstack);//
void initnumber(num_node*numstack);//
void push_symbol(sym_node*opstack,char ch);//
void push_number(num_node*numstack,int x);//
char pop_symbol(sym_node*opstack);//栈顶元素出栈
int pop_number(num_node*numstack);//栈顶元素出栈
int get_number(num_node*numstack);//查看栈顶元素
char ger_symbol(sym_node*opstack);//查看栈顶元素
bool is_symbol_or_num(char ch);//
char priority(char symbol,char ch);//判断运算符优先级
int calculate(int num1,char ch,int num2); ////用于计算
int MainCalc(void);
int main(int argc, const char * argv[]) {
    int result;
    result=MainCalc();
    printf("%d",result);
    return 0;
}
void initoperator(sym_node*opstack){
    opstack->top=-1;
}
void initnumber(num_node*numstack){
    numstack->top=-1;
}
void push_symbol(sym_node*opstack,char ch){
    opstack->top++;
    opstack->symbol[opstack->top]=ch;
}
void push_number(num_node*numstack,int x){
    numstack->top++;
    numstack->data[numstack->top]=x;
}
char pop_symbol(sym_node*opstack){
    char ch;
    ch=opstack->symbol[opstack->top];
    opstack->top--;
    return ch;
}
int pop_number(num_node*numstack){
    int num;
    num=numstack->data[numstack->top];
    numstack->top--;
    return num;
}
int get_number(num_node*numstack){
    return  numstack->data[numstack->top];
}
char ger_symbol(sym_node*opstack){
    return opstack->symbol[opstack->top];
}
bool is_symbol_or_num(char ch){
    switch (ch) {
            
        case '+': case '-':case '*':case '/':case '%':case '(': case ')':
            return true;
            
            
        default:
            return false;
    }
}
char priority(char symbol,char ch){
    switch (symbol){
        case '+':case '-':{
            if(ch=='+'||ch=='-')
                return '>';
            else if(ch=='*'||ch=='/')
                return '<';
            else if(ch=='(')
                return '<';
            else if(ch==')')
                return '>';
            else return '>';
            
        }
        case '*':case '/':case '%':{
            if(ch=='+'||ch=='-')
                return '>';
            else if(ch=='*'||ch=='/'||ch=='%')
                return '>';
            else if(ch=='(')
                return '<';
            else if(ch==')')
                return '>';
            else return '>';
        }
            break;
        case '(':{
            if(ch==')')
                return '=';
            else return '>';}
            break;
        case ')':{
            return '=';}
            break;
        case '\n':{
            if(ch=='\n')
                return '=';
            else
                return '<';}
            break;
        default: break;}
    return  'o';
    
}
int calculate(int num1,char ch,int num2){
    switch (ch) {
        case '+':{
            return num1+num2;
            break;}
        case '-':{
            return num1-num2;
            break;
        }
        case '*':{
            return num1*num2;
            break;
        }
        case '/':{
            return num1/num2;
            break;
        }
        case '%':{
            return num1%num2;
            break;
        }
    }
    return 'a';
}
int MainCalc(void){
    num_node*num_stack;
    sym_node*opt_stack;
    int num1,num2,num,result;
    char sym,ch;
    initnumber(num_stack);
    initoperator(opt_stack);
    push_symbol(opt_stack, '\n');
    ch=getchar();
    while (ch!='\n'||ger_symbol(opt_stack)!='\n') {//为换行符表示符号栈已经到栈底，以及当前输入结束，否则继续读取改式
        if (!is_symbol_or_num(ch)) {//如果是数字则将字符转换成数字
            num=atoi(&ch);
            ch=getchar();//读取下一个字符
            
            while (!is_symbol_or_num(ch)) {//如果再次读取的字符仍然是数字则表示该数字不是个位数
                num=num*10+atoi(&ch);
                ch=getchar();//再次读取
            }
            push_number(num_stack, num);//该数字读取完毕后进入数字栈
        }
        else{//如果该字符为运算符
            switch(priority(ger_symbol(opt_stack), ch)){//与栈顶的运算符比较优先级
                case '<':push_symbol(opt_stack, ch);//如果优先级高于栈顶运算符则进符号栈
                    ch=getchar();//继续读取，下一个可能为字符或数字
                    break;
                case '=':sym=pop_symbol(opt_stack);//如果优先级相同，如左右括号，则栈顶出栈
                    ch=getchar();
                    break;
                case '>':sym=pop_symbol(opt_stack);//如果低于栈顶优先级，则栈顶出栈，开始运算
                    num2=pop_number(num_stack);
                    num1=pop_number(num_stack);
                    result=calculate(num1, sym, num2);
                    push_number(num_stack, result);//将运算结果入数栈
                    break;
            }
        }
    }
    result=get_number(num_stack);
    return result;}

