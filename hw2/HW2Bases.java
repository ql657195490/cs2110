/**
 * CS 2110 Fall 2015 HW2
 * Part 1 - Coding with bases
 *
 * @author HONGRUI ZHENG
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 *     String.equals()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   strdtoi.
 * - You may declare exactly one String variable each in itostrb, and itostrx.
 */
public class HW2Bases
{
	/**
	 * strdtoi - Decimal String to int
	 *
	 * Convert a string containing ASCII characters (in decimal) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid decimal numbers, and able to fit in a 32-bit signed integer.
	 *
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal)
	{
		int result = 0;
		int power = 10;
		for (int i = decimal.length() - 1; i >= 0; i--) {
			if (i == decimal.length() - 1) {
				result += ((int) decimal.charAt(i) - 48);
			} else {
				result += ((int) decimal.charAt(i) - 48) * power;
				power *= 10;
			}
		}
		return result;
	}

	/**
	 * strbtoi - Binary String to int
	 *
	 * Convert a string containing ASCII characters (in binary) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid binary numbers, and able to fit in a 32-bit signed integer.
	 *
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary)
	{
		int result = 0;
		int power = 0;
		for (int i = binary.length() - 1; i >= 0; i--) {
			result += ((int) binary.charAt(i) - 48) << power;
			power++;
		}
		return result;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 *
	 * Convert a string containing ASCII characters (in hex) to an int.
	 * The input string will only contain numbers and uppercase letters A-F.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 *
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex)
	{
		int result = 0;
		int power = 0;
		for (int i = hex.length() - 1; i >= 0; i--) {
			int character = (int) hex.charAt(i);
			if (character >= 65) {
				result += (character - 55) << power;
			} else {
				result += (character - 48) << power;
			}
			power += 4;
		}
		return result;
	}

	/**
	 * itostrb - int to Binary String
	 *
	 * Convert a int into a String containing ASCII characters (in binary).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 *
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary)
	{
		String result = "";
		if (binary == 0) {
			return "0";
		}
		while (binary > 0) {
			int remainder = binary & 1;
			result = remainder + result;
			binary = binary >> 1;
		}
		return result;
	}


	/**
	 * itostrx - int to Hexadecimal String
	 *
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * The output string should only contain numbers and uppercase letters A-F.
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 *
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex)
	{
		int rem;
		String result = "";
		char hexlib[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		if (hex == 0) {
			return "0";
		}
		while (hex > 0) {
			rem = hex & 15;
			result = hexlib[rem] + result;
			hex = hex >> 4;
		}
		return result;
	}
}

