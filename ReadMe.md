This is an attempt to create a self-hosting C compiler.  

The source code will be very simple because it have to compile itself.  
Every design chose have to be thought because of the self-hosting.  
For pedagogical reason, all step will be done as one binary.  

Going further :  
- Group every binary in one binary  
- Implementing code optimisation.  
- Inject machine code into binary for control flow analasys.  
  
First step : ast_builder  
Build a simple parser/lexer that handle itself.  
  
Second step : translater  
Build a simple translater into machine language  
  
First Reflexions :  
How to compile several files ?  
- ast_builder can generate one AST per file and save it :  
  .ast file (binary)  
  .ast_readable file (readable)  
- then load every file and groupe then into one big ast file but :  
  - remove multiple instance of included files.  
  - link function name and function call.  
  
  
15/02/2016  
################  
#### Data Structure  
########  
  
Abstract Data Type  
What should I first handle ?  
  
"  
	int main()  
	{  
		return (0);  
	}  
"  
C grammar :   
  
alpha	     := ['a' - 'z'] | ['A' - 'Z']    
string	     := string alpha |  
                alpha  
digit	     := ['0' - '9']  
number	     := number digit |  
                digit  
alphanum     := alphanum (number | alpha) |  
                (number | alpha)  
id	     := alphanum #simple  
  
comparaison  := pass #ie, not usable for now  
if           := ('if' parenthesis block 'else' block)  
		| 'if' parenthesis block  
conditional  := if   |  
		pass   #ie, not usable for now  
func_call    := id parenthesis #pass  
  
operations   := operations operation | operation  
operation    := stuff '+' stuff #pass  
  
var_name     := aplha #simple  
  
declaration  := c_type expression |  
		expression        |  
		keyword #do not know how to deal with it ...   
  
assignation  := var_name '=' expression #pass  
#after https://en.wikipedia.org/wiki/Statement_%28computer_science%29  
#this is a statement  
#comparaison | terminale when assignation  
#Level up on expression  
#divide it !		  
#almost everything   
stuff        :=	comparaision| #pass  
		func_call   | #toomuch  
		var_name    | #toomuch  
		num  
#garbage !! I quit !  
expression   := operations  | #??!!!  
#operations and assignation should work together.  
		stuff  
  
parenthesis  := '(' expression ')'  
keyword      := 'return' parenthesis  
statement    := block	    |  
		declaration |  
		assignation |  
		conditional | #pass  
		keywork #maybe catch it downer ...  
statements   := statements statement |  
	        statement  
block 	     := '{' statements '}'  
c_type	     := 'int' #see further with user types.  
func_decl    := c_type func_name parenthesis #see further again for decl  
function     := func_decl block  
declaration  := function |  
                variable  
_start 	     := declaration  
  
# We can notice the statements rule here : it think it define le LL parser  
# Doable via list I guess, what the best choice LR or LL ?  
# how to manager return !? What is the name ? keywords ?  
# Can see in parenthesis something wrong ... Don't know why ...  
  
# Can be declaration OR statement ?  
# else declaration is statement.  
# Both use expression !  
# Think scopes !  
  
  
## Check with `@tchoum'  
# declaration and expression are on the same layer  
# Write terminals  
# NPDA stack state machine  
# Elements Of The Theory Of Computation - Harry R. Levis / Christos H. Papadimitriou  
# |_> Book  
  
# TODO :  
# define terminal symbol and keep them in terminal state section  
  
## SymTable :#  
 - LEXER populate the symtable  
 - PARSER update the symtable  
  
16/02/2015  
  
I wrote earlier grammar.md a most elaborate part of the previous note.  
Maybe start with the `very' simple following :  
```  
int a;  
```  
  
grammar representation :  
  
digit	    := ['0' - '9']  
num         := num digit  
	     | digit  
charac	    := ['a' - 'z']  
	     | ['A' - 'Z']  
alpha	    := alpha charac  
	     | charac  
alphanum    := alpha  
	     | num  
alphanumeric:= alphanumeric alphanum  
	     | alphanum  
id	    := alpha alphanumeric  
	     | alpha  
type	    := 'int'  
declaration := type id  
start 	    := declaration  
  
`type' and `declaration' are incomplete, but I think id is complete.  
  
17/02/2015 to 18/02/2015  
  
I'm stuck ... Should I continue to parse it or should I developp a lexer now ?  
I wrote is funcs. They can recognise all previous rules.  
But only somes are function entry.  
  
'''  
int	is_id(char *str);  
int	is_alpha(char *str);  
int	is_num(char *str);  
  
'''  
  
specifier   := c_type  
	     | user_type  
argument    := specifier id  
arguments   := arguments ',' argument  
	     | argument  
block params:= '(' arguments ')' block  
declaration := specifier id block_params  
	     | specifier id  
statement   := declaration  
statements  := statements statement  
	     | statement  
block	    := '{' statements '}'  
_start      := block  
  
Should I execute a function call or should I evaluate it ?  
e.g. A function call is a expression or a statement ?  
I think it's a statement, cause of prolog and epilog.  
It's a stack move so execute it !  
  
I have to dig into my HDD, I may find some crapy old work.  
  
Is the following piece of code a declaration or a definition ?  
```  
struct   prob {  
  int    field;  
};  
```  
It look like a definition, but the following C code is legit :  
```  
struct   prob {  
  int    field;  
}        var;  
var = wathever();  
```  
This one is obviously a declaration cause the variable `var' is declare.  
So the first piece of code is a definition and where should I handle them !?  
  
  
user_block  := user_block specifier id  
	     | specifier id  
union_def   := 'union' user_block  
struct_def  := 'struct' user_block  
param       := specifier id  
params      := params ',' parame  
	     | param  
func_proto  := specifier id '(' params ')'  
definition  := func_proto  
	     | struct_def  
	     | union_def  
  
23/02/2016  
  
Statement from wikipedia :  
https://en.wikipedia.org/wiki/Statement_%28computer_science%29#Kinds_of_statements  
  
#Lenient statements  
    assignment:  
	A = A + 5  
    goto:  
	goto next;  
    return:  
	return 5;  
    call:  
	CLEARSCREEN()  
  
#Compound statements  
  
    block:  
	begin integer NUMBER; WRITE('Number? '); READLN(NUMBER); A:= A*NUMBER end  
    do-loop:  
	do { computation(&i); } while (i < 10);  
    for-loop:  
	for A:=1 to 10 do WRITELN(A) end  
    if-statement:  
	if A > 3 then WRITELN(A) else WRITELN("NOT YET"); end  
    switch-statement:  
	switch (c) { case 'a': alert(); break; case 'q': quit(); break; }  
    while-loop:  
	while NOT EOF DO begin READLN end  
  
  
After wikipedia, a call is a statement. So a function call is a statement.  
But, I know we can pass a function call as argument in a function call.  
And for me an argument is an expression. Definitly, it can't be a statment.  
We can't pass a block or an if-statement for example.  
Then, a function call might be an expression instead of being a statement.  
  
Thus, wikipedia help us writing the following definition of statement :  
  
  
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
  
I also rewrite the grammar.md.   


02/03/2016
I Have to write a tokenizer.
This tokenizer will have to :
- Init
Initialise the tokenizer with an input stream

- Send_Next_Token
Call by the parser to get the next token of the stream

- Save_Context
Call by the parser to save the context.
It mean the current position of the cursor on the stream

- Resore_Context
Call by the parser to restore the context.
It mean the old position of the cursor on the stream

- Consume
Call by the parser to release memory when enough token are accepted.
Release a part of the stream.

The tokenizer will read an input stream and segment it into token.
A token is a structure which represent a lexeme and the category of the token.
A token category is one rule of the grammar.
A lexeme stand for a `word' in the stream.

The tokenizer contain a cursor usefull to travel into the stream.
Also, it will be used for the context.

27/07/2016
Tokenizer :
===========
- Creation of a token chained list 
Save_context save the current pointer of the chained list.
When the parser ask for consume, every node before the current node are freed
and the context is renew.
The tokenizer will create X token (defined by a macro) and for every `consume`
call, it will generate enough token to fill the chained list.

/!\ How to define and extract a token ?
A token is defined by those rules :
- ""
- spaces
- and the following are tokens : ':' '{' and so on.

28/07/2016
Try to write tokenizer documentation and ask :
How to define a stream ?
eg. (13/10/2016) Already wrote the circular_buffer.

struct	tokenizer
{
  struct stream  stream;
  struct token	 input_token;	//token list to send
  struct token	 output_token;	//token sent to parser (release_token)
  void		 *context;	//current context
  void		 *saved_context	//context stack
}

struct	stream
{
  int	fd;			//file fd
  cirular_buffer	buff;	//circular buffer to handle huge files
}

13/10/2016
Start writing the token structure it must contain token type and lexem
Wrote lexem structure;
(Wiki : https://en.wikipedia.org/wiki/Lexical_analysis#Tokenization)
Tokenizer in two stages : Scanner and Evaluator
Scanner build lexem and send it to Evaluator
Evaluator build token by getting lexem type.
Evaluator job have to be clearer.

17/10/2016
Ask LSE about lexer.
Lexer produce token based on grammar terminal. Identifier will be given for
every non-keyword lexem.
Types have to be detected at this stage.
Those token will be improve after, during the parsing stage.

Casts rule :
CAST ::= '(' TYPE ')'

20/10/2016
Lexical Analyser : Produce Token with lexem set at obvious values
Syntaxical Analyser : Increase

## TODO :  
- do-loop  
- for-loop  
- switch-stmt  
  
/!\ Think about it !  
- Parenthesis Handling  
- Type Handling  
  - Function Pointer  
  - User Type (such as struct or union)  
    - Incomplete Type Implementation  
- Bit Field  
 
  
  /\  ||  
  \/  ||     Talk about It:  
|        _   - a definition is a statement ?  
\________/   - what is a func call ?  
