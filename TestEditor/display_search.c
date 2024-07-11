
/*
NAME : BHARATHKUMAR K
DISCRIPTION : TEXT EDITOR TO PERFORM OPERATIONS ON FILE CONTENTS
 */
#include "text_editor.h"
#include "display_search.h"
/*Display the content*/
void displayText(TextEditor *editor)
{
    //if there is no data
    if(editor->head == NULL)
    {
	printf("INFO : No Data\n");
	return;
    }

    Node *temp = editor->tail;
    //printf("line %s\n",(editor->head)->line);
    //printf("sec %s\n",temp->line);
    //to display each line
    int i = 1;
    while(temp != NULL)
    {
	printf("%d. %s\n",i++,temp->line);
	temp = temp->prev;
    }
}

/*displayies the cursor position*/
void showCursorPosition(TextEditor *editor)
{
    if(editor->head == NULL)
    {
	printf("INFO : No data\n");
	return;
    }
    /*Node *lin = editor->tail;
    editor->cursor = lin;*/

    //displyies line number and cursor number
    printf("Cursor Position: Line %d, Column %d\n",editor->cursorLine,editor->cursorPos);
}

/*finding the text*/
void findText(TextEditor *editor, const char *searchTerm)
{
    Node *temp = editor->tail;
    int i = 1,j=0;
    while(temp)
    {
	//if the text is present print the line number
	if(strstr(temp->line,searchTerm) != NULL)
	{
	    printf("INFO : Data %s found at line %d\n",searchTerm,i);
	}
	//else
	//{
	    //printf("no match\n");
	temp = temp->prev;
	i++;
	//}
    }
    
    //while(j < strlen(temp->line))
    //{
//	if()
    /*if(strstr(temp->line,searchTerm) != NULL)
	printf("INFO : Data %s found at line %d\n",searchTerm,i);
    else
	printf("Data not found\n");*/
}
