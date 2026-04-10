#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the operation
typedef struct Operation {
    char type[5];          // "add", "sub", "mul", "div"
    int operand;
    struct Operation* next;
} Operation;

// Helper function to create a new operation node
Operation* create_operation(char* t, int o) {
    Operation* new_node = (Operation*)malloc(sizeof(Operation));
    if (new_node == NULL) { //check if we can allocate the memory
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(new_node->type, t);
    new_node->operand = o;
    new_node->next = NULL;
    return new_node;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sequences_sample N\n");
        return 1;
    }

    int current_value = atoi(argv[1]);
    char input[10];

    Operation* head = NULL;
    Operation* tail = NULL;

    // Use scanf to read strings from stdin
    while (scanf("%s", input) != EOF) {
        if (strcmp(input, "n") == 0) {
            // Traverse the linked list to apply operations
            Operation* current_op = head;
            while (current_op != NULL) {
                if (strcmp(current_op->type, "add") == 0) {
                    current_value += current_op->operand;
                } else if (strcmp(current_op->type, "sub") == 0) {
                    current_value -= current_op->operand;
                } else if (strcmp(current_op->type, "mul") == 0) {
                    current_value *= current_op->operand;
                } else if (strcmp(current_op->type, "div") == 0) {
                    // Check for division by zero to be safe
                    if (current_op->operand != 0) {
                        current_value /= current_op->operand;
                    }
                }
                current_op = current_op->next;
            }
            printf("%d\n", current_value);

        } else if (strcmp(input, "add") == 0 || strcmp(input, "sub") == 0 || 
                   strcmp(input, "mul") == 0 || strcmp(input, "div") == 0) {
            
            int val;
            if (scanf("%d", &val) == 1) {
                Operation* new_node = create_operation(input, val);
                if (!head) {
                    head = tail = new_node;
                } else {
                    tail->next = new_node;
                    tail = new_node;
                }
            }
        }
    }

    // Free allocated memory
    while (head != NULL) {
        Operation* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}