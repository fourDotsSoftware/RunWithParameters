using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32;

namespace RunWithParameters
{
    class ArgsParser
    {
        public static bool ParseArgs(string[] args)
        {
            /*
            string sa = "";
            for (int k = 0; k < args.Length; k++)
            {
                sa += args[k] + " ";
            }

            MessageBox.Show(sa);
            */

            if (args.Length == 0)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);

                frmRunWithParameters fr = new frmRunWithParameters("");
                fr.ShowDialog();
                                
            }
            else if (args.Length > 0)
            {
                try
                {
                    if (args[0].ToLower().StartsWith("-tempfile:"))
                    {
                        string tempfile = GetParameter(args[0]);

                        //MessageBox.Show(tempfile);

                        using (StreamReader sr = new StreamReader(tempfile, Encoding.Unicode))
                        {
                            string scont = sr.ReadToEnd();

                            //args = scont.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                            args = SplitArguments(scont);
                            Module.args = args;

                            //MessageBox.Show(scont);
                        }
                    }

                }
                catch (Exception ex)
                {
                    Module.ShowError("Error could not parse Arguments !", ex);
                    return false;
                }

                /*
                string sa = "";
                for (int k = 0; k < args.Length; k++)
                {
                    sa += args[k] + "|";
                }

                MessageBox.Show(sa);
                  */

                try
                {

                    for (int k = 0; k < args.Length; k++)
                    {
                        if (System.IO.File.Exists(args[k]))
                        {
                            frmRunWithParameters f = new frmRunWithParameters(args[k]);
                            f.ShowDialog();

                        }
                    }


                }
                catch (Exception ex)
                {
                    Module.ShowError("Error while Running the File(s) !", ex);
                }
                finally
                {

                }
            }


            Environment.Exit(0);

            return true;
        }

        private static string GetParameter(string arg)
        {
            int spos = arg.IndexOf(":");
            if (spos == arg.Length - 1) return "";
            else
            {
                return arg.Substring(spos + 1);
            }
        }

        private static List<string> GetParameterValues(string arg)
        {
            string str = GetParameter(arg);

            string[] spl = str.Split(new string[] { "-" }, StringSplitOptions.RemoveEmptyEntries);
            List<string> parval = new List<string>();

            for (int k = 0; k < spl.Length; k++)
            {
                parval.Add(spl[k]);
            }

            return parval;
        }               

        public static string[] SplitArguments(string commandLine)
    {
        char[] parmChars = commandLine.ToCharArray();
        bool inSingleQuote = false;
        bool inDoubleQuote = false;
        for (int index = 0; index < parmChars.Length; index++)
        {
            if (parmChars[index] == '"' && !inSingleQuote)
            {
                inDoubleQuote = !inDoubleQuote;
                parmChars[index] = '\n';
            }
            if (parmChars[index] == '\'' && !inDoubleQuote)
            {
                inSingleQuote = !inSingleQuote;
                parmChars[index] = '\n';
            }
            if (!inSingleQuote && !inDoubleQuote && parmChars[index] == ' ')
                parmChars[index] = '\n';
        }
        return (new string(parmChars)).Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);
     }
    }
}
