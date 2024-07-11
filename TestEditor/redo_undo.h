#include "text_editor.h"
// Stack operations
void initStack(DynamicArrayStack *stack);
void pushStack(DynamicArrayStack *stack, Action action);
Action popStack(DynamicArrayStack *stack);
int isStackEmpty(DynamicArrayStack *stack);

// Undo/redo operations
void undo(TextEditor *editor);
void redo(TextEditor *editor);

// Utility functions
void init(TextEditor *, DynamicArrayStack *, DynamicArrayStack *); 
