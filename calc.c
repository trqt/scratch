#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef _Bool bool;
#define true 1
#define false 0

typedef struct {
    long data;
    void* next;
} node;


// TODO: Arena allocator
node* stack_push(node* head, long value){
    node* new = calloc(1, sizeof(node));

    new->next = head;
    new->data = value;
    return new;
}

node* stack_pop(node* head, long* value){
    *value = head->data;
    node* newhead = head->next; 
    free(head);
    return newhead;
}

inline bool is_num(char c){
    return c >= '0' && c <= '9';
}

bool is_operand(char c){
    switch(c){
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
        return true;
        default:
        return false;
    }
}

long calc(char* buf){
    char* op;
    node* stack = NULL;
    while((op = strsep(&buf, " "))){
        if((strlen(op) == 1 || strlen(op) == 2 && op[1] == '\n') && is_operand(op[0])) {
            long op1 = 0;
            long op2 = 0;
            stack = stack_pop(stack, &op1);
            stack = stack_pop(stack, &op2);
            long res; 
            switch(op[0]){
                case '+':
                res = op1 + op2;
                case '-':
                res = op1 - op2;
                case '/':
                res = op1 / op2;
                case '*':
                res = op1 * op2;
                case '^':
                res = op1 ^ op2; // TODO: pow instead of xor
 
            }

            stack = stack_push(stack, res);
             
        }

        char* endptr;
        long val = strtol(op, &endptr, 10);

        if(endptr == op){
            // No digits
            continue;
        }
        stack = stack_push(stack, val);
    }
    long res; 
    stack = stack_pop(stack, &res);

    return res;
}

int main(void){
    // use shunting yard to make a infix too
    char buf[4096];
    fgets(buf, 4096, stdin);

    long res = calc(buf);

    printf("%lu", res);
}
