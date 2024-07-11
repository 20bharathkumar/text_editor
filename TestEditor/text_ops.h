#include "text_editor.h"


void insertText(TextEditor *editor, const char *text);
void deleteCharacters(TextEditor *editor, int length);
void deleteLine(TextEditor *editor);
void copyText(TextEditor *editor, int start, int end);
void cutText(TextEditor *editor, int start, int end);
void pasteText(TextEditor *editor);
void undo(TextEditor *editor);
void redo(TextEditor *editor);
