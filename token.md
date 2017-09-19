struct	token
{
  enum token type;
  struct *lexem;
};

struct	lexem
{
  char	*value;
  int	size; //already compute
};
