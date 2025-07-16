#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char *action;
    char *timestamp;
}draw;

typedef struct Node {
    draw draw;
    struct Node *next;
}Node;


typedef struct {
    Node *top;
}Stack;


Node *createNode(const char * action, const char * timestamp) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if ( newNode == NULL) {
        return NULL;
    }

    newNode -> draw.action = (char *)malloc(strlen(action) *sizeof(char) );
    newNode -> draw.timestamp = (char *)malloc(strlen(timestamp) *sizeof(char) );
    strcpy(newNode -> draw.action, action);
    strcpy(newNode -> draw.timestamp, timestamp);

    newNode -> next = NULL;
    return newNode;
}



Stack *newStack() {
    Stack *newStack = (Stack *)malloc(sizeof(Stack));
    if (newStack == NULL) {
        printf("Loi cap khoi tao Stack !\n");
        return NULL;
    }
    newStack -> top = NULL;
    return newStack;
}

void push(Stack* stack,const char * action, const char * timestamp) {
    Node *newNode = createNode(action, timestamp);
    if (newNode == NULL) {
        return;
    }
    newNode -> next = stack -> top;
    stack -> top = newNode;
}


draw pop(Stack* stack) {
    if (stack -> top == NULL) {
        printf("Stack is empty\n");
        draw null;
        null.action = (char *)malloc(strlen("NULL") *sizeof(char) );
        null.timestamp = (char *)malloc(strlen("NULL") *sizeof(char) );
        strcpy(null.action, "NULL");
        strcpy(null.timestamp, "NULL");


        return null;
    }

    const Node *temp = stack -> top;
    draw infor;

    infor.action =  strdup(temp -> draw.action);
    infor.timestamp =  strdup(temp -> draw.timestamp);
    stack -> top = temp -> next;

    free(temp -> draw.action);
    free(temp -> draw.timestamp);
    free(temp);

    return infor;

}











// DRAW: Thực hiện thao tác vẽ
void actionDraw(Stack *draw);
// UNDO: Hoàn tác thao tác gần nhất
void PRINT(const Stack *draw);
// REDO: Phục hồi thao tác vừa UNDO
void redo(Stack * drawStack, Stack * redo);
// PRINT: In toàn bộ thao tác (vẽ) đã thực hiện


// EXIT: kết thúc chương trình

void freeStack(Stack *s) {
    while (s -> top != NULL) {
        pop(s);
    }
    free(s);
}


void undo(Stack * drawStack, Stack * redo);

int main(void) {
    Stack *draw = newStack();
    Stack *REDO = newStack();
    int choice;


    do {
        printf("|--------------MENU------------|\n");
        printf("1. DRAW\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. PRINT\n");
        printf("5. EXIT\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
               actionDraw(draw);
                break;
            case 2:
                undo(draw, REDO);
                break;
            case 3:
                redo(draw, REDO);
                break;
            case 4:
                PRINT(draw);
                break;
            case 5:
                freeStack(REDO);
                freeStack(draw);

                break;

            default:
                printf("invalid\n");
                break;
        }


    }while ( choice != 5);

    return 0;
}


void actionDraw(Stack *draw){
    char action[30];
    char timestamp[30];
    getchar();
    printf("action: ");
    fgets(action, sizeof(action), stdin);
    action[strlen(action) - 1] = '\0';

    printf("timestamp: ");
    fgets(timestamp, sizeof(timestamp), stdin);
    timestamp[strlen(timestamp) - 1] = '\0';
    push(draw, action,timestamp);



}

void PRINT(const Stack *draw) {
    if (draw -> top == NULL) {
        printf("Stack is empty \n");
        return;
    }

    Node *temp = draw -> top;

    int i  = 1;
    while ( temp != NULL) {

        printf("|%d. Action %5s | timestamp %5s\n",i++, temp -> draw.action, temp -> draw.timestamp);
        temp = temp -> next;

    }
}

void undo(Stack * drawStack, Stack * redo){
     if (drawStack -> top == NULL) {
        printf("Is empty\n");
    }

    const draw temp = pop(drawStack);

   push(redo,temp.action, temp.action);



}

void redo(Stack * drawStack, Stack * redo){
    if (redo -> top == NULL) {
        printf("Is empty\n");
    }

    const draw temp = pop(redo);

    push(drawStack,temp.action, temp.action);

}




