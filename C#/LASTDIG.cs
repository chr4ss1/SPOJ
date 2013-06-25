using System;
namespace SPOJ_PL
{
    public class LASTDIG
    {
        public static void Execute()
        {
            var testCases = Convert.ToInt32(Console.ReadLine());
            while (testCases-- > 0)
            {
                var parts = Console.ReadLine().Split(' ');
                var numberBase = Convert.ToInt32(parts[0]);
                var numberExponent = Convert.ToInt32(parts[1]);

                if (numberBase == 0 && numberExponent == 1) Console.WriteLine(0);
                else if (numberBase == 1 && numberExponent == 0) Console.WriteLine(1);
                else if (numberBase == 0 && numberExponent == 0) Console.WriteLine(1);
                else
                {
                    var result = 1;
                    while (numberExponent > 0)
                    {
                        if (numberExponent % 2 == 1)
                            result = (result * numberBase) % 10;

                        numberExponent = numberExponent >> 1;
                        numberBase = (numberBase * numberBase) % 10;
                    }
                    Console.WriteLine(result);
                }
            }
        }
    }
}