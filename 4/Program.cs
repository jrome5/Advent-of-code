using System;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
namespace Advent4
{
    class ReadFromFile
    {
        static void Main()
        {
            string path = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\..\input.txt");
            string[] files = File.ReadAllLines(path);
            int valid_passports = 0;
            int fields = 0;
            int total_passports = 0;
            string passport = "";
            foreach (string line in files)
            {
                passport += line;
                if (line.Equals("") || line.Equals("\r\n") || line.Equals("\r") || line.Equals("\n"))
                {
                    if (fields > 5)
                    {
                        valid_passports++;
                        Console.WriteLine("valid: " + passport);
                    }
                    else
                    {
                        Console.WriteLine("invalid: " + passport);
                    }
                    fields = 0; //reset counter
                    total_passports++;
                    passport = "";
                }
                else
                {
                    int char_index = 0;
                    bool end_of_line = false;
                    while (!end_of_line)
                    {
                        char_index = line.IndexOf(":", char_index + 1);
                        if (char_index == -1)
                        {
                            end_of_line = true;
                            //break;
                        }
                        else
                        {
                            var field = line.Substring(char_index - 3, 3);

                            if (!field.Equals("cid"))
                            {
                                fields++;
                            }
                        }
                    }
                }
            }
			Console.WriteLine("valid passports: " + valid_passports);
        }
    }
}
