#include&lt;stdio.h&gt;
#include&lt;conio.h&gt;
int main()
{
int a,b;
int op;
printf(&quot; 1.Addition\n 2.Subtraction\n 3.Multiplication\n
4.Division\n&quot;);
printf(&quot;Enter the values of a &amp; b: &quot;);
scanf(&quot;%d %d&quot;,&amp;a,&amp;b);
printf(&quot;Enter your Choice : &quot;);
scanf(&quot;%d&quot;,&amp;op);
switch(op)
{
case 1 :
printf(&quot;Sum of %d and %d is : %d&quot;,a,b,a+b);
break;
case 2 :
printf(&quot;Difference of %d and %d is : %d&quot;,a,b,a-b);
break;
case 3 :
printf(&quot;Multiplication of %d and %d is : %d&quot;,a,b,a*b);
break;
case 4 :
printf(&quot;Division of Two Numbers is %d : &quot;,a/b);
break;
default :
printf(&quot; Enter Your Correct Choice.&quot;);
break;
}
return 0;
}
