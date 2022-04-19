using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading;

namespace ContainerProcess
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            string executingAssemblyPath = Assembly.GetExecutingAssembly().Location;

            if (args.Length == 0)
            {
                var startInfo = new ProcessStartInfo
                {
                    FileName = "dotnet",
                    Arguments = executingAssemblyPath + " " + Guid.NewGuid().ToString(),
                };

                var process = new Process
                {
                    StartInfo = startInfo,
                };

                process.Start();
                process.WaitForExit();
            }
            else
            {
                var startInfo = new ProcessStartInfo
                {
                    FileName = "ps",
                    Arguments = "-A f",
                };

                var process = new Process
                {
                    StartInfo = startInfo,
                };

                process.Start();
                Thread.Sleep(5000);
                process.WaitForExit();
            }
        }
    }
}
