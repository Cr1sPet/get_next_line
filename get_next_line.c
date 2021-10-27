/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:23:36 by jchopped          #+#    #+#             */
/*   Updated: 2021/10/26 12:03:16 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# define BUFFER_SIZE 100000

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

	while (!ft_strchr(buf, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret)
		{
			temp = *str;
			*str = ft_strjoin(*str, buf);
			free(temp);
		}
	}
}

char *trim_bef(char **res, char *in_str, int len)
{
	int	i;
	char *temp_res;
	
	i = 0;
	temp_res = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == temp_res)
		return NULL;
	while (i < len)
	{
		temp_res[i] = in_str[i];
		i++;
	}
	temp_res[i] = 0;
	*res = temp_res;
	printf("%s - res after filling\n", *res);
	free(temp_res);
	len = ft_strlen(ft_strchr(in_str, '\n') + 1);
	in_str = ft_strdup(ft_strchr(in_str, '\n') + 1);
	return (in_str);
}

char *str_proc(char **in_str)		
{
	char *res;
	int len;
	char *temp;
	char *new_in_str;
	
	len = 0;
	new_in_str = *in_str;
	if (ft_strchr(new_in_str, '\n'))
	{
		while(new_in_str[len] != '\n')
			len++;
		len++;
		temp = new_in_str;
		new_in_str = trim_bef(&res, new_in_str, len);
		free(temp);
		*in_str = new_in_str;
		free(new_in_str);
	}
	else
	{
		res = ft_strdup(*in_str);
		free(*in_str);
	}
	printf("%s - res before returning\n", res);
	return (res);
}


char *get_next_line(int fd)
{
	static char	*in_str;

	if(!in_str)
		in_str = ft_strdup("");
	else
	{
		in_str = ft_strdup(in_str);
	}

	if(fd && !ft_strchr(in_str,'\n'))
		read_buff(fd, &in_str);
	//printf("%s\n", in_str);
	return (str_proc(&in_str));
}

int main (void)
{
	int	fd;
	int i;

	fd = open("fail2", O_RDONLY);
	if(fd)
	{
		 printf("%s", get_next_line(fd));
		
	}
	else 
		printf("ERROR\n");
	return (0);
}
