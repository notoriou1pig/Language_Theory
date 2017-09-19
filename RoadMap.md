15/02/2016 : Start writing basic C grammar.
	     It should cover main concept of C programming such as:
       	     - declaration
               - function
	       - variable
	     - literal
	       - alpha
	       - numeric
	       toKnow : literal is often use to initialize variables
	       s = "cat" <-< cat is literal
	     - statement
	     - expression
	       this is a combination (like operations =P)

	         - assignation
	     - user types
	     - macros
	     - conditionals
	     - 
	     Question on 'expression' ... What does it stand for !?
	     Reflection around LR and LL. Why not building LR parser.
	     (Maybe another project ...)
	     
Statements are executed
Expressions are evaluated

28/07/2016
Common Data :
=============

Tokenizer :
===========
Data :



Functions :

- Init
Initialise the tokenizer with an fd.
Generate a tokenizer structure.
```
stream	init_tokenize(int fd)


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

