using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Runtime;
using System.Diagnostics;

namespace RunWithParameters
{
    public partial class frmRunWithParameters : RunWithParameters.CustomForm
    {
        public frmRunWithParameters(string file)
        {
            InitializeComponent();
            cmbFile.Text = file;
        }
                
        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;

            Environment.Exit(0);
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (cmbFile.Text.Trim() == String.Empty || !System.IO.File.Exists(cmbFile.Text))
            {
                Module.ShowMessage("Please specify a valid File to execute !");

                return;
            }


            RegistryKey reg = Registry.CurrentUser;

            RegistryKey reg2 = reg.OpenSubKey(@"Software\4dots Software", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey(@"Software\4dots Software");
            }

            reg = reg2;
            reg2 = reg.OpenSubKey("RunWithParameters", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey("RunWithParameters");
            }

            reg = reg2;


            List<string> lst = new List<string>();

            for (int k = 0; k < cmbParams.Items.Count; k++)
            {
                lst.Add(cmbParams.Items[k].ToString());
            }

            lst.Remove(cmbParams.Text);

            lst.Insert(0, cmbParams.Text);

            string[] vals = reg.GetValueNames();

            for (int k = 0; k < vals.Length; k++)
            {
                if (vals[k].StartsWith(cmbFile.Text + ":::"))
                {                    
                    reg.DeleteValue(vals[k]);
                }
            }
            
            for (int k=0;k<lst.Count && k<15;k++)
            {
                reg.SetValue(cmbFile.Text+":::"+k.ToString(),lst[k]);
            }                        

            reg2 = reg.OpenSubKey("Files", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey("Files");
            }

            reg = reg2;

            cmbFile.Items.Remove(cmbFile.Text);
            cmbFile.Items.Insert(0, cmbFile.Text);

            for (int k = 0; k < cmbFile.Items.Count && k < 15; k++)
            {
                reg.SetValue("File #"+ k.ToString(), cmbFile.Items[k].ToString());
            }                        

           ProcessStartInfo pr=new ProcessStartInfo(cmbFile.Text);

            pr.Arguments=cmbParams.Text;
            pr.WorkingDirectory = System.IO.Path.GetDirectoryName(cmbFile.Text);

           if (chkAdmin.Checked)
           {
               pr.Verb = "runas";
               //pr.UserName = "administrator";
               //pr.Password = new System.Security.SecureString();

               pr.UseShellExecute = true;
           }

            if (chkHidden.Checked)
            {
            pr.WindowStyle=ProcessWindowStyle.Hidden;
            }

            Process.Start(pr);

            this.DialogResult = DialogResult.OK;
                        
        }

        private void FillParameters()
        {
            cmbParams.Items.Clear();

            if (cmbFile.Text == "") return;

            RegistryKey reg = Registry.CurrentUser;

            RegistryKey reg2 = reg.OpenSubKey(@"Software\4dots Software", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey(@"Software\4dots Software");
            }

            reg = reg2;
            reg2 = reg.OpenSubKey("RunWithParameters", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey("RunWithParameters");
            }

            reg = reg2;

            string[] vals = reg.GetValueNames();

            for (int k = 0; k < vals.Length; k++)
            {
                if (vals[k].StartsWith(cmbFile.Text + ":::"))
                {
                    int epos = vals[k].LastIndexOf(":::");
                    cmbParams.Items.Add(reg.GetValue(vals[k]));
                }
            }                               
        }

        private void frmRunWithParameters_Load(object sender, EventArgs e)
        {
            FillParameters();

            RegistryKey reg = Registry.CurrentUser;

            RegistryKey reg2 = reg.OpenSubKey(@"Software\4dots Software", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey(@"Software\4dots Software");
            }

            reg = reg2;
            reg2 = reg.OpenSubKey("RunWithParameters", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey("RunWithParameters");
            }

            reg = reg2;                        

            reg2 = reg.OpenSubKey("Files", true);

            if (reg2 == null)
            {
                reg2 = reg.CreateSubKey("Files");
            }

            reg = reg2;

            cmbFile.Items.Clear();

            string[] valf = reg.GetValueNames();

            for (int k = 0; k < valf.Length; k++)
            {
                cmbFile.Items.Add(reg.GetValue(valf[k]));
            }
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            try
            {
                openFileDialog1.FileName = cmbFile.Text;                
            }
            catch { }

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                cmbFile.Text = openFileDialog1.FileName;

                FillParameters();
            }
        }

        private void cmbFile_SelectedIndexChanged(object sender, EventArgs e)
        {
            FillParameters();
        }
    }
}

