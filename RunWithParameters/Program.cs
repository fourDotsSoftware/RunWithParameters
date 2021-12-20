using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace RunWithParameters
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            ExceptionsHelper.AddUnhandledExceptionHandlers();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            ArgsParser.ParseArgs(args);

            Environment.Exit(0);
        }
    }
}