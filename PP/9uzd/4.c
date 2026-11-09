#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct List {
    Point value;
    struct List *next;
} List;

Point createPoint(double x, double y) {
    Point p = {x, y};
    return p;
}

void printPoint(Point p) {
    printf("(%.2f, %.2f)\n", p.x, p.y);
}

List *createList(Point value) {
    List *element = malloc(sizeof(List));
    if (element == NULL) return NULL;

    element->value = value;
    element->next = NULL;
    return element;
}

void printList(List *list) {
    if (list == NULL) return;

    printPoint(list->value);
    printList(list->next);
}

int getListSize(List *list) {
    int size = 0;
    while (list != NULL) {
        size++;
        list = list->next;
    }
    return size;
}

void insertElement(List **list, Point value) {
    if (list == NULL) return;

    List *element = createList(value);
    if (element == NULL) return;

    element->next = *list;
    *list = element;
}

Point getElement(List *list) {
    if (list == NULL) return createPoint(0.0, 0.0);
    return list->value;
}

Point deleteElement(List **list) {
    if (list == NULL || *list == NULL) {
        return createPoint(0.0, 0.0);
    }

    Point value = getElement(*list);
    List *oldFirst = *list;
    *list = oldFirst->next;
    free(oldFirst);

    return value;
}

void destroyList(List **list) {
    if (list == NULL) return;

    while (*list != NULL) {
        List *next = (*list)->next;
        free(*list);
        *list = next;
    }
}

int main(void) {
    List *list = NULL;

    insertElement(&list, createPoint(1.0, 2.0));
    insertElement(&list, createPoint(-3.0, 4.0));
    insertElement(&list, createPoint(5.0, -2.0));

    printf("Taškų sąrašas:\n");
    printList(list);
    printf("Sąrašo dydis: %d\n", getListSize(list));

    Point first = getElement(list);
    printf("Pirmas taškas: ");
    printPoint(first);

    Point removed = deleteElement(&list);
    printf("Pašalintas taškas: ");
    printPoint(removed);

    destroyList(&list);
    return 0;
}
