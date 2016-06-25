/*
** my_pass.c for my_pass.c in /home/huiban_t/pool_ratp/projTester
**
** Made by Théo HUIBAN
** Login   <huiban_t@epitech.net>
**
** Started on  Wed Jun 22 15:44:22 2016 Théo HUIBAN
** Last update Sat Jun 25 13:45:35 2016 HUIBAN Theo
*/

#include "proj.h"

int		taille(char *str)
{
  int		i;
  int		len;

  i = 0;
  len = 0;
  while (str[i] != '\0')
    {
      if (str[i] == ':'  && str[i + 1] != '\0')
	len++;
      i++;
    }
  return (len + 1);
}

char		**path_to_tab(char *str)
{
  char		**stt;
  int		i;
  int		tail;

  tail = taille(str);
  i = 0;
  if ((stt = malloc((tail + 1) * sizeof(*stt))) == NULL)
    exit(84);
  stt[tail] = NULL;
  while (i < tail && *str != '\0')
    {
      while (*str == ' ' || *str == '\t')
	str++;
      stt[i] = str;
      i++;
      if (i == tail)
	break;
      while (*str != ':' && *str != '\0')
	str++;
      *str = '\0';
      str++;
      while (*str == ':' && *str != '\0')
	str++;
    }
  return (stt);
}

char		**my_getpath()
{
  char		*str;
  char		**my_path;
  int		i;

  i = 0;
  if ((str = getenv("PATH")) == NULL)
    exit(84);
  my_path = path_to_tab(my_strdup(str));
  while (my_path[i] != NULL)
    {
      my_path[i] = my_strcat("/", my_strdup(my_path[i]));
      i++;
    }
  return (my_path);
}

char		*my_access(char *str, char **path)
{
  t_path	pt;

  pt.stt = "\0";
  pt.i = 0;
  pt.fok = 0;
  if ((pt.fok = access(str, F_OK)) == 0  && access(str, X_OK) == 0)
    {
      if (my_strncmp("./", str, 2) == 0)
	return (str);
      else
	{
	  pt.stt = my_strdup("./");
	  return (my_strcat(str, pt.stt));
	}
    }
  else
    if ((pt.fok = access(str, X_OK)) != 0)
      {
	while (path[pt.i] != NULL &&
	       (pt.fok = access(my_strcat(str, path[pt.i]), F_OK)) != 0)
	  pt.i++;
	if (pt.fok == 0 && access(my_strcat(str, path[pt.i]), X_OK) == 0)
	  return (my_strcat(str, path[pt.i]));
      }
  return (NULL);
}

char		*my_pass(char *str)
{
  char		**path;
  char		*access;

  path = my_getpath();
  access = my_access(str, path);
  if (access == NULL)
    {
      my_dprintf(2, "Bad file\n");
      exit(84);
    }
  free(path);
  return (access);
}
