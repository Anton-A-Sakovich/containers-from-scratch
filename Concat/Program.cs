using System;
using System.IO;
using System.Reflection;

namespace Concat
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            string fileName = DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss.ffff") + ".log";
            string filePath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? "/", fileName);

            string concatenatedArgs = String.Concat(args);

            File.WriteAllText(filePath, concatenatedArgs + Environment.NewLine);
            Console.WriteLine(concatenatedArgs);
        }
    }
}
