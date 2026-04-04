#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Operation { // operation we be in the form {(type, operand) -> next} eg {(add, 1) -> (mul, 2) -> nullptr}
    string type; // can only be (add, sub, mul ,div)
    int operand; // number 
    Operation* next; //points to the next node
Operation(string t, int o) : type(t), operand(o), next(nullptr) {}
};

int main(int argc, char const *argv[]){
if (argc != 2) { // check if user use the program correctly
        cout << "Usage: ./sequences_sample N";
    }
string input;

int current_value = atoi(argv[1]); //get the value from command line argument

Operation* head = nullptr; //start
Operation* tail = nullptr; //end
while (cin >> input) {
    if (input == "n") {
            // Traverse the linked list to apply operations
            Operation* current_op = head;
            while (current_op != nullptr) { // keep calculating until end of the list
                if (current_op->type == "add") {
                    current_value += current_op->operand; // +
                } else if (current_op->type == "sub") {
                    current_value -= current_op->operand; // -
                } else if (current_op->type == "mul") {
                    current_value *= current_op->operand; // *
                } else if (current_op->type == "div") { 
                        current_value /= current_op->operand; // /
                }
                current_op = current_op->next; // go to next operation
            }
            cout << current_value << endl; // print statment

        } 
        else if (input == "add" || input == "sub" || input == "mul" || input == "div") { // Handle operator input (add, sub, mul, div)
        // This is a valid operator, now we must get the number
            int val;
            if (std::cin >> val) {
                Operation* new_node = new Operation(input, val); // creation of a new node of operation from the givin inputs
                if (!head) { // check if operation is empty
                    head = tail = new_node; // set op 1 and op 2 to the givin op
                } else {
                    tail->next = new_node; // op n points to op n+1
                    tail = new_node; // set the last op to op n+1
                }
            }
        }
    } // if not (add, sub, mul, div) skip the word

while (head != nullptr) { //free memory
        Operation* temp = head; // start from the start
        head = head->next; //update head to the next value to avoid dangling pointer when temp is freed
        delete temp; // continue the loop until the end of the linked list (aka nullpointer)
    }

    return 0;
}