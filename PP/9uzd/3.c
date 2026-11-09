#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point *data;
    int size;
} Stack;

Point createPoint(double x, double y) {
    Point p = {x, y};
    return p;
}

double getDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void printPoint(Point p) {
    printf("(%.2f, %.2f)", p.x, p.y);
}

void initStack(Stack *stack) {
    if (stack == NULL) return;
    stack->data = NULL;
    stack->size = 0;
}

void printStack(Stack *stack) {
    if (stack == NULL) return;

    printf("Taškų stekas:\n");
    for (int i = 0; i < stack->size; i++) {
        printf("  ");
        printPoint(stack->data[i]);
        printf("; atstumas iki pradžios: %.2f\n",
               getDistance(stack->data[i], createPoint(0.0, 0.0)));
    }
}

int getStackSize(Stack *stack) {
    if (stack == NULL) return 0;
    return stack->size;
}

void push(Stack *stack, Point value) {
    if (stack == NULL) return;

    Point *newData = realloc(stack->data,
                             (size_t)(stack->size + 1) * sizeof(Point));
    if (newData == NULL) return;

    stack->data = newData;
    stack->data[stack->size] = value;
    stack->size++;
}

Point top(Stack *stack) {
    if (stack == NULL || stack->size == 0) {
        return createPoint(0.0, 0.0);
    }
    return stack->data[stack->size - 1];
}

Point pop(Stack *stack) {
    if (stack == NULL || stack->size == 0) {
        return createPoint(0.0, 0.0);
    }

    Point value = top(stack);
    stack->size--;

    if (stack->size == 0) {
        free(stack->data);
        stack->data = NULL;
    } else {
        Point *newData = realloc(stack->data,
                                 (size_t)stack->size * sizeof(Point));
        if (newData != NULL) {
            stack->data = newData;
        }
    }

    return value;
}

void destroyStack(Stack *stack) {
    if (stack == NULL) return;
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
}

int main(void) {
    Stack stack;
    initStack(&stack);

    push(&stack, createPoint(2.0, 3.0));
    push(&stack, createPoint(-1.0, 4.0));
    push(&stack, createPoint(0.0, 5.0));
    push(&stack, createPoint(-3.0, -2.0));
    push(&stack, createPoint(6.0, 1.0));

    printStack(&stack);
    printf("Steke yra %d taškai.\n", getStackSize(&stack));

    destroyStack(&stack);
    return 0;
}
