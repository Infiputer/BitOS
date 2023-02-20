#pragma once
struct Point
{
    long X;
    long Y;
};
#define PI 3.141592653589793
#define TWO_PI 6.283185307179586
/*
 * Maps a value from one range to another.
 * @param x - the value to be mapped
 * @param in_min - the lower bound of the input range
 * @param in_max - the upper bound of the input range
 * @param out_min - the lower bound of the output range
 * @param out_max - the upper bound of the output range
 * @return the mapped value
 */
double mathmap(double x, double in_min, double in_max, double out_min, double out_max);

/*
 * Calculates the remainder of the division of two numbers.
 * @param x - the numerator
 * @param y - the denominator
 * @return the remainder
 */
double dmod(double x, double y);

/*
 * Rounds down a number to a multiple of a specified precision.
 * @param value - the value to be rounded
 * @param precision - the precision to round to
 * @return the rounded value
 */
double floor(double value, double precision);

/*
 * Rounds up a number to a multiple of a specified precision.
 * @param value - the value to be rounded
 * @param precision - the precision to round to
 * @return the rounded value
 */
double ceil(double value, double precision);

/*
 * Rounds a number to the nearest multiple of a specified precision.
 * @param value - the value to be rounded
 * @param precision - the precision to round to
 * @return the rounded value
 */
double round(double value, double precision);

/*
 * Linearly interpolates between two values based on a percentage.
 * @param a - the starting value
 * @param b - the ending value
 * @param percent - the percentage to interpolate
 * @return the interpolated value
 */
double percentLerp(double a, double b, double percent);

/*
 * Calculates the sine of an angle.
 * @param radians - the angle in radians
 * @return the sine value
 */
double sin(double radians);

/*
 * Calculates the cosine of an angle.
 * @param radians - the angle in radians
 * @return the cosine value
 */
double cos(double radians);
/**
 * Returns the minimum value between two values.
 *
 * @param a  The first value.
 * @param b  The second value.
 *
 * @return   The minimum value.
 */
double min(double a, double b);

/**
 * Returns the maximum value between two values.
 *
 * @param a  The first value.
 * @param b  The second value.
 *
 * @return   The maximum value.
 */
double max(double a, double b);

/**
 * Constrains a value between a minimum and maximum value.
 *
 * @param val      The value to constrain.
 * @param min_val  The minimum value.
 * @param max_val  The maximum value.
 *
 * @return         The constrained value.
 */
double constrain(double val, double min_val, double max_val);

/**
 * Linearly interpolates between two values with a constant rate.
 *
 * @param A    The starting value.
 * @param B    The ending value.
 * @param t    The interpolation rate.
 *
 * @return     The interpolated value.
 */
double constantlerp(double A, double B, double t);

/**
 * Returns the absolute value of a number.
 *
 * @param x   The input value.
 *
 * @return    The absolute value of the input.
 */
double abs(double x);

/**
 * Returns the square root of a number with a given epsilon value.
 *
 * @param x         The input value.
 * @param epsilon   The epsilon value.
 *
 * @return          The square root of the input.
 */
double sqrt(double x, double epsilon);

/**
 * Calculates the distance between two points in 2D space.
 *
 * @param x1   The x-coordinate of the first point.
 * @param y1   The y-coordinate of the first point.
 * @param x2   The x-coordinate of the second point.
 * @param y2   The y-coordinate of the second point.
 *
 * @return     The distance between the two points.
 */
double distance(double x1, double y1, double x2, double y2);
