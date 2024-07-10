/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:07:12 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:57:27 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                          STRUCTURES INITIALIZATION                         */
/* ************************************************************************** */
void	init_clean_format_struct(t_c_data *data)
{
	data->str_format.plus = FALSE;
	data->str_format.minus = FALSE;
	data->str_format.space = FALSE;
	data->str_format.zero = FALSE;
	data->str_format.dash = FALSE;
	data->str_format.width = EMPTY;
	data->str_format.precision = EMPTY - 1;
	data->str_format.specifier = EMPTY;
	data->str_format.base = BASE_DEC_10;
	data->str_format.uppercase = FALSE;
}
/*
We initiate str_format.precision at -1  because precision can be equal to 0.
*/

void	init_clean_format_num_struct(t_struc *ts)
{
	ts->s = 0;
	ts->m = 0;
	ts->width_pad = 0;
	ts->zero_pad = 0;
}

void	init_clean_format_s_struct(t_st_s *ts)
{
	ts->s = 0;
	ts->width_pad = 0;
	ts->truncate = 0;
	ts->s_len = 0;
	ts->arg_null = 0;
}

void	init_rva(t_c_data *data)
{
	data->rva.int_a = EMPTY;
	data->rva.void_a = NULL;
	data->rva.char_a = NULL;
	data->rva.a_s = EMPTY;
}

int	init_data(t_c_data *data, const char *str_tob_frmt)
{
	data->s = str_tob_frmt;
	data->cp = NULL;
	data->ot_buffer = (char *)ft_calloc(SIZE_BUFFER, sizeof(char));
	if (!(data->ot_buffer))
		return (ERROR);
	data->i_buffer = 0;
	data->format_substr = (char *)ft_calloc(SIZE_BUFFER, sizeof(char));
	if (!(data->format_substr))
		return (ERROR);
	data->format_abs = (char *)ft_calloc(LL_SIZE, sizeof(char));
	if (!(data->format_abs))
		return (ERROR);
	data->r_value = 0;
	data->len_abs = 0;
	init_rva(data);
	init_clean_format_struct(data);
	return (OK);
}
/*
See FUTHER EXPLENATIONS, to understand the choice of 4096 bytes for choice of
SIZE_BUFFER the size of ot_buffer (outpout buffer).
LL_SIZE == 65 because 64 bytes because on some system an adress (a pointer) can
take up to 64 bytes and I want one more for ensuring I have always a 0 in the
last bytes (this is required for my function flush_format_abs to work).
*/

/* ************************************************************************** */
/*                              FUTHER EXPLENATIONS                           */
/* ************************************************************************** */

/* ***************************  SIZE OF 4096 BYTES  ************************* */

/* The number 4096 bytes (or 4 KB) is a common size for memory pages in many
computer systems and is frequently used as a default buffer size for I/O
operations, including file and stream I/O in various programming languages and
libraries. This choice is not random; it is based on the architecture of modern
computer systems and operating systems.

Here's why 4096 bytes is a significant number:

Memory Page Size: Most modern computer architectures use a memory management
scheme that involves paging, where memory is divided into chunks of a fixed size
called pages. The size of a page can vary between systems, but 4 KB (4096 bytes)
is the most common page size on many platforms. By aligning buffer sizes with
the page size, systems can achieve more efficient memory usage and data transfer

Disk Sector and File System Block Size: Historically, disk sectors were 512
bytes, but many modern hard drives use a physical sector size of 4096 bytes.
Additionally, file systems often use a block size of 4096 bytes for similar
reasons of efficiency and alignment with hardware capabilities.

Performance Optimization: Using a buffer size that aligns with the system's
memory page size and the file system's block size can lead to performance
improvements. It reduces the number of read/write operations required to process
a given amount of data and minimizes the overhead associated with memory
management and disk I/O.

Standard Practice: Over time, the use of 4096 bytes as a default buffer size has
become a standard practice in many libraries and systems due to the reasons
mentioned above. It represents a balance between memory usage and performance
that works well for a wide range of applications.
*/
