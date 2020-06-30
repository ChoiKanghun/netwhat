#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define DEB(x) write(1, x, strlen(x));
#define uint unsigned int
#define BUFFER_SIZE 100
typedef struct	s_bip{
	char		digit[35];
}				ip;
void	putstr(char *s);
void	putnbr(int i);
int		is_char_in(char c, char *set);
int		is_num(char c);
uint	bin_int(char *b);
uint	dec_int(char *d);
uint	str_uint(char *s);
void	uint_str(char *s, uint ui);
ip		uint_dec(uint ui);
uint	make_subnet_bit(uint ui);
uint	make_wildcard_bit(uint ui);
char	get_class(char *str);
void	info_cidr(char *s);
int		is_private(char *s);
char	**split(char *s, char *charset);
void	putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}
void	putnbr(int i)
{
	char	digit[13];
	uint_str(digit, i);
	putstr(digit);
}
char	*strjoin(char *s1, char *s2)
{
	char	*r;
	char	*rc;
	char	*sc;
	if (!(r = (char*)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
		return 0;
	rc = r;
	sc = s1;
	while (*s1)
		*rc++ =*s1++;
	while (*s2)
		*rc++ =*s2++;
	*rc = 0;
	free(sc);
	return r;
}
char	*readstr(void)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*s;
	char	*sc;
	char	*bc;
	int		read_chars;
	char	tmp[2];
	char	*tc;
	s = (char*)malloc(1);
	*s = 0;
	// while ((read_chars = read(1, buffer, BUFFER_SIZE)) > 0)
	// {
	// 	buffer[read_chars] = 0;
	// 	bc = buffer;
	// 	while (read(0, tmp, 1))
	// 	{
	// 		if (*tmp == 'q')
	// 			break;
	// 		else
	// 		{
	// 			putstr("[");
	// 			putstr(s);
	// 			putstr("]");
	// 			s = strjoin(s, buffer);
	// 		}
	// 	}
	// }
	// return s;
	while ((read_chars = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_chars] = 0;
		sc = s;
		s = strjoin(s, buffer);
	}
	return s;
}
int		is_char_in(char c, char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}
int		is_num(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}
uint	bin_int(char *b)
{
	uint	i = 0;
	while (*b && (*b == '0' || *b == '1'))
		i = i * 2 + (*b++ - '0');
	return (i);
}
uint	dec_int(char *d)
{
	uint	i = 0;
	while (*d && is_num(*d))
		i = i * 10 + (*d++ - '0');
	return (i);
}
uint	str_uint(char *s)
{
	int		is_bin = 0;
	uint	res = 0;
	char	*sc;
	sc = s;
	while (*sc && *sc != '.')
		sc++;
	if (sc - s == 8)
		is_bin = 1;
	if (is_bin == 1)
	{
		for (int i = 0 ; i < 32 ; i++)
		{
			if (*s == '.')
			{
				s++;
				continue ;
			}
			res <<= 1;
			res += *s++ - '0' ? 1: 0;
		}
	}
	else
	{
		while (is_char_in(*s, "0123456789."))
		{
			res <<= 8;
			res += dec_int(s);
			while ('0' <= *s && *s <= '9' && *s)
				s++;
			if (*s == '.')
				s++;
		}
	}
	return (res);
}
void	uint_str(char *s, uint ui)
{
	char	digit[13];
	char	*c;
	c = digit;
	*c++ = 0;
	*c++ = ui % 10 + '0';
	ui /= 10;
	while (ui)
	{
		*c++ = ui % 10 + '0';
		ui /= 10;
	}
	c--;
	while (*c)
		*s++ = *c--;
	*s = 0;
}
ip		uint_dec(uint ui)
{
	ip		d;
	int		tmp;
	char	digit[4];
	*(d.digit) = 0;
	for (int i = 0 ; i < 4 ; i++)
	{
		tmp = (ui >> (8 * (3 - i))) & 0xff;
		uint_str(digit, tmp);
		strcat(d.digit, digit);
		if (i != 3)
			strcat(d.digit, ".");
	}
	return (d);
}
uint	make_subnet_bit(uint ui)
{
	uint	res = 0xffffffff;
	if (ui == 32)
		return 0xffffffff;
	res >>= ui;
	res = ~res;
	return res;
}
uint	make_wildcard_bit(uint ui)
{
	uint	res = 0xffffffff;
	if (ui == 0)
		return 0xffffffff;
	ui = 32 - ui;
	res >>= ui;
	res = ~res;
	return res;
}
char	get_class(char *str)
{
	uint	ui = str_uint(str);
	uint	class;
	if (ui >> 31 == 0)
		class = 'A';
	else if (ui >> 30 == 2)
		class = 'B';
	else if (ui >> 29 == 6)
		class = 'C';
	else if (ui >> 28 == 14)
		class = 'D';
	else if (ui >> 27 == 30)
		class = 'E';
	return (char)class;
}
void	info_cidr(char *s)
{
	uint	ui = str_uint(s);
	uint	subnet;
	uint	wildcard;
	uint	network_id;
	uint	range_f;
	uint	range_l;
	uint	broadcast;
	while (*s && is_char_in(*s, "0123456789."))
	{
		s++;
	}
	if (*s == '/')
	{
		s++;
		subnet = make_subnet_bit(dec_int(s));
	}
	else
	{
		s++;
		subnet = str_uint(s);
	}
	wildcard = ~subnet;
	network_id = ui & subnet;
	broadcast = ui | wildcard;
	range_f = network_id + 1;
	range_l = broadcast - 1;
	printf("##########################################\n");
	printf("#------------------CIDR------------------#\n");
	printf("##########################################\n");
	printf("IP_address	: %s\n", uint_dec(ui).digit);
	printf("subnet_mask	: %s\n", uint_dec(subnet).digit);
	printf("wildcard_ma	: %s\n", uint_dec(wildcard).digit);
	printf("------------------------------------------\n");
	printf("network_id	: %s\n", uint_dec(network_id).digit);
	printf("broadcast	: %s\n", uint_dec(broadcast).digit);
	printf("------------------------------------------\n");
	printf("host_range	: %s\n", uint_dec(range_f).digit);
	printf("host_range	: %s\n", uint_dec(range_l).digit);
	printf("------------------------------------------\n");
	printf("num_of_host	: %u\n", range_l - range_f + 1);
}
int	is_private(char *s)
{
	uint	ip_address = str_uint(s);
	if (str_uint("10.0.0.0") <= ip_address && ip_address <= str_uint("10.255.255.255"))
	{
		printf("YES\n");
		return 1;
	}
	else if (str_uint("172.16.0.0") <= ip_address && ip_address <= str_uint("172.31.255.255"))
	{
		printf("YES\n");
		return 1;
	}
	else if (str_uint("192.168.0.0") <= ip_address && ip_address <= str_uint("192.168.255.255"))
	{
		printf("YES\n");
		return 1;
	}
	else
	{
		printf("NO\n");
		return 0;
	}
}
char	**split(char *s, char *charset)
{
	char	*sc;
	char	*sd;
	char	**r;
	char	**rc;
	int		n_strs = 0;
	if (!(r = (char**)malloc(sizeof(char*) * 20)))
		return (0);
	memset(r, 0xff, 20 * sizeof(char*));
	rc = r;
	rc[19] = 0;
	while (*rc)
	{
		if (!(*rc++ = (char*)malloc(sizeof(char) * 50)))
			return (0);
	}
	*rc = 0;
	rc = r;
	sc = s;
	while (*sc && is_char_in(*sc, charset))
	{
		sc++;
	}
	sd = *rc;
	while (*sc)
	{
		while (*sc && is_char_in(*sc, charset) == 0)
		{
			*sd++ = *sc++;
		}
		*sd = 0;
		rc++;
		while (*sc && is_char_in(*sc, charset))
		{
			sc++;
		}
		sd = *rc;
	}
	*rc = 0;
	return r;
}
int		main(int argc, char **argv)
{
	char	str[10000];
	char	*lstr;
	char	**ips;
	char	**ipsc;
	int		goahead = 1;
	uint	ip;
	putstr("##########################################\n");
	putstr("#----------------------------------------#\n");
	putstr("#--------------IP CALCULATOR-------------#\n");
	putstr("#----------------------------------------#\n");
	putstr("##########################################\n");
	putstr("p: private or not\n");
	putstr("m: how many hosts with the mask\n");
	putstr("ip: cidr info\n");
	putstr("\n");
	while (goahead)
	{
		memset(str, 0, sizeof(str));
		putstr("type option: ");
		scanf("%s", str);
		if (*str == 'p' || strcmp(str, "private\n") == 0)
		{
			putstr("##########################################\n");
			putstr("#-----------------PRIVATE----------------#\n");
			putstr("##########################################\n");
			putstr("ip: \n");
			scanf("%s", str);
			putstr("if you want to go back, press 'q'\n");
			if (*str == 'q' || *str == 27)
			{
				printf("back\n");
				continue ;
			}
			else
			{
				do
				{
					printf("%15s : ", str);
					is_private(str);
					scanf("%s", str);
				}
				while (*str != 'q' || *str == 27);
			}
		}
		else if (*str == 'm' || strcmp(str, "mask\n") == 0)
		{
			printf("##########################################\n");
			printf("#------------------MASK------------------#\n");
			printf("##########################################\n");
			printf("mask:");
			scanf("%s", str);
			ip = 0;
			ip = str_uint(str);
			printf("num of hosts: %u\n", ~ip - 1);
		}
		else if (*str == 'q' || *str == 27)
		{
			printf("##########################################\n");
			printf("#-----------------BYE BYE----------------#\n");
			printf("##########################################\n");
			printf("break\n");
			goahead = 0;
			break ;
		}
		else
		{
			info_cidr(str);
		}
		// free(str);
	}
	return (0);
}
		// 	- private		: 10.0.0.0 ~ 10.255.255.255
		// - B.	 128 ~ 191
		// 	- 구분 비트		 : 10(2비트)
		// 	- 네트워크 비트	 : 14 비트
		// 	- 호스트 비트	 : 16 비트
		// 	- private		: 172.16.0.0 ~ 172.31.255.255
		// - C.	 192 ~ 223
		// 	- 구분 비트		 : 110(3비트)
		// 	- 네트워크 비트	 : 21비트
		// 	- 호스트 비트	 : 8비트
		// 	- private		: 192.168.0.0 ~ 192.168.255.255
