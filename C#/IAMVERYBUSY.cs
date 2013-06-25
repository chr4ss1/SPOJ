using System;
using System.Collections.Generic;
using System.Linq;

namespace SPOJ_PL
{
    class IAMVERYBUSY
    {
        private static List<KeyValuePair<int, int>> activityList;


        public static void Execute(string[] args)
        {
            var testCases = Convert.ToInt32(Console.ReadLine());

            while (testCases-- > 0)
            {
                var activities = Convert.ToInt32(Console.ReadLine());

                activityList = new List<KeyValuePair<int, int>>();
                while (activities-- > 0)
                {
                    var xc = Console.ReadLine().Split(' ').Select(x => Convert.ToInt32(x)).ToList();
                    var start = xc[0];
                    var end = xc[1];

                    activityList.Add(new KeyValuePair<int, int>(start, end));
                }

                activityList = activityList.OrderBy(x => x.Key).ToList();

                var rn = true;

                var cur = activityList.First();
                var st = cur.Key;
                var xd = 0;

                while (rn)
                {
                    var ex = activityList.Where(x => x.Key >= st).Any();
                    if (!ex) break;

                    st = activityList.Where(x => x.Key >= st).Min(x => x.Value);
                    xd++;
                }

                Console.WriteLine(xd);
            }
        }
    }
}
