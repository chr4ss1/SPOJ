using System;
using System.Collections.Generic;

namespace SPOJ_PL
{
    class PIGGY
    {
        public static void Execute(string[] args)
        {
            var testCases = Convert.ToInt32(Console.ReadLine());
            while (testCases-- > 0)
            {
                var line = Console.ReadLine().Split(' ');

                // grams
                var weightOfEmptyPig = Convert.ToInt32(line[0]);
                var weightOfPigWithCoins = Convert.ToInt32(line[1]);

                var differentCoins = Convert.ToInt32(Console.ReadLine());
                var coinList = new Dictionary<int, int>(differentCoins);

                while (differentCoins-- > 0)
                {
                    line = Console.ReadLine().Split(' ');

                    var coinValue = Convert.ToInt32(line[0]);
                    var coinWeight = Convert.ToInt32(line[1]);

                    coinList[coinValue] = coinWeight;
                }

                var answer = Solve(weightOfEmptyPig, weightOfPigWithCoins, coinList);
                var possibleOutcomes = new[]
                                           {
                                               "The minimum amount of money in the piggy-bank is {0}.",
                                               "This is impossible."
                                           };

                if (answer == -1)
                    Console.WriteLine(possibleOutcomes[1]);
                else Console.WriteLine(possibleOutcomes[0], answer);

                _cache.Clear();
            }
        }

        private static Dictionary<int, int> _cache = new Dictionary<int, int>();
        private static int Solve(int weightOfEmptyPig, int currentWeight, Dictionary<int, int> coinList)
        {
            if (weightOfEmptyPig == currentWeight) return 0;
            if (currentWeight < weightOfEmptyPig) return -1;
            if (_cache.ContainsKey(currentWeight)) return _cache[currentWeight];

            var minimumAmount = -1;
            foreach (var coin in coinList)
            {
                var coinValue = coin.Key;
                var coinWeight = coin.Value;

                var cx = Solve(weightOfEmptyPig, currentWeight - coinWeight, coinList);
                if (cx == -1) continue;

                cx += coinValue;
                minimumAmount = minimumAmount == -1 ? cx : Math.Min(minimumAmount, cx);
            }

            _cache[currentWeight] = minimumAmount;
            return minimumAmount;
        }
    }
}

