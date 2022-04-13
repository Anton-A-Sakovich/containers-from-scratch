using System;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace ContainerProcess
{
    internal class Program
    {
        private static void Main(string[] args)
        {          
            var si = new ProcessStartInfo
            {                
                FileName = "/bin/bash",
                UseShellExecute = false,
                RedirectStandardOutput = true,
            };

            si.ArgumentList.Add("-c");
            si.ArgumentList.Add("apt-get update && apt-get -qq install procps");

            var p = new Process
            {
                StartInfo = si,
            };

            p.Start();
            p.WaitForExit();

            Console.WriteLine($"{Environment.UserName}@{Environment.UserDomainName}:");

            var startInfo = new ProcessStartInfo
            {
                FileName = "/bin/ps",
                UseShellExecute = false,
            };

            startInfo.ArgumentList.Add("-A");
            startInfo.ArgumentList.Add("f");

            var process = new Process
            {
                StartInfo = startInfo,
            };

            process.Start();
            process.WaitForExit();

            Thread.Sleep(5000);
        }
    }
}
