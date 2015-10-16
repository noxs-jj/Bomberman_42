/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:41:32 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/04 14:24:02 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 1
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct		s_delim
{
	size_t			i;
	size_t			j;
}					t_delim;

typedef struct		s_buff
{
	char			*buff;
	int				offst;
	int				fd;
	int				readret;
	struct s_buff   *next;
}					t_buff;

int					get_next_line(int const fd, char **line);
char				**ft_strsplit_whitespaces(char const *s);
char				**ft_strstrsplit(char const *s, char *c);
int					ft_lstfind(t_list **lst, t_list *elem);
int					ft_lstlen(t_list *list);
t_list				*ft_lstcpynew(void *content, size_t size);
void				ft_lstinsertsort(t_list **start,
						int (*cmp)(t_list *a, t_list *b), t_list *elem);
char				*ft_newstrchr(char *s, char c);
void				ft_freetab(char **tab, int len);
char				*ft_newstrc(char *s, char c);
float				ft_atof(char *str);
int					*ft_getoptions(char *alphabet, int *ac, char ***av);
int					ft_tabstrlen(char **yolo);
int					ft_nbrlenbase(long n, int base);
void				ft_putnbrbase(long n, char *alphabet, int a);
void				ft_unputnbrbase(unsigned long n, char *alphabet, int a);
void				ft_lstmove(t_list **a, t_list *b, t_list *c);
void				ft_lstinsert(t_list **a, t_list *b, t_list *c);
void				ft_lstsup(t_list **start, t_list *elem);
void				ft_lstsort(t_list **a, int (*cmp)(t_list *a, t_list *b));
void				ft_lstswap(t_list **a, t_list *b, t_list *c);
char				*ft_strbchr(char *str, char c);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_tabstrlen(char **tab);
char				*ft_strrev(char *str);
int					ft_dectobin(int n);
char				*ft_backchrfils(char *s1, char *s2, char c);
unsigned int		ft_abs(int n);
int					ft_bintodec(int n);
int					ft_pow(int n, int p);
char				*ft_strnchr(const char *str, int c, int n);
char				*ft_strerase(char *str, int n);
void				*ft_memalloc(size_t size);
void				ft_lstiter(t_list *lst, void (*f)(t_list*elem));
void				ft_memdel(void **ap);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
#endif
