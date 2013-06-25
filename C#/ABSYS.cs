using System;
using System.Linq;
using System.Collections.Generic;

namespace SPOJ_PL
{
    public class ABSYS
    {
        public static void Execute(string[] args)
        {
            try
            {
                var testCases = Convert.ToInt32(Console.ReadLine());
                while (testCases-- > 0)
                {
                    Console.ReadLine();

                    var equation = Console.ReadLine();

                    var parts = equation.Split('+');
                    var secondParts = parts[1].Split('=');

                    var firstPart = parts[0].Trim();
                    var secondPart = secondParts[0].Trim();
                    var thirdPart = secondParts[1].Trim();

                    var isFirstPartNumeric = (firstPart.Any(x => !Char.IsDigit(x)));
                    var isSecondPartNumeric = (secondPart.Any(x => !Char.IsDigit(x)));
                    var isThirdPartNumeric = (thirdPart.Any(x => !Char.IsDigit(x)));


                    if (isFirstPartNumeric)
                    {
                        var secondNumber = Convert.ToInt32(secondPart);
                        var thirdNumber = Convert.ToInt32(thirdPart);

                        var mkm = thirdNumber - secondNumber;

                        Console.WriteLine(string.Format("{0} + {1} = {2}", mkm, secondNumber, thirdNumber));
                    }
                    else if (isSecondPartNumeric)
                    {
                        var firstNumber = Convert.ToInt32(firstPart);
                        var thirdNumber = Convert.ToInt32(thirdPart);

                        var mkl = thirdNumber - firstNumber;

                        Console.WriteLine(string.Format("{0} + {1} = {2}", firstNumber, mkl, thirdNumber));
                    }
                    else if (isThirdPartNumeric)
                    {
                        var firstNumber = Convert.ToInt32(firstPart);
                        var secondNumber = Convert.ToInt32(secondPart);

                        var cc = firstNumber + secondNumber;

                        Console.WriteLine(string.Format("{0} + {1} = {2}", firstNumber, secondNumber, cc));
                    }
                    else
                    {
                        Console.WriteLine(equation);
                    }
                }
            }
            catch (Exception e)
            {
            }
        }
    }
}