########
## Simple C Grammar


digit	     := ['0' - '9']
num          := num digit
	      | digit

parent_l     := '('
parent_r     := ')'

curve_l      := '{'
curve_r      := '}'

bracket_l    := '['
bracket_r    := ']'

charac	     := ['a' - 'z']
	      | ['A' - 'Z']
alpha	     := alpha charac
	      | charac
alphanum     := alpha
	      | num
alphanumeric := alphanumeric alphanum
	      | alphanum
literal	     := num
	      | '"' alphanumeric '"'
id	     := alpha alphanumeric
	      | alpha

term_op	     := '+'
	      | '-'
	      | '*'
	      | '/'
	      | '%'
term_comp    := '=='
	      | '!='
	      | '>'
	      | '<'
	      | '>='
	      | '<='
term_log_op  := '||'
	      | '&&'
term_bin_op  := '!'
	      | '^'
	      | '&'
	      | '|'

operation    := expression term_op expression
comparaison  := expression term_comp expression


arguments    := arguments ',' expression
              | expression
func_call    := id '(' arguments ')'
expression   := operation
	      | func_call
	      | comparaison
	      | id
	      | literal


user_block  := user_block specifier id
	     | specifier id
union_def   := 'union' user_block
struct_def  := 'struct' user_block
func_proto  := specifier id '(' params ')'
definition  := func_proto
	     | struct_def
	     | union_def


cond_block   := '(' expression ')' brace_blocks
while-loop   := 'while' cond_block
if-stmt	     := 'if' cond_block
condi_stmt   := brace_block
	      | while-loop
	      | if-stmt


assignment   := id '=' expression
label        := id
goto         := 'goto' label ':'
return       := 'return' '(' expression ')'
lenient_stmt := assignment
	      | goto
	      | return
	      | definition
              | expression


statement    := lenient_stmt
	      | condi_stmt
statements   := statements statement
	      | statement


specifier    := c_type
param        := specifier id
params       := params ',' param
	      | param
block_params := '(' paramters ')' brace_blocks
declaration  := specifier id block_params
	      | specifier id

decls        := decls declaration
	      | declaration

block        := decls
              | statements
blocks       := blocks block
	      | block

brace_blocks := '{' blocks '}'
_start       := brace_block


Unmanaged :
- user_type declaration
- user_type definition
- pointer type
- function pointer
- parenthesis
- struct/unions
- else statement
- do-while/for/switch


Thought List :
- declaration
  - function
  - variable
  - user type
- literal
  - alpha
  - numeric
  # toKnow : literal is often use to initialize variables
  # s = "cat" <-< cat is literal
- statement
  - assignation
  - return
  - conditional
  - func_call
- expression  #this is a combination
  - operation  


