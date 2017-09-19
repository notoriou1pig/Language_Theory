// No Header
// 02/03/2016 - 16:49:39

#include <string.h>

#define TRUE	1
#define FALSE	0

/*
** digit    := ['0' - '9']
**
*/
int	is_digit(char c)
{
  if (c >= '0' && '9' >= c)
    return (TRUE);
  return (FALSE);
}

/*
** num      := num digit
**           | digit
**
** return the size of sub-num-string in str
*/
int	is_num(char *str)
{
  if (is_digit(str[0]) == TRUE)
    return (1 + is_num(str+1));
  return (FALSE);
}

/*
** charac    := ['a' - 'z']
**	      | ['A' - 'Z']
*/
int	is_charac(char c)
{
  if ((c >= 'a' && 'z' >= c) ||
      (c >= 'A' && 'Z' >= c))
    return (TRUE);
  return (FALSE);
}

/*
** alpha    := alpha charac
**	     | charac
**
** return the size of alpha in str
*/
int	is_alpha(char *str)
{
  if (is_charac(str[0]) == TRUE)
    return (1 + is_alpha(str+1));
  return (FALSE);
}

/*
** alphanum := alpha
**  	     | num
*/
int	is_alphanum(char *str)
{
  int	size;

  if ((size = is_alpha(str)) > 0 ||
      (size = is_num(str)) > 0)
    return (size);
  return (FALSE);
}

/*
** alphanumeric:= alphanumeric alphanum
**  	        | alphanum
*/
int	is_alphanumeric(char *str)
{
  int	size;

  if ((size = is_alphanum(str)) > 0)
    return (size + is_alphanumeric(str+size));
  return (FALSE);  
}

/* Terminal entry (in a sense)
** id	    := alpha alphanumeric
**	     | alpha
*/
int	is_id(char *str)
{
  int	size;
  int	size2;
  if ((size = is_alpha(str)) > 0 && (size2 = is_alphanumeric(str + size)) > 0)
    return (size + size2);
  return (size);
}

int	main(int argc, char **argv)
{
  char	*input_stream;

  input_stream = strdup("int a;");

  return (is_id("ABC123AbCbD155sd15sd15sd"));
}
