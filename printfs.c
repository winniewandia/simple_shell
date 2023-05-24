#include "shell.h"

/**
 * stderror_printf - prints formatted output to stderr
 * @stream: File descriptor
 * @str: String to be read
 *
 * Return: No of chars read
 */

int stderror_printf(FILE *stream, const char *str)
{
	int count = 0;

	if (stream == NULL || str == NULL)
	{
		return (-1);
	}
	while (*str != '\0')
	{
		if (write(fileno(stream), str, 1) == -1)
		{
			return (-1);
		}
		count++;
		str++;
	}
	return (count);
}

/**
 * my_printf - prints chars to stdout
 * @format: Format specifiers
 */
void my_printf(const char *format, ...)
{
	va_list args;
	const char *prog_name, *arg, *str;

	va_start(args, format);
	prog_name = va_arg(args, const char*);
	arg = va_arg(args, const char*);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				str = *prog_name ? prog_name : "(null)";
				while (*str != '\0')
				{
					_putchar(*str++);
				}
			}
			else if (*format == 's')
			{
				str = *arg ? arg : "(null)";
				while (*str != '\0')
				{
					_putchar(*str++);
				}
			}
		}
		else
		{
			_putchar(*format);
		}
		format++;
	}
	va_end(args);
}

