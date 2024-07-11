
/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */
#include "text_editor.h"
#include "redo_undo.h"
#include "text_ops.h"

/*initalizing*/
void init(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    //head, tail, and cursor are null initally
    editor->head = editor->tail = editor->cursor = NULL;
    //cursor line and position are zero
    editor->cursorLine = editor->cursorPos = 0;

    initStack(undoStack);
    initStack(redoStack);
    editor->redo = redoStack;
    editor->undo = undoStack;
}

/*initalizing dynamic array*/
void initStack(DynamicArrayStack *stack)
{
    //allocating memory for stack
    stack->actions = (Action *)malloc(INITIAL_CAPACITY * sizeof(Action));
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
}

/*pushing to the push stack*/
void pushStack(DynamicArrayStack *stack, Action action)
{
    //if the size is more
    if (stack->size >= stack->capacity)
    {
	stack->capacity *= 2;
	//reallocate the memory
	stack->actions = (Action *)realloc(stack->actions, stack->capacity * sizeof(Action));
    }
    //storing the action in indexes
    stack->actions[stack->size++] = action;
}

/*poping from the popstack*/
Action popStack(DynamicArrayStack *stack)
{
    //if stack is empty
    if (isStackEmpty(stack))
    {
	Action emptyAction = {NULL, NULL, -1, -1};
	return emptyAction;
    }
    //if stack is not empty decrement the size of stack
    return stack->actions[--stack->size];
}

/*if stack is empty*/
int isStackEmpty(DynamicArrayStack *stack)
{
    return stack->size == 0;
}

/*Redoing the operation*/
void redo(TextEditor *editor)
{
    //if stack is empty
    if (isStackEmpty(editor->redo))
	return;

    //poping the index from stack
    Action action = popStack(editor->redo);
    //checking if the operation is insert
    if (strcmp(action.operation, "insert") == 0)
    {
	//creating new node addong data
	Node *temp = editor->tail;
	Node *new = malloc(sizeof(Node));
	new->line = action.text;
	new->prev = NULL;
	new->next = NULL;
	//if the node is first node
	if(action.cursorLine == 1)
	{
	    editor->cursorLine++;
	    (editor->tail)->next = new;
	    new->prev = editor->tail;
	    editor->tail = new;
	}
	else
	{
	    //moving cursor to that node
	    int i=1;
	    while(i < editor->cursorLine)
	    {
		if(i == action.cursorLine)
		    break;
		temp = temp->prev;
		i++;
	    }
	    //if node is last node
	    if(temp == editor->head)
	    {
		editor->cursorLine++;
		(editor->head)->prev = new;
		new->next = editor->head;
		editor->head = new;

	    }
	    else//if node is any other intermediate node
	    {
		editor->cursorLine++;
		new->next = temp;
		new->prev = temp->prev;
		(temp->prev)->next = new;
		temp->prev = new;
	    }
	}
	//insertText(editor,action.text);
	// Re-insert the text
	/*int len = strlen(action.text);
	  editor->cursorPos += len;*/
    }
    else if (strcmp(action.operation, "delete") == 0)	//if the operation is delete
    {
	// Re-delete the text
	int len = strlen(action.text);
	//int len = strlen(action.text);
	/*editor->head = (editor->head)->next;
	editor->cursorPos -= len;*/
	Node *temp = editor->tail;
	//if the undoed line is at first line
	if(action.cursorLine == 1)
	{
	    editor->tail = (editor->tail)->prev;
	    free((editor->tail)->next);
	    (editor->tail)->next = NULL;
	    (editor->cursorLine)--;
	}
	else
	{
	    //moving the cursor to action line
	    int i=1;
	    while(i < action.cursorLine)
	    {
		temp = temp->prev;
		i++;
	    }
	    //if the undoed line is at last line
	    if(temp == editor->head)
	    {
		editor->head = (editor->head)->next;
		free((editor->head)->prev);
		(editor->head)->prev = NULL;
		(editor->cursorLine)--;
	    }
	    else //if the undoed line is at intermediate line
	    {
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
		free(temp);
		(editor->cursorLine)--;
	    }
	}
    }
    //if the action is paste or deletechar or cut
    else if (strcmp(action.operation, "paste") == 0 || strcmp(action.operation, "deletechar") || strcmp(action.operation, "cut") == 0) //if the operation is deletechar
    {

	Node *temp = editor->tail;
	int i=1;
	    while(i < action.cursorLine)
	    {
		temp = temp->prev;
		i++;
	    }
	    //befor replacing storing the data
	    char *dup = strdup(temp->line);
	    //adding data from action text to line
	    temp->line = action.text;
	    //replacing text with old text
	    action.text = dup;
    }


    //pushing index data into undo stack
    pushStack(editor->undo, action);
}

/*Performing undo operation*/
void undo(TextEditor *editor)
{
    //checking if stack is empty or not
    if (isStackEmpty(editor->undo))
    {
	printf("Stack is empty\n");
	return;
    }
    else
	printf("not empty\n");

    /*Node *loc = editor->tail;
      int i=0;
      while(i < editor->cursorLine)
      {
      loc = loc->prev;
      i++;
      }*/
    //storing index data of stack
    Action action = popStack(editor->undo);
    //if the operation is insert
    if (strcmp(action.operation, "insert") == 0)
    {
	// Remove the inserted text
	int len = strlen(action.text);
	Node *temp = editor->tail;
	//if the text is at first line
	if(action.cursorLine == 1)
	{
	    editor->tail = (editor->tail)->prev;
	    free((editor->tail)->next);
	    (editor->tail)->next = NULL;
	    (editor->cursorLine)--;
	}
	else
	{
	    //moving to cursor line
	    int i=1;
	    while(i < action.cursorLine)
	    {
		temp = temp->prev;
		i++;
	    }
	    //if the text inserted at last line
	    if(temp == editor->head)
	    {
		editor->head = (editor->head)->next;
		free((editor->head)->prev);
		(editor->head)->prev = NULL;
		(editor->cursorLine)--;
	    }
	    else //if the text inserted at intermediate line	
	    {
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
		free(temp);
		(editor->cursorLine)--;
	    }
	}
	//memmove(editor->cursorLine + editor->cursorPos - len, editor->cursorLine + editor->cursorPos, strlen(editor->cursorLine) - editor->cursorPos + 1);
	//editor->cursorPos -= len;
    }
    else if (strcmp(action.operation, "delete") == 0)	//if the operation is delte
    {
	//inserting the deleted line
	//creating node and adding the data of deleted node
	Node *temp = editor->tail;
	Node *new = malloc(sizeof(Node));
	new->line = action.text;
	new->prev = NULL;
	new->next = NULL;
	//if first line was deleted 
	if(action.cursorLine == 1)
	{
	    //insert at first
	    editor->cursorLine++;
	    (editor->tail)->next = new;
	    new->prev = editor->tail;
	    editor->tail = new;
	}
	else
	{
	    //moving to the deleted line
	    int i=1;
	    while(i < editor->cursorLine)
	    {
		if(i == action.cursorLine)
		    break;
		temp = temp->prev;
		i++;
	    }
	    printf("%d node\n",i);
	    printf("data %s\n",temp->line);
	    //if last line was deleted
	    if(temp == editor->head)
	    {
		//insert at last
		editor->cursorLine++;
		(editor->head)->prev = new;
		new->next = editor->head;
		editor->head = new;
	    }
	    else	//if the intermediate line was deleted
	    {
		//inserte after
		editor->cursorLine++;
		new->next = temp;
		new->prev = temp->prev;
		(temp->prev)->next = new;
		temp->prev = new;

	    }
	}
	printf("action %s, data %s\n",action.operation,action.text);


	// Insert the deleted text back
    }
    else if (strcmp(action.operation, "paste") == 0)	//if the operation is paste
    {
	Node *temp = editor->tail;
	int i=1;
	    while(i < action.cursorLine)
	    {
		temp = temp->prev;
		i++;
	    }
	    //befor replacing storing the data
	    char *dup = strdup(temp->line);
	    //adding data from action text to line
	    temp->line = action.text;
	    //replacing text with old text
	    action.text = dup;
    }
    else if (strcmp(action.operation, "deletechar") == 0 || strcmp(action.operation, "cut") == 0) //if the operation is deletechar or cut
    {
	Node *temp = editor->tail;
	int i=1;
	    while(i < action.cursorLine)
	    {
		temp = temp->prev;
		i++;
	    }
	    //befor replacing storing the data
	    char *dup = strdup(temp->line);
	    //adding data from action text to line
	    temp->line = action.text;
	    //replacing text with old text
	    action.text = dup;
    }

    //pushing index data into redo stack
    pushStack(editor->redo, action);
}
