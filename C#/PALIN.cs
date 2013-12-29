using System;
using System.Text;

namespace PALIN
{
    static internal class Program
    {
        public static string FullReverse(this string str)
        {
            var bytes = str.ToCharArray();
            Array.Reverse(bytes);
            return new string(bytes);
        }

        public static string IncrementByOne(this string str)
        {
            var strBuilder = new StringBuilder(str);
            for (var k = str.Length - 1; k >= 0; k--)
            {
                if (strBuilder[k] != '9')
                {
                    strBuilder[k]++;
                    return strBuilder.ToString();
                }

                // carry it over.
                strBuilder[k] = '0';
                if (k == 0)
                    return string.Concat('1', strBuilder.ToString());
            }

            throw new Exception("InvalidOperationException");
        }

        public static string FindPalindrome(string input)
        {
            var current = input.IncrementByOne();
            if (current == current.FullReverse())
                return current;

            var oddCase = current.Length%2 != 0;
            var length = current.Length;

            var includeSecondPart = oddCase;

            var halfLength = length/2;

            var firstPart = current.Substring(0, halfLength);
            var secondPart = current.Substring(halfLength, 1);
            if (!includeSecondPart)
                secondPart = string.Empty;

            var thirdPart = current.Substring(halfLength + (includeSecondPart ? 1 : 0), halfLength);

            var firstPartReversed = firstPart.FullReverse();
            var incrementNeeded = true;

            for (var j = 0; j < firstPartReversed.Length; j++)
            {
                if (firstPartReversed[j] > thirdPart[j])
                {
                    incrementNeeded = false;
                    break;
                }

                if (firstPartReversed[j] < thirdPart[j])
                    break;
            }

            if (incrementNeeded)
            {
                firstPart = string.Concat(firstPart, secondPart).IncrementByOne();

                if (includeSecondPart)
                {
                    firstPartReversed = firstPart.FullReverse().Substring(1, firstPart.Length - 1);
                    secondPart = string.Empty;
                }
                else
                {
                    firstPartReversed = firstPart.FullReverse();
                }
            }

            return string.Concat(firstPart, secondPart, firstPartReversed);
        }


        static void Main()
        {
            var tests = Convert.ToInt32(Console.ReadLine());
            while (tests-- > 0)
                Console.WriteLine(FindPalindrome(Console.ReadLine()));
        }
    }
}
