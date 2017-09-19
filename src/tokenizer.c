// No Header
// 03/02/2017 - 16:44:45

#include <string.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

#define EXIT_MALLOC -100

typedef enum	
  {
    IDENTIFIER,
    LITERAL,		// numeric || quoted_string || quoted_char
    COMPARAISON,	// '==' | '!=' | '>' | '<' | '>=' | '<='
    OPERATOR,		// '+' | '-' | '*' | '/' | '%'
    ASSIGN,		// '='
    IF,			// 'if'
    ELSE,		// 'else'
    WHILE,		// 'while'
    PARENT_L,		// '('
    PARENT_R,		// ')'
    CBRACE_L,		// '{'
    CBRACE_R,		// '}'
    SBRACE_L,		// '['
    SBRACE_R,		// ']'
    DOT_COMA,		// ';'
    NOT_DEFINED
  }	token_cat;

typedef	struct	s_token
{
  void		*lexem;
  token_cat	token_type;
}		t_token;

typedef	struct		s_tok_list
{
  t_token		token;
  struct s_tok_list	*prev;
  struct s_tok_list	*next;  
}			t_token_list;

int	is_not_separator(char x)
{
  if (x == ' ' || x == 0)
    return (FALSE);
  return (TRUE);
}

t_token	*generate_token(char *stream, int start_pos, int size)
{
  t_token	*token;

  token = xmalloc(sizeof(*token));
  token->lexem = xmalloc(size);
  token->lexem = memcpy(token->lexem, &(stream[start_pos]), size);
  //  token->token_type;
  return (token);
}

int	tok_scanner(char *stream)
{
  t_token_list	*token_list;
  int		start;
  int		current;
  t_token	*token;
  
  start = 0;
  if (stream == NULL)
    return (FALSE);
  while (stream[start] != 0)
    {
      current = 0;
      while (is_not_separator(stream[start + current]))
	current++;
      if (current != 0)
	{
	  token = generate_token(stream, start, current);
	  write(1, token->lexem, strlen(token->lexem));
	  write(1, "\n", 1);
	}
      start = start + ((current != 0) ? current : 1);
    }
  return (TRUE);
}

int	main()
{
  char	*str;

  if ((str = strdup("a = 1;")) == NULL)
    exit(0);
  tok_scanner(str);
  if ((str = strdup("a=1;")) == NULL)
    exit(0);
  tok_scanner(str);
  return (0);
}
