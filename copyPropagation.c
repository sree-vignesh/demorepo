#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#include &lt;stdbool.h&gt;
char *str_replace(char *orig, char *rep, char *with) {
char *result; // the return string
char *ins; // the next insert point
char *tmp; // varies
int len_rep; // length of rep (the string to remove)
int len_with; // length of with (the string to replace rep with)
int len_front; // distance between rep and end of last rep
int count; // number of replacements
// sanity checks and initialization
if (!orig || !rep)
return NULL;
len_rep = strlen(rep);
if (len_rep == 0)
return NULL; // empty rep causes infinite loop during count
if (!with)
with = &quot;&quot;;
len_with = strlen(with);
// count the number of replacements needed
ins = orig;
for (count = 0; (tmp = strstr(ins, rep)); ++count) {
ins = tmp + len_rep;
}
tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
if (!result)
return NULL;
// first time through the loop, all the variable are set correctly
// from here on,
// tmp points to the end of the result string
// ins points to the next occurrence of rep in orig
// orig points to the remainder of orig after &quot;end of rep&quot;
while (count--) {
ins = strstr(orig, rep);
len_front = ins - orig;
tmp = strncpy(tmp, orig, len_front) + len_front;
tmp = strcpy(tmp, with) + len_with;
orig += len_front + len_rep; // move to next &quot;end of rep&quot;
}
strcpy(tmp, orig);
return result;
}
bool is_operator(char c) {
return c == &#39;+&#39; || c == &#39;-&#39; || c == &#39;*&#39; || c == &#39;/&#39; || c == &#39;(&#39; || c == &#39;)&#39;;
}
int calculate(int a, int b, char op)
{
switch (op)
{
case &#39;+&#39;: return a + b;
case &#39;-&#39;: return a - b;
case &#39;*&#39;: return a * b;
case &#39;/&#39;: return a / b;
case &#39;^&#39;: return pow(a, b);
}
return -1;
}
bool is_operand(char c)
{
return strchr(&quot;0123456789&quot;, c);
}
int priority(char c)
{
switch (c)
{
case &#39;+&#39;:
case &#39;-&#39;:
return 0;
case &#39;*&#39;:
case &#39;/&#39;:
return 1;
case &#39;^&#39;:
return 2;
}
return -1;
}
int evaluate(char *expression)
{
int op1;
int op2;
int top = 0;
int ops = 0;
int operand_stack[50];
char operators[50];
char *p = expression;
for (; *p; p++)
{
if (*p == &#39; &#39;)
{
continue;
}
else if (isalpha(*p))
{
return -1;
}
else if (is_operand(*p))
{
operand_stack[++top] = strtol((char*)p, (char**)&amp;p, 10);
p--;
}
else if (is_operator(*p))
{
while (ops) {
if (priority(*p) &lt; priority(operators[ops])) {
op2 = operand_stack[top--];
op1 = operand_stack[top--];
operand_stack[++top] = calculate(op1, op2, operators[ops--]);
}
else {
break;
}
}
operators[++ops] = *p;
}
}
while (ops) {
op2 = operand_stack[top--];
op1 = operand_stack[top--];
operand_stack[++top] = calculate(op1, op2, operators[ops--]);
}
return operand_stack[top];
}
char expressions[50][50];
int n;
void constant_folding() {
for (int i = 0; i &lt; n; i++) {
char *p = strchr(expressions[i], (int)&#39;=&#39;);
if (p) {
char integer[20];
int a = evaluate(p+1);
if (a != -1) {
sprintf(integer, &quot;%d&quot;, a);
strcpy(expressions[i], str_replace(expressions[i], p + 1, integer));
}
}
}
}
// line starts from 0
typedef struct use_def {
int line;
int use_count;
char var[20];
char replacement[20];
int lines_used[20];
} use_def;
use_def use_defs[5];
int use_def_count = 0;
void constant_propogation() {
for (int i = 0; i &lt; use_def_count; i++) {
use_def *a = &amp;use_defs[i];
for (int j = 0; j &lt; a-&gt;use_count; j++) {
strcpy(expressions[a-&gt;lines_used[j]], str_replace(expressions[a-&gt;lines_used[j]], a-
&gt;var, a-&gt;replacement));
}
}
}
int main()
{
printf(&quot;\n\nEnter the number of expressions : &quot;);
scanf(&quot;%d&quot;, &amp;n);
for(int i=0; i&lt;n;i++)
{
scanf(&quot; %[^\n]&quot;, expressions[i]);
}
for (int i = 0; i &lt; n; i++)
{
use_def *a = use_defs + i;
a-&gt;line = i;
char buff[20];
strcpy(buff, expressions[i]);
strcpy(a-&gt;var, strtok(buff, &quot;=&quot;));
if (a-&gt;var) {
strcpy(a-&gt;replacement, strtok(NULL, &quot;&quot;));
for (int j = i + 1; j &lt; n ; j++) {
if (strstr(expressions[j], a-&gt;var)) {
a-&gt;lines_used[a-&gt;use_count++] = j;
}
}
use_def_count++;
}
}
constant_propogation();
constant_folding();
printf(&quot;\nCode after propagation: \n&quot;);
for(int i=0;i&lt;n;i++) {
printf(&quot;%s\n&quot;, expressions[i]);
}
return 0;
}
