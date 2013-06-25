using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class FASHION
    {
        public static void Execute(string[] args)
        {
            var testCases = Convert.ToInt32(Console.ReadLine());
            var input = new List<KeyValuePair<List<int>, List<int>>>(testCases);

            // read testCases from INPUT.
            for (var i = 0; i < testCases; i++)
            {
                var line1 = Console.ReadLine();
                var line2 = Console.ReadLine();
                var line3 = Console.ReadLine();

                var N = Convert.ToInt32(line1);

                var menHotness = line2.Split(' ');
                var womenHotness = line3.Split(' ');

                var menHotnessList = menHotness.Select(n => Convert.ToInt32(n)).ToList();
                var womenHotnessList = womenHotness.Select(n => Convert.ToInt32(n)).ToList();

                menHotnessList.Sort();
                womenHotnessList.Sort();

                input.Add(new KeyValuePair<List<int>, List<int>>(menHotnessList, womenHotnessList));
            }


            // emit OUTPUT.
            var testCaseIndex = 0;
            foreach (var testCase in input)
            {
                var menHotness = testCase.Key;
                var womenHotness = testCase.Value;

                var sum = 0;
                for (int i = 0; i < menHotness.Count; i++)
                    sum += menHotness[i] * womenHotness[i];

                Console.WriteLine(sum);
            }
        }
    }
}