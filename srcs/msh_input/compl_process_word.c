/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_process_word.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 13:52:29 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 12:17:22 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"

static char	*get_closest_match(char *word, size_t max_len, t_list *matches)
{
	t_list	*match;
	char	*ref;
	char	*closest_match;

	closest_match = NULL;
	ref = (char *)matches->content;
	match = matches;
	while (match)
	{
		if (max_len > ft_str_nbrequ(ref, match->content))
			max_len = ft_str_nbrequ(ref, match->content);
		match = match->next;
	}
	if (max_len > ft_strlen(word) - 1)
		closest_match = ft_strndup(matches->content, max_len);
	else
		closest_match = ft_strndup(word, ft_strlen(word));
	return (closest_match);
}

/*
**	Get all possible matches and the closest match
*/

int			process_word(t_compl *compl)
{
	int		ret;

	ret = 1;
	compl->matches = get_matches(compl);
	if (compl->matches)
	{
		if (!compl->matches->next)
			compl->closest_match = ft_strdup(compl->matches->content);
		else if (compl->word)
			compl->closest_match = get_closest_match(compl->word,
				compl->max_match_len, compl->matches);
	}
	if (!compl->closest_match)
		return (1);
	if (ft_strlen(compl->closest_match) == compl->max_match_len)
		process_closest_match(&compl->closest_match, *compl);
	if (ft_strlen(compl->closest_match) > ft_strlen(compl->word))
		ret = 0;
	return (ret);
}