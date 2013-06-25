using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SPOJ_PL
{
    class NY10A
    {

        private static Dictionary<string, int> _cache = new Dictionary<string, int>();
        private static Dictionary<int, int> _intCache = new Dictionary<int, int>();

        //  TTT, TTH, THT, THH, HTT, HTH, HHT, HHH
        public static int FindOccurences(string line, int currentOffset)
        {
            if (_intCache.ContainsKey(currentOffset))
                return _intCache[currentOffset];

            if (currentOffset + 3 == line.Count())
            {
                _intCache[currentOffset] = 1;

                var ev = new string(new char[] { line[currentOffset], line[currentOffset + 1], line[currentOffset + 2] });
                if (!_cache.ContainsKey(ev))
                    _cache[ev] = 0;

                _cache[ev] += 1;
                return 1; // base case!! :-O
            }
            if (currentOffset + 3 > line.Count()) return 0; // not possible :-)


            // assume we have more than 3 characters left.

            var firstCharacter = line[currentOffset];
            var secondCharacter = line[currentOffset + 1];
            var thirdCharacter = line[currentOffset + 2];

            var str = new string(new char[] { firstCharacter, secondCharacter, thirdCharacter });

            if (!_cache.ContainsKey(str))
                _cache[str] = 0;

            // add one more, because we found it =]
            _cache[str] += 1;

            // evaluate other shizzle ;)
            var occurences = FindOccurences(line, currentOffset + 1);
            occurences += FindOccurences(line, currentOffset + 2);
            occurences += FindOccurences(line, currentOffset + 3);

            _intCache[currentOffset] = occurences;
            return occurences;
        }


        public static void Execute(string[] args)
        {

            var testCases = Convert.ToInt32(Console.ReadLine());
            while (testCases-- > 0)
            {
                var N = Convert.ToInt32(Console.ReadLine());
                var line = Console.ReadLine();

                Console.Write(N);

                var evaluation = FindOccurences(line, 0);
                foreach (var permutation in new[] { "TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH" })
                {
                    Console.Write(" ");
                    var contains = _cache.ContainsKey(permutation);
                    if (!contains)
                        Console.Write("0");
                    else
                    {
                        Console.Write(_cache[permutation]);
                    }
                }

                // if we are not dealing with latest testcase,
                // print out new line.
                if (testCases != 0)
                    Console.WriteLine();

                _intCache.Clear();
                _cache.Clear();
            }
        }
    }
}
