using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SPOJ_PL
{
    public class WILLITST
    {
        public static void Execute(string[] args)
        {

            var number = Convert.ToUInt64(Console.ReadLine());

            var visited = new Dictionary<ulong, bool>();
            while (number > 1)
            {
                if (number % 2 == 0) number /= 2;
                else
                    number = 3 * number + 3;

                if (visited.ContainsKey(number))
                {
                    Console.WriteLine("NIE");
                    return;
                }

                visited.Add(number, true);
            }

            Console.WriteLine("TAK");
        }
    }
}
