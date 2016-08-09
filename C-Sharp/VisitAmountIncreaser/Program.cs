using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VisitAmountIncreaser
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("The application is staring!");
            //string url = Console.ReadLine();
            string url = "http://blog.csdn.net";
            //int threadAcount = 2;
            StartTask(url);
            string command = Console.ReadLine();
            if (string.CompareOrdinal(command, "X") == 0)
            {
                Console.WriteLine("Application will quit after 30 seconds!");
                Thread.Sleep(30000);
            }
        }

        static async void StartTask(string url)
        {
            while (true)
            {
                await RunVisit(url);
                Thread.Sleep(1000);
            }
        }

        static async Task RunVisit(string url)
        {
            using (var client = new HttpClient())
            {
                client.BaseAddress = new Uri(url);
                client.DefaultRequestHeaders.Accept.Clear();
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("text/html"));
                string BlogURL = "kiritow/article/details/51339461";
                try
                {
                    HttpResponseMessage response = await client.GetAsync(BlogURL);
                    response.EnsureSuccessStatusCode();    // Throw if not a success code.

                    string content = await response.Content.ReadAsStringAsync();

                    string result = GetStringInBetween(content, "<span class=\"link_view\" title=\"阅读次数\">", "</span>");
                    Console.WriteLine(result);
                }
                catch (HttpRequestException e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        public static string GetStringInBetween(string strSource, string strStart, string strEnd)
        {
            if (strSource.Contains(strStart) && strSource.Contains(strEnd))
            {
                int Start = strSource.IndexOf(strStart, 0, System.StringComparison.Ordinal) + strStart.Length;
                int End = strSource.IndexOf(strEnd, Start, System.StringComparison.Ordinal);
                return strSource.Substring(Start, End - Start);
            }
            else
            {
                return "";
            }
        }
    }
}
