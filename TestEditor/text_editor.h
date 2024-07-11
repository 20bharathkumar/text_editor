#ifndef TEXT_EDITOR
#define TEXT_EDITOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

// Define the structure for a node in the linked list (each line in the editor)
typedef struct Node {
    char *line;
    struct Node *prev;
    struct Node *next;
} Node;
// Define the structure for an action (used for undo/redo operations)
typedef struct {
    char *operation;  // Operation type ("insert" or "delete")
    char *text;       // Text involved in the operation
    int cursorLine;   // Line number where the operation occurred
    int cursorPos;    // Column position where the operation occurred
} Action;
// Define the structure for a dynamic array stack (used for undo/redo stacks)
typedef struct {
    Action *actions;  // Dynamic aTrray of actions
    int size;         // Current size of the stack
    int capacity;     // Current capacity of the stack
} DynamicArrayStack;

// Define the structure for the text editor
typedef struct {
    Node *head;       // Pointer to the first line
    Node *tail;       // Pointer to the last line
    Node *cursor;     // Pointer to the current line where the cursor is
    char f_name[20];
    int cursorLine;   // Line number of the cursor
    int cursorPos;    // Column position of the cursor
    DynamicArrayStack *redo;
    DynamicArrayStack *undo;
} TextEditor;



typedef struct
{
    DynamicArrayStack *redo;
    DynamicArrayStack *undo;
}reun;
void printMenu();

void handleCommand(char *command, TextEditor *editor);


#endif
