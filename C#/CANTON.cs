using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class CANTON
    {
        public static void Execute(string[] args)
        {
            var input = new List<int>();
            var testCases = Convert.ToInt32(Console.ReadLine());
            for (var k = 0; k < testCases; k++)
                input.Add(Convert.ToInt32(Console.ReadLine()));

            foreach (var term in input)
            {
                // know which row we are EXACTLY targeting
                // ROW1 = 1
                // ROW2 = 2..3  // TWO ELEMENTS
                // ROW3 = 4..6 // THREE ELEMENTS
                // ROW4 = 7..10 // FOUR ELEMENTS
                // ROW5 = 11..15 // FIVE ELEMENTS

                // 

                // So basically formula for X row is:
                // X_ROW_BEGINNING = (X-1) * X / 2 + 1
                // X_ROW_ENDING    = X_ROW_BEGINNING + X
                // (X-1) * X / 2 + 1 <= C <= (X-1) * X / 2 + 1 + X

                // TWO CONDITIONS
                // 1) (X-1) * X / 2 + 1 >= C 
                // 2) (X-1) * X / 2 + 1 + X <= C

                // calculate ROW.
                // (X^2 - X)/2 + (1 - C) = 0
                // 

                var ROW = (int)(1 + Math.Sqrt(8 * term - 7)) / 2;

                var denominator = ROW;
                var numerator = 1;
                if (ROW % 2 == 0)
                {
                    var swap = denominator;
                    denominator = numerator;
                    numerator = swap;
                }



                // find difference between these two elements!
                var beginning = (ROW - 1) * ROW / 2 + 1;
                var diff = term - beginning;

                if (ROW % 2 != 0)
                    diff *= -1;

                denominator += diff;
                numerator -= diff;


                Console.WriteLine("TERM {0} IS {1}/{2}", term, denominator, numerator);

            }
        }
    }
}