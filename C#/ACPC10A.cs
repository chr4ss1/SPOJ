using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class ACPC10A
    {
        public static void Execute(string[] args)
        {
            var input = new List<List<int>>();

            // read testCases from INPUT.
            while (true)
            {
                var line1 = Console.ReadLine();
                var sequence = line1.Split(' ');

                var seq = sequence.Select(n => Convert.ToInt32(n)).ToList();

                var allZero = true;
                foreach (var number in seq)
                    if (number != 0)
                        allZero = false;

                if (allZero)
                    break;

                input.Add(seq);
            }


            // emit OUTPUT.
            var testCaseIndex = 0;
            foreach (var testCase in input)
            {
                var sequence = testCase;

                // test if AP
                var diff = sequence[1] - sequence[0];
                var secondDiff = sequence[2] - sequence[1];

                if (diff == secondDiff)
                {
                    // AP
                    Console.WriteLine("AP " + (sequence[2] + diff));
                }
                else
                {
                    var diffFactor = sequence[1] / sequence[0];
                    Console.WriteLine("GP " + sequence[2] * diffFactor);
                }
            }
        }
    }
}