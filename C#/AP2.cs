using System;
using System.Linq;
using System.Text;

namespace SPOJ_PL
{
    class AP2
    {
        public static void Execute(string[] args)
        {
            var testCases = Convert.ToInt32(Console.ReadLine());
            var str = new StringBuilder(2000);

            ulong thirdTerm, thirdLastTerm, sum, diff, d;
            int terms;

            while (testCases-- > 0)
            {
                var vx = Console.ReadLine().Split(' ').Select(x => Convert.ToUInt64(x)).ToList();
                thirdTerm = vx[0];
                thirdLastTerm = vx[1];
                sum = vx[2];

                terms = (int)(2 * sum / (thirdTerm + thirdLastTerm));
                diff = (ulong)(-2 + terms - 3);
                d = (thirdLastTerm - thirdTerm) / (diff);

                Console.WriteLine(terms);

                str.Length = 0;

                for (var j = 0; j < terms; j++)
                {
                    if (j > 0)
                        str.Append(" ");

                    str.Append((long)thirdTerm + ((long)j - 2) * (long)d);
                }

                Console.WriteLine(str);
            }
        }
    }
}
