using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class Candy
    {
        private static void Execute(string[] args)
        {
            while (true)
            {
                var candyCount = Convert.ToInt32(Console.ReadLine());
                if (candyCount == -1)
                    break;


                // read in candies
                var candies = new List<int>();
                for (var i = 0; i < candyCount; i++)
                    candies.Add(Convert.ToInt32(Console.ReadLine()));

                candies = candies.OrderByDescending(x => x).ToList();

                // TAKE CARE OF SOME EXTREME CASES?!
                // ALL CANDIES ARE SAME || ONLY ONE CANDY
                if (candies[0] == candies.Last() || candyCount == 1)
                {
                    // answer is ZERO, since everything in the array is the same!!
                    Console.WriteLine(0);
                    continue;
                }


                // take average
                var average = candies.Average();
                if (average % 1 != 0)
                {
                    Console.WriteLine(-1);
                    continue;
                }

                var intAverage = (int)average;

                var movements = 0;

                var higher = 0;
                var lower = candies.Count - 1;

                while (higher < lower)
                {
                    var leftOver = candies[higher] - intAverage; // how much can we possibly take?!
                    if (leftOver <= 0) // if we don't have anything left, quit now!
                        break;

                    // see how much is left.
                    var howMuchIsMoreNeeded = intAverage - candies[lower];
                    if (howMuchIsMoreNeeded <= 0)
                        break;

                    var canWeSatisfy = leftOver >= howMuchIsMoreNeeded;
                    var space = Math.Abs(leftOver - howMuchIsMoreNeeded);

                    if (canWeSatisfy)
                    {
                        candies[higher] -= howMuchIsMoreNeeded;
                        candies[lower] += howMuchIsMoreNeeded;

                        movements += howMuchIsMoreNeeded;
                    }
                    else
                    {
                        candies[higher] -= leftOver;
                        candies[lower] += leftOver;

                        movements += leftOver;
                    }

                    if (candies[higher] == intAverage) higher++;
                    if (candies[lower] == intAverage) lower--;

                }
                Console.WriteLine(movements);
            }
        }
    }
}