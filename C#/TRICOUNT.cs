using System;
namespace SPOJ_PL
{
    class TRICOUNT
    {
        public static void Execute(string[] args)
        {
            var testCases = Convert.ToUInt64(Console.ReadLine());
            while (testCases-- > 0)
            {
                var n = Convert.ToUInt64(Console.ReadLine());
                Console.WriteLine(n * (n + 2) * (2 * n + 1) / 8);
            }
        }
    }
}
