%{
int a,b,flag=0;
%}
dig [0-9]*
add "+"
sub "-"
mul "*"
div "/"
Rule section
%%
{dig} {dig();}
{add} {flag=1;}
{sub} {flag=2;}
{mul} {flag=3;}
{div} {flag=4;}
\n {printf("The answer is:%d\n",a);}
%%
dig()
{
if(flag==0)
{
a=atof(yytext);
}
else
{
b=atof(yytext);
switch(flag)
{
case 1:
a=a+b;
break;
case 2:
a=a-b;
break;
case 3:
a=a*b;
break;
case 4:
a=a/b;
break;
}
}
}
int main()
{
// The function that starts the analysis
yylex();
return 0;
}
int yywrap(void) {}
