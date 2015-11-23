using skyConverter.Exporters;
using skyConverter.Importers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace skyConverter
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        private void btnConvert_Click(object sender, EventArgs e)
        {
            if (tbFileLoad.Text == "" || tbFileSave.Text == "")
            {
                MessageBox.Show("Error cannot convert please select a file to load or specifiy the file to save");
            }
            else
            {
                backgroundWorker.WorkerReportsProgress = true;
                backgroundWorker.RunWorkerAsync();
                backgroundWorker.DoWork += backgroundWorker_DoWork;
                backgroundWorker.ProgressChanged += backgroundWorker_ProgressChanged;
        
            }
        }

 
        void backgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar.Value = e.ProgressPercentage;
        }

        void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            backgroundWorker.ReportProgress(0);

            OBJImporter importer = new OBJImporter(tbFileLoad.Text, backgroundWorker);
            importer.SetIsMultipart(splitPartsCheckBox.Checked);
            importer.Import();

            backgroundWorker.ReportProgress(60);
            


            Exporter exporter = new Exporter(splitPartsCheckBox.Checked);

            if (!splitPartsCheckBox.Checked)
                exporter.SetModels(importer.GetFirstModel());
            else
                exporter.SetModels(importer.GetModels());

            exporter.Save(tbFileSave.Text);

            backgroundWorker.ReportProgress(100);
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private double GetKB(double length)
        {
            return (((double)length) / 1024);
        }

        private double GetMB(double length)
        {
            return (((double)length) / 1024) / 1024;
        }

        private void btnFileLoadSearch_Click(object sender, EventArgs e)
        {
            DialogResult rslt = openFileDialog.ShowDialog();

            if (rslt == System.Windows.Forms.DialogResult.OK)
            {
                FileInfo fi = new FileInfo(openFileDialog.FileName);
                double size = (fi.Length > 1024) ? GetMB((double)fi.Length) : GetKB((double)fi.Length);
                double estSize = (size / 100) * 159;
                currentSizeLabel.Text = Math.Round(size, 5).ToString() + " mb";
                sizeLabel.Text = Math.Round(estSize, 5).ToString() + " mb";

                tbFileLoad.Text = openFileDialog.FileName;
            }
        }

        private void btnFileSaveSearch_Click(object sender, EventArgs e)
        {
            DialogResult rslt = saveFileDialog.ShowDialog();

            if (rslt == System.Windows.Forms.DialogResult.OK)
            {
                tbFileSave.Text = saveFileDialog.FileName;
                
               
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void splitPartsCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (splitPartsCheckBox.Checked)
            {
                useDebugMode.Enabled = true;
                useDebugMode.Visible = true;
            }
            else
            {
                useDebugMode.Enabled = false;
                useDebugMode.Visible = false;
            }
        }
    }
}
