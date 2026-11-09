#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data; /* Dinaminio masyvo pradžios adresas. */
    int size;  /* Šiuo metu steke esančių elementų skaičius. */
} Stack;

void initStack(Stack *stack) {
    if (stack == NULL) return;

    stack->data = NULL;
    stack->size = 0;
}

void printStack(Stack *stack) {
    if (stack == NULL) return;

    printf("Stekas: ");
    for (int i = 0; i < stack->size; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int getStackSize(Stack *stack) {
    if (stack == NULL) return 0;
    return stack->size;
}

void push(Stack *stack, int value) {
    if (stack == NULL) return;

    int *newData = realloc(stack->data,
                           (size_t)(stack->size + 1) * sizeof(int));
    if (newData == NULL) {
        /* Jei atminties rezervuoti nepavyko, stekas lieka nepakeistas. */
        return;
    }

    stack->data = newData;
    stack->data[stack->size] = value;
    stack->size++;
}

int top(Stack *stack) {
    if (stack == NULL || stack->size == 0) return 0;
    return stack->data[stack->size - 1];
}

int pop(Stack *stack) {
    if (stack == NULL || stack->size == 0) return 0;

    int value = top(stack);
    stack->size--;

    if (stack->size == 0) {
        free(stack->data);
        stack->data = NULL;
    } else {
        int *newData = realloc(stack->data,
                               (size_t)stack->size * sizeof(int));
        /* Jei mažinant nepavyko, senas blokas vis tiek lieka tinkamas. */
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

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printStack(&stack);
    printf("Steko dydis: %d\n", getStackSize(&stack));
    printf("Viršutinis elementas: %d\n", top(&stack));
    printf("Pašalintas elementas: %d\n", pop(&stack));
    printStack(&stack);

    destroyStack(&stack);
    return 0;
}
