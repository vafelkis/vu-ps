#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoublyLinkedList {
    char **words;                    
    size_t wordCount;                
    struct DoublyLinkedList *prev;
    struct DoublyLinkedList *next;
} DoublyLinkedList;

static char *copyString(const char *source) {
    if (source == NULL) return NULL;

    size_t length = strlen(source) + 1;
    char *copy = malloc(length);
    if (copy == NULL) return NULL;

    memcpy(copy, source, length);
    return copy;
}

void initDoublyLinkedList(DoublyLinkedList **head,
                          DoublyLinkedList **tail) {
    if (head != NULL) *head = NULL;
    if (tail != NULL) *tail = NULL;
}

DoublyLinkedList *createWordSet(const char *const words[], size_t count) {
    if (count > 0 && words == NULL) return NULL;

    DoublyLinkedList *node = malloc(sizeof(DoublyLinkedList));
    if (node == NULL) return NULL;

    node->words = NULL;
    node->wordCount = 0;
    node->prev = NULL;
    node->next = NULL;

    if (count > 0) {
        node->words = calloc(count, sizeof(char *));
        if (node->words == NULL) {
            free(node);
            return NULL;
        }

        for (size_t i = 0; i < count; i++) {
            node->words[i] = copyString(words[i]);
            if (node->words[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(node->words[j]);
                }
                free(node->words);
                free(node);
                return NULL;
            }
            node->wordCount++;
        }
    }

    return node;
}

void appendWordSet(DoublyLinkedList **head, DoublyLinkedList **tail,
                   const char *const words[], size_t count) {
    if (head == NULL || tail == NULL) return;

    DoublyLinkedList *node = createWordSet(words, count);
    if (node == NULL) return;

    node->prev = *tail;

    if (*tail != NULL) {
        (*tail)->next = node;
    } else {
        *head = node;
    }

    *tail = node;
}

void sortWords(DoublyLinkedList *node) {
    if (node == NULL || node->wordCount < 2) return;

    for (size_t i = 0; i < node->wordCount - 1; i++) {
        for (size_t j = 0; j < node->wordCount - 1 - i; j++) {
            if (strcmp(node->words[j], node->words[j + 1]) > 0) {
                char *temporary = node->words[j];
                node->words[j] = node->words[j + 1];
                node->words[j + 1] = temporary;
            }
        }
    }
}

void sortAllWords(DoublyLinkedList *head) {
    while (head != NULL) {
        sortWords(head);
        head = head->next;
    }
}

void sortListByWordCount(DoublyLinkedList *head, int descending) {
    if (head == NULL) return;

    int swapped;
    do {
        swapped = 0;
        for (DoublyLinkedList *node = head; node->next != NULL;
             node = node->next) {
            size_t left = node->wordCount;
            size_t right = node->next->wordCount;
            int shouldSwap = descending ? (left < right) : (left > right);

            if (shouldSwap) {
                char **temporaryWords = node->words;
                size_t temporaryCount = node->wordCount;

                node->words = node->next->words;
                node->wordCount = node->next->wordCount;

                node->next->words = temporaryWords;
                node->next->wordCount = temporaryCount;
                swapped = 1;
            }
        }
    } while (swapped);
}

void printDoublyLinkedList(DoublyLinkedList *head) {
    int setNumber = 1;

    while (head != NULL) {
        printf("%d rinkinys (%zu ž.): ", setNumber, head->wordCount);
        for (size_t i = 0; i < head->wordCount; i++) {
            printf("%s", head->words[i]);
            if (i + 1 < head->wordCount) printf(", ");
        }
        printf("\n");

        setNumber++;
        head = head->next;
    }
}

void destroyDoublyLinkedList(DoublyLinkedList **head,
                             DoublyLinkedList **tail) {
    if (head == NULL) return;

    DoublyLinkedList *node = *head;
    while (node != NULL) {
        DoublyLinkedList *next = node->next;

        for (size_t i = 0; i < node->wordCount; i++) {
            free(node->words[i]);
        }
        free(node->words);
        free(node);

        node = next;
    }

    *head = NULL;
    if (tail != NULL) *tail = NULL;
}

int main(void) {
    DoublyLinkedList *head;
    DoublyLinkedList *tail;
    initDoublyLinkedList(&head, &tail);

    const char *set1[] = {"kriause", "obuolys", "bananas"};
    const char *set2[] = {"kate", "skruzdė"};
    const char *set3[] = {"vienas", "du", "trys", "keturi"};

    appendWordSet(&head, &tail, set1, 3);
    appendWordSet(&head, &tail, set2, 2);
    appendWordSet(&head, &tail, set3, 4);

    printf("Pradiniai rinkiniai:\n");
    printDoublyLinkedList(head);

    sortAllWords(head);
    printf("\nSurikiuoti žodžiai kiekviename rinkinyje:\n");
    printDoublyLinkedList(head);

    sortListByWordCount(head, 0); /* 0 - didėjimo tvarka. */
    printf("\nRinkiniai pagal dydį (didėjimo tvarka):\n");
    printDoublyLinkedList(head);

    sortListByWordCount(head, 1); /* 1 - mažėjimo tvarka. */
    printf("\nRinkiniai pagal dydį (mažėjimo tvarka):\n");
    printDoublyLinkedList(head);

    destroyDoublyLinkedList(&head, &tail);
    return 0;
}
