/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */
#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"

int main()
{
    // Initialize the text editor and stacks
    TextEditor editor;
    reun dyStack;
    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;

    dyStack.redo = &redoStack;
    dyStack.undo = &undoStack;

    editor.head = NULL;
    editor.tail = NULL;
    editor.cursorLine = 0;

    init(&editor, &undoStack, &redoStack);

    // User interaction loop
    char command[256];
    while (1) 
    {
	printf("===============================================================================================\n");
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
         //TODO Remove newline character
	int len = strlen(command);

	if(len > 0 && command[len-1] == '\n')
	    command[len-1] = '\0';

	//exit the exit editor
        if(strcmp(command, "exit") == 0)
	{
            break;
        }
	else if(strcmp(command, "help") == 0)//to print the menu
	{
	    printMenu();
	}
	else	//for text operations
	{
            handleCommand(command, &editor);
        }
    }

    return 0;
}

