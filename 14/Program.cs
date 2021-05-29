using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace Advent14
{
    class Program
    {
        static int mask_size = 36;
        static string uint2binary(long value)
        {
            var binary = Convert.ToString(value, 2);
            var padding = mask_size - binary.Length;
            for(int i = 0; i < padding; i++)
            {
                binary = "0" + binary;
            }
            return binary;
        }

        static long binary2long(string binary)
        {
            return Convert.ToInt64(binary, 2);
        }

        static long applyMask(string mask, long value)
        {
            var binary = uint2binary(value);
            string masked = "";
            for(int i = 0; i < mask_size; i++)
            {
                var tmp = mask.Length;
                var bit = mask.Substring(mask_size - i - 1, 1);
                int digit = Int32.Parse(binary.Substring(mask_size - i - 1, 1));
                if (bit == "X")
                {
                    masked = digit + masked;
                }
                else
                {
                    int op = Int32.Parse(bit);
                    masked = op + masked;
                }
            }
            Console.WriteLine(masked);
            return binary2long(masked);
        }
        static void Main(string[] args)
        {
            try
            {
                // Get the current directory.
                string path = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\..\input.txt");
                string[] files = File.ReadAllLines(path);
                string mask = "";
                Dictionary<long, long> mem = new Dictionary<long, long>();
                foreach (string line in files)
                {
                    Console.WriteLine(line);
                    bool mask_line = line.Contains("mask");
                    if(mask_line)
                    {
                        mask = line.Substring(7, mask_size); //36 bit value starting at index 7
                    }
                    else 
                    {
                        int addr_start = 4;
                        int addr_end = line.IndexOf(']');
                        long addr = Int64.Parse(line.Substring(addr_start, addr_end - addr_start));
                        int data_start = addr_end + 4;
                        long value = Int64.Parse(line.Substring(data_start, line.Length - data_start));
                        var masked = applyMask(mask, value);
                        mem[addr] = masked;
                    }
                }
                long sum = 0;
                foreach (long val in mem.Values)
                {
                    sum = sum + val;
                }
                Console.WriteLine(sum);
            }
            catch (Exception e)
            {
                Console.WriteLine("The process failed: {0}", e.ToString());
            }
        }
    }
}
