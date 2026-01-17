/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:50:28 by gfulconi          #+#    #+#             */
/*   Updated: 2025/03/11 15:15:23 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define PI 3.141592653589793
# define EPSILON 1e-7

// Calculates the term index of the Fibonnaci sequence
int			ft_fibonacci(int index);
// Calculates the power of an integer by another
int			ft_power(int nb, unsigned int power);
// Calculates the integer square root of an integer (-1 if it does not exist)
long		ft_sqrt(unsigned long nb);
// Calculates the factorial of an integer
int			ft_factorial(int nb);
// Checks if a number is prime
int			ft_is_prime(int nb);
// Returns the next prime number bigger than nb
int			ft_find_next_prime(int nb);
// Returns the absolute value of a number
int			ft_abs(int nb);
// Returns an array of integers containing successive numbers from min to max
int			*ft_range(int min, int max);

// Returns the smallest of two integers
int			ft_min(int a, int b);
// Returns the biggest of two integers
int			ft_max(int a, int b);
// Return the int value bound between min and max
int			ft_clamp(int value, int min, int max);
// Returns the smallest value inside an array of integers
int			ft_array_min(int *array, int size);
// Returns the biggest value inside an array of integers
int			ft_array_max(int *array, int size);

// Returns the absolute value of a double
double		ft_absf(double nb);
// Returns the smallest of two doubles
double		ft_minf(double a, double b);
// Returns the biggest of two doubles
double		ft_maxf(double a, double b);
// Returns the double value bound between min and max
double		ft_clampf(double value, double min, double max);
// Compare two doubles with an error margin
int			ft_equalf(double value1, double value2);
int			ft_supf(double value1, double value2);
int			ft_inff(double value1, double value2);
int			ft_in_range(int value, int min, int max);
int			ft_in_rangef(double value, double min, double max);

// Lerps between two doubles
double		ft_lerpf(double min, double max, double lambda);

// Returns the number of characters (sign and digits) of a signed number
// written is a specific base
int			signed_nbrlen_base(long long nb, int base_len);
// Returns the number of characters (digits) of an unsigned number written
// is a specific base
int			usigned_nbrlen_base(unsigned long long nb, int base_len);
// Returns the number of characters (digits sign and point) of a base ten
// double number
int			ft_doublelen(double nb, int precision);

// Converts a double to an integer by truncating its decimal part
long long	ft_truncate(double nb);
// Converts a double by rounding it to the closest integer
long long	ft_round(double nb);
// Calculates the power of a double by a signed integer
double		ft_powerf(double nb, int power);
// Returns the exponent of a double when written in scientific notation
int			ft_get_exponent(double nb);

// TODO
// Trigonomerty
// Operations on doubles
// PGCD and PPCM
// Statistics (mean, variance, median, binomial coeff, distributions)
// Numerical Integration
// Complex numbers

#endif
