using System;
using System.Collections.Generic;

namespace SPOJ_PL
{
    public class ACODE
    {
        private static Dictionary<ulong, ulong> _cache = new Dictionary<ulong, ulong>();
        private static char[] _charCache = new char[2];

        private static int ConvertToUlong(char first, char second)
        {
            _charCache[0] = first;
            _charCache[1] = second;

            return Convert.ToInt32(new string(_charCache));
        }

        private static ulong Solve(string ways, ulong offset)
        {
            // If we are dealing with only one character,
            // then we have one different way to decode it
            // or if it'z zero, then we can't decode it!
            if (offset + 1 == (ulong)ways.Length)
            {
                if (ways[(int)offset] != '0')
                    return 1UL;

                return 0UL;
            }

            // If we are dealing with only two characters
            if (offset + 2 == (ulong)ways.Length)
            {
                // either split it one by one
                // or use whole.

                var firstChar = ways[(int)offset];
                var secondChar = ways[(int)offset + 1];

                var actualValue = ConvertToUlong(firstChar, secondChar);

                var solutions = 0UL;
                if (firstChar >= '1' && actualValue <= 26) solutions++;
                if (firstChar >= '1' && secondChar >= '1') solutions++;

                return solutions;
            }

            if (_cache.ContainsKey(offset))
                return _cache[offset];

            var firstCharx = ways[(int)offset];
            var secondCharx = ways[(int)offset + 1];
            var thirdCharx = ways[(int)offset + 2];

            // use first char if possible
            var extra = 0UL;
            var actualValuex = ConvertToUlong(firstCharx, secondCharx);

            if (firstCharx >= '1' && secondCharx != '0')
                extra = Solve(ways, offset + 1);

            if (firstCharx >= '1' && actualValuex <= 26 && thirdCharx != '0')
                extra += Solve(ways, offset + 2);

            _cache[offset] = extra;
            return _cache[offset];
        }

        public static void Execute()
        {
            try
            {
                while (true)
                {
                    var line = Console.ReadLine();
                    if (line == "0")
                        break;

                    Console.WriteLine(Solve(line, 0));
                    _cache.Clear();
                }

            }
            catch (Exception e)
            {

            }
        }
    }
}