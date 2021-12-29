//
// Created by zfl on 2021/12/29.
//

#include "stack.h"
#include "../utils/digit_utils.h"
#include <iostream>
using namespace std;
//进制转换
static void convert(stack<char>& s, int n, int base){
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                           'A', 'B', 'C', 'D', 'E', 'F'};
    while (n > 0){
        int remainder = (int) (n % base);
        s.push(digit[remainder]);
        n /= base;
    }
}

//括号匹配
static bool paren(const char exp[], int lo, int hi){
    stack<char> s;
    for (int i = lo; i <= hi; i++){
        switch (exp[i]) {
            case '(':
            case '[':
            case '{': s.push(exp[i]);break;
            case ')': if (s.empty() || s.pop() != '(') return false; break;
            case ']': if (s.empty() || s.pop() != '[') return false; break;
            case '}': if (s.empty() || s.pop() != '{') return false; break;
            default:break;
        }
    }
    return s.empty();
}

//优先级表
#define N_OPTR 9
typedef enum{ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator;
//加 减 乘 除 乘方 阶乘 左括号 右括号 起始终止符
const char pri[N_OPTR][N_OPTR] = {
        /***************************当前运算符*********************/
                    /*      +       -       *       /       ^       !       (       )       $*/
        /*-- + */          '>',    '>',    '<',    '<',    '<',    '<',    '<',    '>',    '>',
        /* | - */          '>',    '>',    '<',    '<',    '<',    '<',    '<',    '>',    '>',
        /*栈 * */          '>',    '>',    '>',    '>',    '<',    '<',    '<',    '>',    '>',
        /*顶 / */          '>',    '>',    '>',    '>',    '<',    '<',    '<',    '>',    '>',
        /*运 ^ */          '>',    '>',    '>',    '>',    '>',    '<',    '<',    '>',    '>',
        /*算 ! */          '>',    '>',    '>',    '>',    '>',    '>',    ' ',    '>',    '>',
        /*符 ( */          '<',    '<',    '<',    '<',    '<',    '<',    '<',    '=',    ' ',
        /* | ) */          ' ',    ' ',    ' ',    ' ',    ' ',    ' ',    ' ',    ' ',    ' ',
        /*-- $ */          '<',    '<',    '<',    '<',    '<',    '<',    '<',    ' ',    '=',
};
//操作符转化为对应的优先级表中的下标
static Operator optr2rank(char op){
    switch (op) {
        case '+':  return ADD;
        case '-':  return SUB;
        case '*':  return MUL;
        case '/':  return DIV;
        case '^':  return POW;
        case '!':  return FAC;
        case '(':  return L_P;
        case ')':  return R_P;
        case '$':  return EOE;
        default: exit(-1);
    }
}
//两个运算符比较
static char orderBetween(char op1, char op2){
    return pri[optr2rank(op1)][optr2rank(op2)];
}
//计算求值
static float calcu(float opnd1, char op, float opnd2 = NULL){
    switch (op) {
        case '+': return opnd1 + opnd2;
        case '-': return opnd1 - opnd2;
        case '*': return opnd1 * opnd2;
        case '/': return opnd1 / opnd2;
        case '^': return 0.f;       //TODO:乘方
        case '!': return 0.f;       //TODO:阶乘
        default:exit(-1);
    }
}
//表达式求值和逆波兰表达式转换
static float evalute(char* s, char*& RPN){
    stack<float> opnd;  //操作数栈
    stack<char> optr;   //操作符栈
    optr.push('$');  //哨兵节点入栈
    while (!optr.empty()){
        if (isdigit(* s)){//读取操作数入栈,并将其接入RPN末尾
            readNum(s, opnd);
            //TODO:append(RPN, opnd.top());
        }else{
            switch (orderBetween(optr.top(), *s)) {
                case '<'://栈顶运算符优先级更低时,将当前操作符入栈，延迟计算
                    optr.push(*s); s++;
                    break;
                case '='://优先级相等时,栈顶为左括号或者尾部哨兵$
                    optr.pop(); s++;
                    break;
                case '>': {//栈顶运算符优先级更高时,进行相应的计算
                    char op = optr.pop();
                    //TODO:append(RPN, op);
                    if ('!' == op) {
                        float pOpnd = opnd.pop();
                        opnd.push(calcu(pOpnd, op));
                    } else {
                        float pOpnd2 = opnd.pop();
                        float pOpnd1 = opnd.pop();
                        opnd.push(calcu(pOpnd1, op, pOpnd2));
                    }
                    break;
                }
                default:exit(-1);//语法错误,直接退出
            }//switch
        }//else
    }//while
    return opnd.pop();
}
//逆波兰表达式求值
static float rpnEvaluation(char *&RPN, int n){
    stack<float> opnd;
    for (char* p = RPN; p < RPN + n;) {
        if (isdigit(*p)){
            readNum(p, opnd);
        }else{
            if ('!' == *p) {
                float pOpnd = opnd.pop();
                opnd.push(calcu(pOpnd, *p));
            } else {
                float pOpnd2 = opnd.pop();
                float pOpnd1 = opnd.pop();
                opnd.push(calcu(pOpnd1, *p, pOpnd2));
            }
            p++;
        }//else
    }//for
    return opnd.pop();
}
