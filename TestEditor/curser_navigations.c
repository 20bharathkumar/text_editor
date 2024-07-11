/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */

#include "curser_navigations.h"
#include "text_editor.h"

/*Moving cursor to upper line*/
void moveCursorUp(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    //if cyrsor line is at first line
    if(editor->cursorLine > 1)
    {
	editor->cursorLine--;
	printf("cursor is moved up one line\n");
    }
    else
	printf("Cursor is at first line\n");
    editor->cursorPos = 1;
}
/*Moving cursor to lower line*/
void moveCursorDown(TextEditor *editor)
{
    //to calculate number of lines
    int i=0;
    Node *temp = editor->tail;
    while(temp)
    {
	temp = temp->prev;
	i++;
    }

    //if there is no data
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    //if cursor is not at last line
    if(editor->cursorLine < i)
    {
	editor->cursorLine++;
	printf("cursor is moved down one line\n");
    }
    else
	printf("Cursor is at last line\n");
    editor->cursorPos = 1;
}

/*Moving cursor one char left*/
void moveCursorLeft(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    if(editor->cursorPos > 1)
    editor->cursorPos--;
    else
	printf("Cursor is at start of line\n");
}
/*Moving cursor one char right*/
void moveCursorRight(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    //fetching the cursor line data
    int i=1;
    Node *temp = editor->tail;
    while(i < editor->cursorLine)
    {
	temp = temp->prev;
	i++;
    }
    //i=0;
    //cursor position should not be end of line
    if(editor->cursorPos < strlen(temp->line))
	editor->cursorPos++;
    else
	printf("Cursor is at end of the line\n");
}
/*Moving the cursor to firstline*/
void jumpToStartOfFile(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    editor->cursorLine = 1;
    editor->cursorPos = 1;
}
/*Moving the cursor to last line*/
void jumpToEndOfFile(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    //counting number of lines
    int i=0;
    Node *temp = editor->tail;
    while(temp)
    {
	temp = temp->prev;
	i++;
    }
    //assingning count to cursor line
    editor->cursorLine = i;
    editor->cursorPos = 1;

}
/*Moving cursor to start char of line*/
void jumpToStartOfLine(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    editor->cursorPos = 1;
}
/*Moving cursor to end of the line*/
void jumpToEndOfLine(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("No data\n");
	return;
    }
    //to move the cursor to end of line
    int i=1;
    Node *temp = editor->tail;
    while(i < editor->cursorLine)
    {
	temp = temp->prev;
	i++;
    }
    editor->cursorPos = strlen(temp->line);
}
