/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:07:59 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/22 11:29:11 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/* ************************************************************************** */
/*                                    ENUMS                                   */
/* ************************************************************************** */
typedef enum bools
{
	FALSE,
	TRUE
}						t_boolean;

typedef enum mess
{
	ERROR = 0,
	EMPTY = 0,
	ERROR_CREATING_A_BUFFER = -100000001,
	ERROR_INCORECT_INPUT_FORMAT = -100000010,
	NO_FLAGS = 11111110,
	FLAG_STORED = 11111101,
	OK = 11111111
}						t_messages;

typedef enum basess
{
	BASE_DEC_10 = 10,
	BASE_HEX_16 = 16,
}						t_s_base;

# define SIZE_BUFFER 4096
# define LL_SIZE 66
# define HEX "0123456789abcdef"
# define UHEX "0123456789ABCDEF"
# define DEC "0123456789"

/*
Why LL_SIZE = 66? Because I need to make sure I can store any adresses for the
pointer type. Adresse in a 64bits sytems can occupy up to 64 byte of memory.
So I needed 64 + 1(for an eventual sign) + 1 (for null terminating the buffer
usefull for my flush buffer implementation), so 66 bytes.
*/
/* ************************************************************************** */
/*                    STRUCT TO HOLD FORMATING CHARACTERISTICS                */
/* ************************************************************************** */
/*
	Why do I define the new type b_frmt? (b_format stands for "base format")

	It is a  struct type that I create to be able to hold all the
	characteristics that can be specified for the output string when 
	using the original/official printf function.
	The specification format in printf is the following:

	%[flags][width][.precision][length]specifier

	b_frmt will be organized as follow:

	struct				base_format
	{

	[flags] -> [+-' '0#]

	[width] -> [number]

	[.prescision] -> [.number]

	[specifier] -> For a list of all specifier available see table (specif*) 
	at the end of this file in the ANNEX section.
	}

	!!! [length] (also called sub-specifier) will not be implemented here.
	Just for my knowledge length can take the following values:
	-> [hh, h, l, ll, j, z, t, L]
*/
typedef struct base_format
{
	t_boolean			space;
	t_boolean			minus;
	t_boolean			plus;
	t_boolean			zero;
	t_boolean			dash;
	t_boolean			percent;
	int					width;
	int					precision;
	char				specifier;
	t_s_base			base;
	t_boolean			uppercase;
}						t_b_frmt;

/* ************************************************************************** */
/*             STRUCT TO HOLD FORMATING CHARACTERISTICS FOR NUMBERS           */
/* ************************************************************************** */
/*
 */
typedef struct temp_struct_num
{
	int					zero_pad;
	int					width_pad;
	int					s;
	int					m;
}						t_struc;

/* ************************************************************************** */
/*             STRUCT TO HOLD FORMATING CHARACTERISTICS FOR STRINGS           */
/* ************************************************************************** */
/*
 */
typedef struct temp_struct_s
{
	int					truncate;
	int					width_pad;
	int					s_len;
	int					s;
	int					arg_null;
}						t_st_s;

/* ************************************************************************** */
/*             STRUCT TO HOLD THE VALUE RETURNED WHEN CALLING VA_ARG          */
/* ************************************************************************** */
/*
 */
typedef struct arg_type_and_sign
{
	int					int_a;
	void				*void_a;
	char				*char_a;
	int					a_s;
}						t_r_va_arg;

/* ************************************************************************** */
/*             UNION TO HOLD ALL THE DATA USED FOR COMPUTATION                */
/* ************************************************************************** */
/*
	Reminder:
	Union in C are used for efficient memory usage, allowing differnt data 
	types to share the same memory space. THis is particularly useful in 
	scenarios where variables may represent different types of data at 
	different times, such as in low-level hardware access or when 
	implementing polymorphic structures. By enabling multiple interpretation
	of memory location, unions offer a versatile tool for memory 
	conservation and data representation in resouce-constrained environments
	or applications requiring direct manipulation of data representations.

	Why do I use a Union here?
	This will allow me to store and handle more easily the following
	specifiers:
	"pdiuxX".
*/
typedef union number_storage
{
	int					s_int;
	unsigned int		us_int;
	long long			s_ll;
	unsigned long long	us_ll;
}						t_un;

/* ************************************************************************** */
/*                STRUCT TO HOLD ALL THE DATA USED FOR COMPUTATION            */
/* ************************************************************************** */
/*
	Why do I define the new type t_c_data? (t_c_data stands for "computation 
	data")

	It is a  struct type that I create to be able to hold all the
	characteristics that can be specified for the output string when using
	the original/official printf function.
	The specification format in printf is the following:

	%[flags][width][.precision][length]specifier

	t_c_data will be organized as follow:

struct				base_format
{

	*s
	A pointer pointing to the begining of the string to be formated,
	so "str_tob_frmt"

	arg_pointer (argument pointer)
	A pointer pointing to the first argument contained in the object
	created as a result of executing "va_list" (will be incremented by
	"va_arg").

	r_value (returned value)
	The number of characters written to the specified output as a result
	of the execution of ft_printf

	ot_buffer (output buffer)
	A buffer created to store each computed peace of the string that is
	going to be printed to the specified output

	i_bufferr (index buffer)
	The current index (position) in the buffer

	str_format (string format)
	The format specified when calling ft_printf on the imput string.
	Computed via the parsing of the imput string.

	}

	!!! [length] (also called sub-specifier) will not be implemented here.
	Just for my knowledge length can take the following values:
	-> [hh, h, l, ll, j, z, t, L]

*/
typedef struct computation_data
{
	const char			*s;
	const char			*cp;
	va_list				arg_pointer;
	char				*ot_buffer;
	int					i_buffer;
	t_b_frmt			str_format;
	char				*format_substr;
	int					i_buf_substr;
	int					len_substr;
	int					r_value;
	t_un				uni;
	char				*format_abs;
	int					len_abs;
	t_r_va_arg			rva;
}						t_c_data;

/*

str_format is a struct used to store the formats specified in the input string.
(stores [flags][width][.precision][specifier]).

r_value is the value returned by the execution of ft_printf() which is the
number of characters printed to the screen.

uni is a union used when the input argument is of type "diuxXp" to store
the promoted argument.

ot_buffer is a buffer we fill with the characters we want to output to the
terminal based on the input format specification contained in the input string.
Each time we flush this buffer the character that where filling it are printed
on the terminal and and the buffer is freed for  new characters (it can happen
multiple times for one call to ft_printf).
(= stores final string to be printed)

format_substr is a buffer used to create and store the substring (store the 
result of formating the argument input), before placing it into ot_buffer.
(= stores formated substring)

format_abs is a buffer used to create and store the character representation
of the input argument when it is of type "diuxXp".
(= stores conversion of (int) or (void *) into (char *))
*/

/* ************************************************************************** */
/*                             FUNCTIONS PROTOTYPES                           */
/* ************************************************************************** */

/* ******************************  FLUSH_BUFFER  **************************** */

void				flush_ot_buffer(t_c_data *data);
void				empty_format_substr(t_c_data *data);
void				flush_format_substr_s(t_c_data *data, t_st_s *ts);
void				flush_format_substr_else(t_c_data *data, t_struc *ts);
void				flush_format_abs(t_c_data *data);

/* *************************  STRUCTURES INITIALIZATION  ******************** */

void				init_clean_format_struct(t_c_data *data);
int					init_data(t_c_data *data, const char *str_tob_frmt);
void				init_clean_format_num_struct(t_struc *ts);
void				init_clean_format_s_struct(t_st_s *ts);

/* ******************************  STORE FLAGS  ***************************** */

int					store_flag(t_c_data *data);

/* ******************************  STORE WIDTH  ***************************** */

int					store_width(t_c_data *data);

/* ****************************  STORE PRECISION  *************************** */

int					store_precision(t_c_data *data);

/* ****************************  STORE SPECIFIER  *************************** */

int					store_specifier(t_c_data *data);

/* ****************************  EXTRACT FORMAT  **************************** */

int					extract_format(t_c_data *data);

/* *********************  FORMATING FUNCTION FOR NUMBERS  ******************* */

int					prefix_plus_minus(t_c_data *data, t_struc *ts);
void				prefix_space(t_c_data *data, t_struc *ts);
void				prefix_ox(t_c_data *data, t_struc *ts);
void				pad_zero_precision(t_c_data *data, t_struc *ts);
void				pad_space_or_zero_width(t_c_data *data, t_struc *ts, int c);
void				abs_to_substr(t_c_data *data, t_struc *ts);

/* *********************  FORMATING FUNCTION FOR STRINGS  ******************* */

int					arg_null_and_precision_less_six(t_c_data *data, t_st_s *ts);
void				no_truncate(t_c_data *data, t_st_s *ts);
void				truncate_precision(t_c_data *data, t_st_s *ts);
void				pad_width(t_c_data *data, t_st_s *ts);

/* ****************************  SUBSTRING CREATION  ************************ */

int					compute_substring(t_c_data *data);
void				init_rva(t_c_data *data);
int					c_format(t_c_data *data);
void				s_format(t_c_data *data);
void				n_format(t_c_data *data);
void				mini_itoa(t_c_data *data, int u);
unsigned long long	get_output_type(t_c_data *data);
void				handle_all_n(t_c_data *data);
void				calculate_width_pad(t_c_data *data, t_struc *ts, int c);
void				h_precision_unsigned(t_c_data *data, t_struc *ts);
void				h_precision_signed(t_c_data *data, t_struc *ts);
void				h_width_unsigned(t_c_data *data, t_struc *ts);
void				h_width_signed(t_c_data *data, t_struc *ts);
void				h_only_flags_unsigned(t_c_data *data, t_struc *ts);
void				h_only_flags_signed(t_c_data *data, t_struc *ts);

/* ****************************  FILLING_OT_BUFFER  ************************* */

int					construct_ot_string(t_c_data *data);

/* ****************************  FT_PRINTF  ********************************* */

int					ft_printf(const char *str_tob_frmt, ...);

/* ************************************************************************** */
/*                                   ANNEX                                    */
/* ************************************************************************** */

/* ******************************  [specifiers]  **************************** */
/*
specif*	| Output                                      			| Example
--------|-------------------------------------------------------|---------
d or i  | Signed decimal integer                      			| 392
u       | Unsigned decimal integer                    			| 7235
o       | Unsigned octal                              			| 610
x       | Unsigned hexadecimal integer (lowercase)    			| 7fa
X       | Unsigned hexadecimal integer (uppercase)    			| 7FA
f       | Decimal floating point, lowercase           			| 392.65
F       | Decimal floating point, uppercase           			| 392.65
e       | Scientific notation (mantissa/exponent), lowercase 	| 3.9265e+2
E       | Scientific notation (mantissa/exponent), uppercase 	| 3.9265E+2
g       | Use the shortest representation: %e or %f   			| 392.65
G       | Use the shortest representation: %E or %F   			| 392.65
a       | Hexadecimal floating point, lowercase       			| 0xc.90fep-2
A       | Hexadecimal floating point, uppercase       			| 0XC.90FEP-2
c       | Character                                   			| a
s       | String of characters                        			| sample
p       | Pointer address                             			| b8000000
n       | Nothing printed.										|
		| The corresponding argument must be a pointer to a	|
		| signed int. The number of characters written so far	|
		| is stored in the pointed location.			|
%		| A % followed by another % character will write a	| %
		| single % to the stream. 								|
*/

/* ******************************  [flags]  ********************************* */
/*
flags   | description
--------|-------------------------------------------------------------------
-       | Left-justify within the given field width; Right justification is
	| the default (see width sub-specifier).
+       | Forces to precede the result with a plus or minus sign (+ or -)
	| even for positive numbers. By default, only negative numbers are
	| preceded with a - sign. (only for "dip")
(space) | If no sign is going to be written, a blank space is inserted before
	| the value.
#       | Used with o, x, or X specifiers the value is preceded with 0, 0x or
	| 0X respectively for values different than zero. Used with a, A, e,
	| E, f, F, g or G it forces the written output to contain a decimal
	| point even if no more digits follow. By default, if no digits
	| follow, no decimal point is written.
0       | Left-pads the number with zeroes (0) instead of spaces when padding
	| is specified (see width sub-specifier).
*/

/* ******************************  [width]  ********************************* */
/*
width   | description
--------|-------------------------------------------------------------
(number)| Minimum number of characters to be printed. If the value to be
		| printed is shorter than this number, the result is padded with
		| blank spaces. The value is not truncated even if the result is
		| larger.
*       | The width is not specified in the format string, but as an
		| additional integer value argument preceding the argument that
		| has to be formatted.
*/

/* ******************************  [.precision]  **************************** */
/*
.preci* | description
--------|---------------------------------------------------------
.number | For integer specifiers (d, i, o, u, x, X): precision
		| specifies the minimum number of digits to be written. If
		| the value to be written is shorter than this number, the
		| result is padded with leading zeros. The value is not
		| truncated even if the result is longer. A precision of 0
		| means that no character is written for the value 0.
		| For a, A, e, E, f and F specifiers: this is the number of
		| digits to be printed after the decimal point (by default,
		| this is 6).
		| For g and G specifiers: This is the maximum number of
		| significant digits to be printed.
		| For s: this is the maximum number of characters to be
		| printed. By default all characters are printed until the
		| ending null character is encountered.
		| If the period is specified without an explicit value for
		| precision, 0 is assumed.
.*      | The precision is not specified in the format string, but
		| as an additional integer value argument preceding the
		| argument that has to be formatted.
*/
#endif
