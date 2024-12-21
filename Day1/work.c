#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;
    return n;
}

Node* append(Node* head, int value) {
    Node* new_node = createNode(value);
    if (head == NULL || head->value >= value) {
        new_node->next = head;
        return new_node;
    }

    Node* current = head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return head;
}

int main_part1(char argc, char** argv) {
    FILE *file = fopen("input.txt", "r");
    int NUM_LISTS = 2;

    int parsed_nums[NUM_LISTS];
    char line[128];
    int depth = 0;
    Node* left_list = NULL;
    Node* right_list = NULL;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d  %d", &parsed_nums[0], &parsed_nums[1]) == NUM_LISTS) {
            left_list = append(left_list, parsed_nums[0]);
            right_list = append(right_list, parsed_nums[1]);
            depth += 1;
        }
    }
    
    fclose(file);

    int sum = 0;
    Node* current_left_node = left_list;
    Node* current_right_node = right_list;

    while(current_left_node != NULL) {
        if (current_left_node->value > current_right_node->value) {
            sum += current_left_node->value - current_right_node->value;
        } else {
            sum += current_right_node->value - current_left_node->value;
        }
        current_left_node = current_left_node->next;
        current_right_node = current_right_node->next;
    }

    free(current_left_node);
    free(current_right_node);

    printf("\nSUM %d\n", sum);

    return 0;
}

typedef struct DictElement {
    int key;
    int value;
    struct DictElement* next;  
} DictElement;

typedef struct Dict {
    int size;
    DictElement** dict;
} Dict;

Dict* createDict(int size) {
    Dict* table = (Dict*) malloc(sizeof(Dict));
    table->size = size;
    table->dict = (DictElement**) malloc(size * sizeof(DictElement**));
    for (int i = 0; i < size; i++) {
        table->dict[i] = NULL;
    }
    return table;
}

unsigned int hash(const int key, int tableSize) {
    return (unsigned int) (key % tableSize);
}

void insert(Dict* dict, const int key, const int value) {
    unsigned int hashVal = hash(key, dict->size);
    DictElement* current = dict->dict[hashVal];
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    DictElement* newPair = (DictElement*)malloc(sizeof(DictElement));
    newPair->key = key;
    newPair->value = value;
    newPair->next = dict->dict[hashVal];
    dict->dict[hashVal] = newPair;
}

int lookup(Dict* dict, int key) {
    unsigned int index = hash(key, dict->size);
    DictElement* current = dict->dict[index];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

void freeDict(Dict* d) {
    for (int i = 0; i < d->size; i++) {
        DictElement* current = d->dict[i];
        free(current);
    }
    free(d->dict);
    free(d);
}

int main(char argc, char** argv) {
    FILE *file = fopen("input.txt", "r");
    int NUM_LISTS = 2;

    int parsed_nums[NUM_LISTS];
    char line[128];
    int lookup_val, lookup_val2;

    int left_lst[1000];
    int left_lst_cnt = 0;
    Dict* right_dict = createDict(1000);
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d  %d", &parsed_nums[0], &parsed_nums[1]) == NUM_LISTS) {
            left_lst[left_lst_cnt] = parsed_nums[0];
            left_lst_cnt += 1;
            lookup_val2 = lookup(right_dict, parsed_nums[1]);
            if (lookup_val2 == -1) {
                insert(right_dict, parsed_nums[1], 1);
            } else {
                insert(right_dict, parsed_nums[1], lookup_val2 + 1);
            }
        }
    }
    
    fclose(file);

    int sum = 0;
    int current_key;
    for (int i = 0; i < left_lst_cnt; i++) {
        current_key = left_lst[i];
        int numOccurences = lookup(right_dict, current_key);
        // printf("current_key = %d | numOccurences = %d\n", current_key, numOccurences);
        if (numOccurences == -1) {
            numOccurences = 0;
        }
        sum += (current_key * numOccurences);
    }

    printf("\nSUM %d @ left_lst_cnt = %d\n", sum, left_lst_cnt);
    freeDict(right_dict);
    return 0;
}