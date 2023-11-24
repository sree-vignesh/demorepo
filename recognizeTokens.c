#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
bool issymbol(char ch)
{
if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
ch == '/' || ch == ',' || ch == ';' ||
ch == '%' || ch == '=' || ch == '(' || ch == ')' ||
ch == '[' || ch == ']' || ch == '{' || ch == '}')
return (true);
return (false);
}
bool isOperator(char ch)
{
if (ch == '+' || ch == '-' || ch == '*' ||
ch == '/' || ch == '%' ||
ch == '=')
return (true);
return (false);
}
bool isIdentifier(char* str)
{
if (isdigit(str[0])|| issymbol(str[0]) == true)
return (false);
return (true);
}
bool isKeyword(char* str)
{
if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||
!strcmp(str, "break") || !strcmp(str, "int") ||!strcmp(str, "float") || !strcmp(str, "return")
|| !strcmp(str,"char") || !strcmp(str, "long") || !strcmp(str, "void"))
return (true);
return (false);
}
bool isInteger(char* str)
{
int i, len = strlen(str);
if (len == 0)
return (false);
for (i = 0; i < len; i++) {
if (!isdigit(str[i])|| (str[i] == '-' && i > 0))
return (false);
}
return (true);
}
bool isNumber(char* str)
{
int i, len = strlen(str);
bool hasDecimal = false;
if (len == 0)
return (false);
for (i = 0; i < len; i++) {
if (isdigit(str[i]) && str[i] != '.' || (str[i] == '-' && i > 0))
return (false);
if (str[i] == '.')
hasDecimal = true;
}
return (hasDecimal);
}
char* subString(char* str, int left, int right)
{
int i;
char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));
for (i = left; i <= right; i++)
subStr[i - left] = str[i];
subStr[right - left + 1] = '\0';
return (subStr);
}
void detectTokens(char* str) {
int left = 0, right = 0;
int length = strlen(str);
while (right <= length && left <= right) {
if (issymbol(str[right]) == false)
right++;
if (issymbol(str[right]) == true && left == right) {
if (isOperator(str[right]) == true)
printf("'%c'is an operator\n", str[right]);
right++;
left = right;
} else if (issymbol(str[right]) == true && left != right || (right == length && left !=
right)) {
char* subStr = subString(str, left, right - 1);
if (isKeyword(subStr) == true)
printf("'%s' is a keyword\n", subStr);
else if (isInteger(subStr) == true)
printf("'%s' is an integer\n", subStr);
else if (isIdentifier(subStr) == true
&& issymbol(str[right - 1]) == false)
printf("'%s' is an identifier \n", subStr);
else if (isIdentifier(subStr) == false
&& issymbol(str[right - 1]) == false)
printf("Invalid Identifier : '%s'\n", subStr);
left = right;
}
}
}
int main()
{
char str[100];
printf("Enter a C Program\n");
gets(str);
detectTokens(str);
return (0);
}
