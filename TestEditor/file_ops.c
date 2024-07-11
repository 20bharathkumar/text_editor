
/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */
#include "text_editor.h"
#include "file_ops.h"
#include "redo_undo.h"

void openFile(TextEditor *editor, const char *filename)
{
    FILE *fp = fopen(filename,"r");

    if(!fp)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char line[200];

    while(fgets(line,sizeof(line),fp) != NULL)
    {
	Node *new = malloc(sizeof(Node));
	new->line = malloc(strlen(line) + 1);
	//printf("%s\n",line);
	int len = sizeof(line),i=0;
	while(line[i])
	{
	    if(line[i] == '\n')
		line[i] = '\0';
		//printf("%d im in",i);
	    i++;
	}
	/*if(len > 0 && (line[len-1] == '\n'))
	{
	    line[len-1] = '\0';
	    //printf("made null\n");
	}*/

	strcpy(new->line,line);
	if(editor->head == NULL && editor->tail == NULL)
	{
	    //printf("im in\n");
	    editor->head = new;
	    editor->tail = new;
	    new->prev = NULL;
	    new->next = NULL;
	    //new->line = line;
	    //printf("im out tail %s\n",(editor->tail)->line);
	}
	else
	{
	    //new->line = line;
	    new->prev = NULL;
	    new->next = editor->head;
	    (editor->head)->prev = new;
	    editor->head = new;
	    //printf("im head %s\n",(editor->head)->line);
	    //printf("im tail %s\n",(editor->tail)->line);
	}
	(editor->cursorLine)++;

    }
    //editor->cursorLine = 1;
    editor->cursorPos = 1;
    editor->cursor = editor->tail;

	    //printf("im tail %s\n",(editor->tail)->line);
	    //printf("im head %s\n",(editor->head)->line);
}

void saveFile(TextEditor *editor, const char *filename)
{
    FILE *fp = fopen(filename,"w");
    if(!fp)
    {
	printf("Error : No file\n");
	return;
    }
    if(editor->head == NULL)
    {
	printf("INFO : NO Data\n");
	return;
    }
    
    Node *temp = editor->tail;
    while(temp != NULL)
    {
	fprintf(fp,"%s\n",temp->line);
	temp = temp->prev;
    }
    
    // Clear the redo stack
    while (!isStackEmpty(editor->redo)) {
	popStack(editor->redo);
    }
}

void closeFile(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("INFO : No file opened\n");
	return;
    }
    
    //delet first logic
    while(editor->head != NULL)
    {
        //if there is only one node
        if(editor->head == editor->tail)
        {
            free(editor->head);
            editor->head = NULL;
            editor->tail = NULL;
	    return;
        }
        //deleting first node
        editor->head = (editor->head)->next;
        free((editor->head)->prev);
        (editor->head)->prev = NULL;
    }
}
