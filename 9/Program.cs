using System;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;

namespace Advent9
{
    class Program
    {

        private static bool IsInvalid(int number, List<int> preamble)
        {
            int length = preamble.Count;
  
            for(int i = 0; i < length-1; i++)
            {
                for (int j = i+1; j < length; j++)
                {
                    var lhs = preamble[i];
                    var rhs = preamble[j];
                    //Console.WriteLine("" + number + ": " + lhs + " + " + rhs + " - " + ((lhs + rhs)));
                    if ((lhs + rhs) == number)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        static void Main()
        {
            string path = ("C:/Users/jackrome/source/repos/Advent9/Advent9/input.txt");

            if (!File.Exists(path))
            {
                // Create the file.
                using (FileStream fs = File.Create(path))
                {
                    Byte[] info =
                        new UTF8Encoding(true).GetBytes("This is some text in the file.");

                    // Add some information to the file.
                    fs.Write(info, 0, info.Length);
                }
            }

            // Open the stream and read it back.
            using (StreamReader sr = File.OpenText(path))
            {
                string s = "";
                Queue<int> q = new Queue<int>();
                int value = 0;
                while ((s = sr.ReadLine()) != null)
                {
                    value = int.Parse(s);
            
                    if (q.Count == 25)
                    {
                        if (IsInvalid(value, Enumerable.ToList<int>(q)))
                        {
                            break;
                        }
                        q.Dequeue();
                    }
                    q.Enqueue(value);

                }
                Console.WriteLine("First invalid: " + value);
            }
        }
    }
}
