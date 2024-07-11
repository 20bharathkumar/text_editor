#include "text_editor.h"

void displayText(TextEditor *editor);
void showCursorPosition(TextEditor *editor);
void findText(TextEditor *editor, const char *searchTerm);
void replaceText(TextEditor *editor, const char *oldTerm, const char *newTerm);
