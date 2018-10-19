/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_hex.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/18 19:01:56 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/20 14:56:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	print_hex(unsigned int n)
{
	char *hexa;

	hexa = ft_strdup("0123456789abcdef");
	if (n >= 16)
		print_hex(n / 16);
	ft_putchar(hexa[n % 16]);
	free(hexa);
}
