using System;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class PRIME1
    {
        public static void Execute(string[] args)
        {
            var testCases = Convert.ToInt32(Console.ReadLine());
            var input = new List<KeyValuePair<int, int>>(testCases);

            // read testCases from INPUT.
            for (var i = 0; i < testCases; i++)
            {
                var line = Console.ReadLine();
                var numbers = line.Split(' ');

                var firstNumber = Convert.ToInt32(numbers[0]);
                var secondNumber = Convert.ToInt32(numbers[1]);

                input.Add(new KeyValuePair<int, int>(firstNumber, secondNumber));
            }


            // emit OUTPUT.
            var testCaseIndex = 0;
            foreach (var testCase in input)
            {
                var m = testCase.Key;
                var n = testCase.Value;

                // create new primeNumbers array
                // and assume that all numbers are PRIMES.
                var primeNumbers = new bool[n - m + 1];
                for (var v = 0; v < primeNumbers.Length; v++)
                    primeNumbers[v] = true;


                var x = 2;
                var maxVal = (n - m)/2 + m;

                var c = 0;
                while (true)
                {
                    var y = (int) Math.Ceiling(m/(double) x)*x + x*c;
                    if (y - m >= primeNumbers.Length)
                    {
                        if (c == 0)
                            break;

                        c = 0;
                        x++;
                        continue;
                    }

                    // mark it as not prime number.

                    if (y != x)
                        primeNumbers[y - m] = false;

                    c++;
                }

                for (var v = 0; v < primeNumbers.Length; v++)
                {
                    if (primeNumbers[v])
                    {
                        var prime = m + v;
                        if (prime == 1)
                            continue;

                        Console.WriteLine(prime);
                    }
                }

                // no need to print WriteLine() when we have latest case
                // I don't think SPOJ should restrict this, but precautions!
                if (testCaseIndex < input.Count - 1)
                    Console.WriteLine();

                testCaseIndex++;
            }
        }
    }
}