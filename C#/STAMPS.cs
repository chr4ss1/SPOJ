using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    public class STAMPS
    {
        public static void Execute()
        {
            // Lucy minimize friends

            try
            {

                var scenario = 1;
                var testCases = Convert.ToInt32(Console.ReadLine());
                while (testCases-- > 0)
                {
                    var line = Console.ReadLine().Split(' ');
                    var marksNeeded = Convert.ToInt32(line[0]);
                    var friends = Convert.ToInt32(line[1]);

                    var answer = 0;
                    var friendList = Console.ReadLine().Split(' ').Select(x => Convert.ToInt32(x)).OrderByDescending(x => x);
                    foreach (var friend in friendList)
                    {
                        if (marksNeeded <= 0) break;
                        marksNeeded -= friend;
                        answer++;
                    }

                    Console.WriteLine(string.Format("Scenario #{0}:", scenario));
                    if (marksNeeded > 0) Console.WriteLine("impossible");
                    else Console.WriteLine(answer);

                    Console.WriteLine();

                    scenario++;
                }
            }
            catch (Exception e)
            {

            }
        }
    }
}