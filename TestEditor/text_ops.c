
/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */
#include "text_editor.h"
#include "text_ops.h"
#include "file_ops.h"
#include "display_search.h"
#include "redo_undo.h"
#include "curser_navigations.h"

//DynamicArrayStack undoStack,redoStack;
//handing the text operation commands
void handleCommand(char *command, TextEditor *editor)
{
    //to store each part of command
    char cmd[100];
    char arg1[100];
    char arg2[100];

    //for displaying cursor
    if(editor->head != NULL && strcmp(command,"show cursor") == 0)
	showCursorPosition(editor);
    else
    {
	int itm = sscanf(command,"%s %[^\n]",cmd,arg1);

	//for opening file
	if(strcmp("open",cmd) == 0)
	{
	    //int length = atoi(arg1);
	    openFile(editor, arg1);
	    strcpy(editor->f_name,arg1);
	}

	//if the file is opened then operation is performed
	if(editor->head != NULL)
	{
	    if(strcmp("insert",cmd) == 0)	//for insert text
	    {
		//printf("in insert\n");
		//Action.text = *(char *)cmd;
		if(arg1[0] == '\"')
		    insertText(editor, strtok(arg1,"\""));
		else
		    printf("INFO : type help command to get help\n");
	    }
	    else if(strcmp("display",cmd) == 0)	//for displaying file content
	    {
		displayText(editor);
	    }
	    else if(strcmp("save",cmd) == 0)	//saving data to file
	    {
		saveFile(editor,editor->f_name);
	    }
	    else if(strcmp("close",cmd) == 0)	//closing the file
	    {
		closeFile(editor);
	    }
	    else if(strcmp("undo",cmd) == 0)	//undoing the operation
	    {
		undo(editor);
	    }
	    else if(strcmp("redo",cmd) == 0)	//redoing the operation
	    {
		redo(editor);
	    }
	    else if(strcmp("delete",cmd) == 0)	//deleting the line
	    {
		if(strcmp("delete",command) == 0)
		    deleteLine(editor);
		else
		    deleteCharacters(editor,atoi(arg1));	//deleting characters
	    }
	    else if(strcmp("cursorup",cmd) == 0)	//moving cursor up 
	    {
		moveCursorUp(editor);
	    }
	    else if(strcmp("cursordown",cmd) == 0)	//moving cursor down
	    {
		moveCursorDown(editor);
	    }
	    else if(strcmp("cursorleft",cmd) == 0)	//moving cursor left
	    {
		moveCursorLeft(editor);
	    }
	    else if(strcmp("cursorright",cmd) == 0)	//moving cursor right
	    {
		moveCursorRight(editor);
	    }
	    else if(strcmp("jumptostartoffile",cmd) == 0)	//moving cursor to firat line
	    {
		jumpToStartOfFile(editor);
	    }
	    else if(strcmp("jumptoendoffile",cmd) == 0)		//moving cursor to last line
	    {
		jumpToEndOfFile(editor);
	    }
	    else if(strcmp("jumptostartofline",cmd) == 0)	//moving cursor to first char of line
	    {
		jumpToStartOfLine(editor);
	    }
	    else if(strcmp("jumptoendofline",cmd) == 0)		//moving cursor to last char of line
	    {
		jumpToEndOfLine(editor);
	    }
	    else if(strcmp("copy",cmd) == 0)		//copying the char from start to end
	    {
		itm = sscanf(command,"%s %s %s",cmd,arg1,arg2);
		int start = atoi(arg1);
		int end = atoi(arg2);
		copyText(editor, start, end);
	    }
	    else if(strcmp("paste",cmd) == 0)		//pasting the text
	    {
		pasteText(editor);
	    }
	    else if(strcmp("find",cmd) == 0)
	    {
		findText(editor,arg1);
	    }
	    else if(strcmp("cut",cmd) == 0)		//cutting the char from start to end
	    {
		itm = sscanf(command,"%s %s %s",cmd,arg1,arg2);
		int start = atoi(arg1);
		int end = atoi(arg2);
		cutText(editor, start, end);
	    }
	}
	else
	    printf("INFO : type help to get help or open the file first\n");


    }
}

//inserting the text at cursor position
void insertText(TextEditor *editor, const char *text)
{
    Node *new = malloc(sizeof(Node));

    //printf("in fun\n");
    if(text == NULL)
    {
	printf("INFO : No data to insert\n");
	free(new);
	return;
    }
    printf("data %s\n",text);
    //adding data to structure
    new->line = malloc(sizeof(char)*200);
    strcpy(new->line,text);
    new->prev = NULL;
    new->next = NULL;
    Node *temp = editor->tail;
    //printf("data add\n");
    //if the cursor is at first line
    if(editor->cursorLine == 1)
    {
	//printf("head is null\n");
	//editor->head = new;
	(editor->tail)->next = new;
	new->prev = editor->tail;
	editor->tail = new;
	//printf("data added\n");
    }
    else
    {
	//moving till cursor line
	int i=1;
	while(i < editor->cursorLine)
	{
	    //if(i == action.cursorLine)
	    //break;
	    temp = temp->prev;
	    i++;
	}
	printf("%d line\n",i);
	printf("%s data\n",temp->line);
	//if the cursor is at ast line
	if(temp == editor->head)
	{
	    (editor->head)->prev = new;
	    new->next = editor->head;
	    editor->head = new;
	}
	else	//if cursor is at any other line
	{
	    new->next = temp;
	    new->prev = temp->prev;
	    (temp->prev)->next = new;
	    temp->prev = new;
	}
    }
    (editor->cursorLine)++;
    //printf("line %s\n",(editor->head)->line);
    // Record the action for undo
    Action action = {
	.operation = strdup("insert"),
	.text = strdup(text),
	.cursorLine = editor->cursorLine,
	.cursorPos = editor->cursorPos
    };
    //pushing to stack
    pushStack(editor->undo, action);

	free(new);
}

//deleting the line	
void deleteLine(TextEditor *editor)
{
    if (editor->head == NULL)
    {
	printf("No data to delete\n");
	return;
    }

    //moving till cursor line
    int i=1;
    Node *lineToDelete = editor->tail;
    while(i < editor->cursorLine)
    {
	lineToDelete = lineToDelete->prev;
	i++;
    }
    char *deletedText;

    //storing packup and the deleting the ine
    //if cursor is at first line
    if(editor->cursorLine == 1)
    {
	deletedText = strdup(lineToDelete->line);
	editor->tail = (editor->tail)->prev;
	free((editor->tail)->next);
	(editor->tail)->next = NULL;
    }
    else
    {
	deletedText = strdup(lineToDelete->line);
	if(lineToDelete == editor->head)	//if cursor is at last line
	{
	    editor->head = (editor->head)->next;
	    free((editor->head)->prev);
	    (editor->head)->prev = NULL;
	}
	else	//if cursor is at any other line
	{
	    (lineToDelete->prev)->next = lineToDelete->next;
	    (lineToDelete->next)->prev = lineToDelete->prev;
	    free(lineToDelete);
	}
    }
    //storng the action
    Action action = {
	.operation = strdup("delete"),
	.text = deletedText,
	.cursorLine = editor->cursorLine,
	.cursorPos = editor->cursorPos
    };

    (editor->cursorLine)--;

    //pushing to stack
    pushStack(editor->undo, action);

}

//for storing the data
static char data[1023],cut_data[1023],flg = 1;
//coping the data from cursor position of line
void copyText(TextEditor *editor, int start, int end)
{
    flg = 1;
    //moving till cursor line
    Node *temp = editor->tail;
    int i = 1;
    while(temp)
    {
	if(i == editor->cursorLine)
	    break;
	temp = temp->prev;
	//printf("done\n");
	i++;
    }
    //printf("out\n");
    //copying the the chars from start to end
    char *text = temp->line;
    int j = start,k=0;
    while(j < end)
    {
	if(text[j])
	data[k++] = text[j++];
	else
	    break;
    }
    data[k] = '\0';
    printf("copied %s\n",data);

}
//paste the comtent
void pasteText(TextEditor *editor)
{
    //move till cursor line
    int i=1;
    Node *temp = editor->tail;
    while(i < editor->cursorLine)
    {
	temp = temp->prev;
	i++;
    }

    //store packup data
    char *pastedText = strdup(temp->line);
    char new_data[1024];
    int j = 0,k=0;
    //paste the data at cursor position
    while(pastedText[j])
    {
	if(j == editor->cursorPos)
	{
	    strcat(new_data,data);
	    k = strlen(new_data);
	}
	new_data[k++] = pastedText[j++];
	new_data[k] = '\0';
	    //printf("cat %s %d\n",new_data,k);
    }
    new_data[k] = '\0';
    strcpy(temp->line,new_data);
    //temp->line = new_data;
    printf("pasted text %s\n",temp->line);
    //printf("pased text %s\n",cut_data);

    //storng the action
    Action action = {
	.operation = strdup("paste"),
	.text = pastedText,
	.cursorLine = editor->cursorLine,
	.cursorPos = editor->cursorPos
    };
    //push the action to stack
    pushStack(editor->undo, action);

}

//delete chars from position
void deleteCharacters(TextEditor *editor, int length)
{
    //move the cursor till the cursor line
    Node *temp = editor->tail;
    int i=1;
    while(i < editor->cursorLine)
    {
	temp = temp->prev;
	i++;
    }
    //store backupdata
    char *deletedText = strdup(temp->line);
    char new_data[1023];
    //copy the data till cursorposition
    strncpy(new_data,temp->line,editor->cursorPos);
    int pos = editor->cursorPos;
    //copy the data from length till null char
    for(int i=(strlen(temp->line)-editor->cursorPos-length)-3;deletedText[i];i++)
    {
	new_data[pos++] = deletedText[i];
    }
    new_data[pos]='\0';
    printf("deleted %s\n",new_data);
    printf("before %s\n",deletedText);
    temp->line = new_data;
    //storng the action
    Action action = {
	.operation = strdup("deletechar"),
	.text = deletedText,
	.cursorLine = editor->cursorLine,
	.cursorPos = editor->cursorPos
    };
    //push the action to the stack
    pushStack(editor->undo, action);
}
/*cutting chars from start to end*/
void cutText(TextEditor *editor, int start, int end)
{
    flg = 2;
    //move the cursor till the cursor line
    Node *temp = editor->tail;
    int i=1;
    while(i < editor->cursorLine)
    {
	temp = temp->prev;
	i++;
    }
    //store backupdata
    char *deletedText = strdup(temp->line);
    char new_data[1023];
    //copy the data till cursorposition
    strncpy(new_data,temp->line,start);
    int pos = start;
    int j = start,k=0;
    while(j < end)
    {
	if(deletedText[j])
	data[k++] = deletedText[j++];
	else
	    break;
    }
    data[k] = '\0';
    printf("cutted %s\n",data);
    //copy the data from length till null char
    for(int i = end;deletedText[i];i++)
    {
	new_data[pos++] = deletedText[i];
    }
    new_data[pos]='\0';
    printf("after %s\n",new_data);
    printf("before %s\n",deletedText);
    strcpy(temp->line,new_data);
    //temp->line = new_data;
    //editor->cursorPos = start;
    //storng the action
    Action action = {
	.operation = strdup("cut"),
	.text = deletedText,
	.cursorLine = editor->cursorLine,
	.cursorPos = editor->cursorPos
    };
    //push the action to the stack
    pushStack(editor->undo, action);
}


//for printing menu
void printMenu()
{
    printf("\nFile Commands:\n");
    printf("1. open <filename> - open the file to perform operation\n");
    printf("2. save - save the content to the file\n");
    printf("3. close - close the file\n");
    printf("\nText Editor Commands:\n");
    printf("1. insert <text> - Insert text at the current cursor position\n");
    printf("2. delete <num_chars> - Delete a number of characters from the current cursor position\n");
    printf("3. undo - Undo the last operation\n");
    printf("4. redo - Redo the last undone operation\n");
    printf("5. print - Print the current state of the text editor\n");
    printf("6. exit - Exit the text editor\n");
    printf("7. delete - to delete the cursor line\n");
    printf("8. copy <startcharpos> <endcharpos> - copies the characters from start position to end position\n");
    printf("9. paste - paste the copied content to where the cursor is pointing\n");
    printf("\nCursor moving commands:\n");
    printf("1. cursorup - move the cursor one line up\n");
    printf("2. cursordown - move the cursor one line down\n");
    printf("3. cursorleft - move the cursor one char left\n");
    printf("4. cursorright - move the cursor one char right\n");
    printf("5. jumptoendoffile - move the cursor to last line\n");
    printf("6. jumptostartoffile - move the cursor to first line\n");
    printf("7. jumptoendofline - move the cursor to last char of line\n");
    printf("8. jumptostartofline - move the cursor to first char of line\n");
}
