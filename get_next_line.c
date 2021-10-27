/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:23:36 by jchopped          #+#    #+#             */
/*   Updated: 2021/10/27 14:22:37 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# define BUFFER_SIZE 1000000

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
	{
		l++;
	}
	return (l);
}

char	*ft_strdup( char *str)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = (char *) malloc ((len + 1) * sizeof(char));
	if ((void *) 0 == new_str)
		return ((void *)0);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!(s1 && s2))
		return ((void *) 0);
	size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1);
	new_s = (char *) malloc(size);
	if ((void *)0 == new_s)
		return ((void *)0);
	i = 0;
	j = 0;
	while (s1[i])
		new_s[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_s[j++] = s2[i++];
	new_s[j] = 0;
	return (new_s);
}

char	*ft_strchr( char *str, int ch)
{
	int	i;

	if(!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)(str + i));
	return ((void *)0);
}

void read_buff(int fd, char **str)
{
	int ret;
	char * temp;
	char buf[BUFFER_SIZE + 1];

	if(!*str || !ft_strchr(*str, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		while (ret > 0)
		{
			if (!*str)
			{
				*str  = ft_strdup("");
			}
			buf[ret] = 0;
			temp = *str;
			*str = ft_strjoin(*str, buf);
			free(temp);
			if(!ft_strchr(*str, '\n'))
				ret = read(fd, buf, BUFFER_SIZE);
			else 
				ret = 0;
		}
	}
}

char *trim_bef(char *res, char *in_str)
{
	int	i;
	int len;
	
	i = 0;
	len = 0;
	while(in_str[len] != '\n')
			len++;
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == res)
		return NULL;
	while (i < len)
	{
		res[i] = in_str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char *str_proc(char **in_str)		
{
	char *res;
	char *new_in_str;

	res = NULL;
	new_in_str = *in_str;
	if (ft_strchr(new_in_str, '\n'))
	{
		res = trim_bef(res, new_in_str);
		*in_str = ft_strdup(ft_strchr(new_in_str, '\n') + 1);
		free(new_in_str);
	}
	else
	{
		res = ft_strdup(*in_str);
		free(*in_str);
		*in_str = NULL;
	}
	return (res);
}


char *get_next_line(int fd)
{
	static char	*in_str;
	char *buf;

	if(!in_str)
		in_str = NULL;
	buf = NULL;
	if(-1 == fd || -1 == read(fd, buf, 0))
		return (NULL);
	read_buff(fd, &in_str);
	if(NULL == in_str || (in_str && !in_str[0]))
		return (NULL);
	return (str_proc(&in_str));
}

int main (void)
{
	int	fd;
	int i;

	fd = open("big_line_with_nl", O_RDONLY);
	if(fd)
	{
		printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd));
		// putchar(c);
	}
	else 
		printf("ERROR\n");
	return (0);
}