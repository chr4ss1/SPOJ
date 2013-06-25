using System;
using System.Collections.Generic;
using System.Linq;

namespace SPOJ_PL
{
    public class COINS
    {
        private static Dictionary<ulong, ulong> _cache = new Dictionary<ulong, ulong>();
        private static ulong Solve(ulong coins)
        {
            if (coins <= 1)
                return coins;

            if (_cache.ContainsKey(coins))
                return _cache[coins];

            var solutions = new List<ulong> { coins };

            var firstPart = coins / 2;
            var secondPart = coins / 3;
            var thirdPart = coins / 4;

            solutions.Add(firstPart + secondPart + thirdPart);

            // calculate more
            var firstPartExchanged = Solve(firstPart);
            var secondPartExchanged = Solve(secondPart);
            var thirdPartExchanged = Solve(thirdPart);

            solutions.Add(firstPart + secondPartExchanged + thirdPart);
            solutions.Add(firstPart + secondPartExchanged + thirdPartExchanged);
            solutions.Add(firstPart + secondPart + thirdPartExchanged);

            solutions.Add(firstPartExchanged + secondPart + thirdPart);
            solutions.Add(firstPartExchanged + secondPartExchanged + thirdPart);
            solutions.Add(firstPartExchanged + secondPartExchanged + thirdPartExchanged);

            _cache[coins] = solutions.Max();
            return _cache[coins];
        }


        public static void Execute()
        {
            try
            {
                while (true)
                {
                    var line = Console.ReadLine();
                    if (!line.Any(Char.IsDigit))
                        break;

                    var coins = Convert.ToUInt64(line);
                    Console.WriteLine(Solve(coins));
                }
            }
            catch (Exception e)
            {

            }
        }
    }
}