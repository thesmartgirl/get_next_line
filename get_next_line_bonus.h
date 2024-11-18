/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:27:49 by ataan             #+#    #+#             */
/*   Updated: 2024/11/12 17:50:13 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

char			*get_next_line(int fd);
int				ft_strlen(char *str);
char	    *ft_strchr(const char *s, int c);
char			*ft_strdup(char *original);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *str, int start, int max);

#endif
