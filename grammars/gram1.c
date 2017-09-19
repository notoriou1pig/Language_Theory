// No Header
// 23/02/2016 - 02:07:38

/*
** Grammar for the following piece of code
*/

int	main(int argc, char **argv)
{
  int	i;
  i = 0;
  return (i);
}

/*

do-loop	     := #later
for-loop     := #later
cond_block   := '(' expression ')' brace_blocks
while-loop   := 'while' cond_block
if-stmt	     := 'if' cond_block
switch-stmt  := #later

label        := id
goto         := 'goto' label ':'
return       := 'return' '(' expression ')'

compound_stmt:= brace_block
	      | do-loop
	      | for-loop
	      | while-loop
	      | if-stmt
	      | switch-stmt
lenient_stmt := assignment
	      | goto
	      | return
statement    := lenient_stmt
	      | compound_stmt

block_params := '(' paramters ')' brace_blocks
declaration  := specifier id block_params
	      | specifier id

decls        := decls declaration
	      | declaration
statements   := statements statement
	      | statement

block        := decls
              | statements
blocks       := blocks block
	      | block

brace_blocks := '{' blocks '}'
*/
