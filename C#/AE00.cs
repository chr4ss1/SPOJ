using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    internal class AE00
    {

        public static void Execute(string[] args)
        {
            var sides = Convert.ToInt32(Console.ReadLine());

            var possibleVariations = 0;
            for (var width = 1; width <= sides; width++)
            {
                for (var height = width; height <= sides; height++)
                {
                    if (width * height > sides)
                        break;

                    possibleVariations++;
                }
            }


            Console.WriteLine(possibleVariations);
        }
    }
}