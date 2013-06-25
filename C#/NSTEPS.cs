using System;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class NSTEPS
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

                var x = Convert.ToInt32(numbers[0]);
                var y = Convert.ToInt32(numbers[1]);

                input.Add(new KeyValuePair<int, int>(x, y));
            }

            //1(1,1)
            //2(2,0)
            //3(3,1)
            //4(2,2)
            //5(3,3)
            //6(4,2)



            // emit OUTPUT.
            var testCaseIndex = 0;
            foreach (var testCase in input)
            {
                var x = testCase.Key;
                var y = testCase.Value;

                // calculate now what is there.

                // first line is basically  y=x
                // second line is basically y=x-2

                if (x == y || y == x - 2)
                {
                    // first line
                    Console.WriteLine(x + y - (x % 2 == 0 ? 0 : 1));
                }
                else
                {
                    Console.WriteLine("No Number");
                }
            }
        }
    }
}