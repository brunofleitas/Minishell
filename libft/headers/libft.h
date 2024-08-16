/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:43:44 by pcasagra          #+#    #+#             */
/*   Updated: 2024/08/04 15:49:38 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
/* ************************************************************************** */
/*                             EXTERNAL LIBRARY                               */
/* ************************************************************************** */
# include <stdlib.h>
# include <unistd.h>
/* ************************************************************************** */
/*                             STRUCT TYPE DEFS                               */
/* ************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************  GARBAGE COLLECTOR NODE  ************************ */
typedef struct s_ntc
{
	void			*data;
	size_t			size;
	struct s_ntc	*next;
	struct s_ntc	*prev;

}					t_ntc;
// ntc = node to clean

/* ************************************************************************** */
/*                                  CHECK                                     */
/* ************************************************************************** */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
/* ************************************************************************** */
/*                                  MEMORY                                    */
/* ************************************************************************** */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_calloc_g_c(size_t nmemb, size_t size, t_ntc **first_node);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
/* ************************************************************************** */
/*                             GARBAGE COLLEECTOR                             */
/* ************************************************************************** */
t_ntc		*g_c(t_ntc **first_node, size_t size_of);
t_ntc   	*find_ntc(t_ntc **first_node, void *data_ptr);
void		free_ntc_prior(t_ntc **first_node, void *data_ptr);
void		free_memory(t_ntc **first_node);
void    	*ft_realloc_g_c(t_ntc **first_node, void *existing_data,\
			size_t new_size);
/* ************************************************************************** */
/*                                 STRING                                     */
/* ************************************************************************** */
int			ft_atoi(const char *nptr);
char		*ft_itoa_g_c(int n, t_ntc **first_node);
char		**ft_split_g_c(char const *s, char c, t_ntc **first_node);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup_g_c(const char *s, t_ntc **first_node);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin_g_c(char const *s1, char const *s2, t_ntc **first_node);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi_g_c(char const *s, char (*f)(unsigned int, char), \
															t_ntc **first_node);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim_g_c(char const *s1, char const *set, t_ntc **first_node);
char		*ft_substr_g_c(char const *s, unsigned int start, size_t len, \
															t_ntc **first_node);
int			ft_tolower(int c);
int			ft_toupper(int c);
/* ************************************************************************** */
/*                                  PRINT                                     */
/* ************************************************************************** */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
/* ************************************************************************** */
/*                                   LIST                                     */
/* ************************************************************************** */
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
t_list		*ft_lstmap_g_c(t_list *lst, void *(*f)(void *), \
									void (*del)(void *), t_ntc **first_node);
void		ft_lstiter(t_list *lst, void (*f)(void *));
#endif
