/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_bang.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 13:55:36 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:39:02 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

int		bang_error(t_event event, int type)
{
	ft_putstr_fd("lsh: ", 2);
	if (type == EVENT_NOT_FOUND)
	{
		ft_putstr_fd(event.ev_designator, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("event not found", 2);
	}
	else if (type == BAD_WD_SPECIF)
	{
		ft_putstr_fd(event.wd_designator, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("bad word specifier", 2);
	}
	return (type);
}

int		is_bang_delimiter(char c)
{
	return (c == '(' || c == ' ' || c == '\t'
		|| c == EOF || c == '=' || c == '\n');
}

void	debug_event(t_event event)
{
	ft_putchar('\n');
	ft_printf("index = %d\n", event.index);
	ft_printf("needle = |%s|\n", event.needle);
	ft_printf("hist = |%s|\n", event.hist);
	if (event.wd_des & WD_DASH)
		ft_putendl("Range");
	if (event.wd_des & WD_WILDCARD)
		ft_putendl("Wildcard");
	ft_printf("wd_start = %d\n", event.wd_start);
	ft_printf("wd_end = %d\n", event.wd_end);
	ft_printf("wd_last = %d\n", event.wd_last_arg);
	ft_printf("expanded_hist = |%s|\n", event.expanded_event);
	ft_printf("ev = |%s|\n", event.ev_designator);
	ft_printf("wd = |%s|\n", event.wd_designator);
}

int		history_expansion(char **line, char **bang, char *ptr, t_shell *shell)
{
	t_event	event;
	size_t	hook;
	int		ret;

	init_event(&event);
	ptr++;
	parse_bang(&ptr, &event);
	ret = process_event(&event, *bang, shell);
	if (!ret)
	{
		ret = process_wd_des(&event, shell);
		if (!ret)
		{
			hook = ft_expand_str_part(line, *bang, (ptr - *bang) - 1,
					event.expanded_event);
			*bang = *line + hook;
		}
	}
	if (ret)
		bang_error(event, ret);
	clear_event(&event);
	return (ret);
}

/*
** Search and replace each <!> in the input stream by
** the history event associated.
*/

int		ft_expand_bang(char **line, t_shell *shell)
{
	char	*bang;
	char	*ptr;
	int		ret;

	ret = 0;
	bang = *line;
	while ((bang = ft_strchr(bang, '!')) && !ret)
	{
		ptr = bang;
		if (is_bang_delimiter(*(ptr + 1)))
		{
			bang += 2;
			continue ;
		}
		else
			ret = history_expansion(line, &bang, ptr, shell);
	}
	return (ret);
}