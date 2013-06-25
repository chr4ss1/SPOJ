using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    public class ARMY
    {
        public static void Execute()
        {
            try
            {
                var testCases = Convert.ToInt32(Console.ReadLine());
                while (testCases-- > 0)
                {
                    Console.ReadLine(); // blank

                    var line = Console.ReadLine().Split(' ');
                    var NG = Convert.ToInt32(line[0]);
                    var MG = Convert.ToInt32(line[1]);

                    var NGMax = Console.ReadLine().Split(' ').Select(x => Convert.ToInt32(x)).Max();
                    var MGMax = Console.ReadLine().Split(' ').Select(x => Convert.ToInt32(x)).Max();

                    if (NGMax >= MGMax) Console.WriteLine("Godzilla");
                    else Console.WriteLine("MechaGodzilla");
                }
            }
            catch (Exception e)
            {

            }
        }
    }
}