// No Header
// 03/02/2017 - 16:44:48

void	*xmalloc(size_t size)
{
  void	*tmp;

  if ((tmp = malloc(size)) == NULL)
    exit(EXIT_MALLOC);
  return (tmp);
}
