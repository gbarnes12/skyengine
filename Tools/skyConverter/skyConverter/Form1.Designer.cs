namespace skyConverter
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnConvert = new System.Windows.Forms.Button();
            this.tbFileLoad = new System.Windows.Forms.TextBox();
            this.tbFileSave = new System.Windows.Forms.TextBox();
            this.btnFileSaveSearch = new System.Windows.Forms.Button();
            this.btnFileLoadSearch = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.backgroundWorker = new System.ComponentModel.BackgroundWorker();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.label3 = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.label4 = new System.Windows.Forms.Label();
            this.sizeLabel = new System.Windows.Forms.Label();
            this.currentSizeLabel = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.splitPartsCheckBox = new System.Windows.Forms.CheckBox();
            this.useDebugMode = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // btnConvert
            // 
            this.btnConvert.Location = new System.Drawing.Point(212, 224);
            this.btnConvert.Name = "btnConvert";
            this.btnConvert.Size = new System.Drawing.Size(75, 23);
            this.btnConvert.TabIndex = 0;
            this.btnConvert.Text = "Convert";
            this.btnConvert.UseVisualStyleBackColor = true;
            this.btnConvert.Click += new System.EventHandler(this.btnConvert_Click);
            // 
            // tbFileLoad
            // 
            this.tbFileLoad.Location = new System.Drawing.Point(12, 26);
            this.tbFileLoad.Name = "tbFileLoad";
            this.tbFileLoad.Size = new System.Drawing.Size(304, 20);
            this.tbFileLoad.TabIndex = 1;
            // 
            // tbFileSave
            // 
            this.tbFileSave.Location = new System.Drawing.Point(12, 73);
            this.tbFileSave.Name = "tbFileSave";
            this.tbFileSave.Size = new System.Drawing.Size(304, 20);
            this.tbFileSave.TabIndex = 2;
            // 
            // btnFileSaveSearch
            // 
            this.btnFileSaveSearch.Location = new System.Drawing.Point(322, 73);
            this.btnFileSaveSearch.Name = "btnFileSaveSearch";
            this.btnFileSaveSearch.Size = new System.Drawing.Size(51, 23);
            this.btnFileSaveSearch.TabIndex = 3;
            this.btnFileSaveSearch.Text = "...";
            this.btnFileSaveSearch.UseVisualStyleBackColor = true;
            this.btnFileSaveSearch.Click += new System.EventHandler(this.btnFileSaveSearch_Click);
            // 
            // btnFileLoadSearch
            // 
            this.btnFileLoadSearch.Location = new System.Drawing.Point(322, 23);
            this.btnFileLoadSearch.Name = "btnFileLoadSearch";
            this.btnFileLoadSearch.Size = new System.Drawing.Size(51, 23);
            this.btnFileLoadSearch.TabIndex = 4;
            this.btnFileLoadSearch.Text = "...";
            this.btnFileLoadSearch.UseVisualStyleBackColor = true;
            this.btnFileLoadSearch.Click += new System.EventHandler(this.btnFileLoadSearch_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 54);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "SM File";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(23, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "File";
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(294, 224);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 7;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(8, 224);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(198, 23);
            this.progressBar.Step = 1;
            this.progressBar.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 208);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Progress";
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "obj";
            this.openFileDialog.FileName = "openFileDialog";
            this.openFileDialog.Filter = "Object File|*.obj";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.DefaultExt = "sm";
            this.saveFileDialog.Filter = "skyEngine Model|*.sm";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 134);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Estimated Size:";
            // 
            // sizeLabel
            // 
            this.sizeLabel.AutoSize = true;
            this.sizeLabel.Location = new System.Drawing.Point(94, 134);
            this.sizeLabel.Name = "sizeLabel";
            this.sizeLabel.Size = new System.Drawing.Size(0, 13);
            this.sizeLabel.TabIndex = 11;
            // 
            // currentSizeLabel
            // 
            this.currentSizeLabel.AutoSize = true;
            this.currentSizeLabel.Location = new System.Drawing.Point(94, 109);
            this.currentSizeLabel.Name = "currentSizeLabel";
            this.currentSizeLabel.Size = new System.Drawing.Size(0, 13);
            this.currentSizeLabel.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 109);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "Current Size:";
            // 
            // splitPartsCheckBox
            // 
            this.splitPartsCheckBox.AutoSize = true;
            this.splitPartsCheckBox.Location = new System.Drawing.Point(12, 179);
            this.splitPartsCheckBox.Name = "splitPartsCheckBox";
            this.splitPartsCheckBox.Size = new System.Drawing.Size(93, 17);
            this.splitPartsCheckBox.TabIndex = 14;
            this.splitPartsCheckBox.Text = "Split into Parts";
            this.splitPartsCheckBox.UseVisualStyleBackColor = true;
            this.splitPartsCheckBox.CheckedChanged += new System.EventHandler(this.splitPartsCheckBox_CheckedChanged);
            // 
            // useDebugMode
            // 
            this.useDebugMode.AutoSize = true;
            this.useDebugMode.Enabled = false;
            this.useDebugMode.Location = new System.Drawing.Point(113, 179);
            this.useDebugMode.Name = "useDebugMode";
            this.useDebugMode.Size = new System.Drawing.Size(93, 17);
            this.useDebugMode.TabIndex = 15;
            this.useDebugMode.Text = "Debug Format";
            this.useDebugMode.UseVisualStyleBackColor = true;
            this.useDebugMode.Visible = false;
            this.useDebugMode.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 251);
            this.Controls.Add(this.useDebugMode);
            this.Controls.Add(this.splitPartsCheckBox);
            this.Controls.Add(this.currentSizeLabel);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.sizeLabel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnFileLoadSearch);
            this.Controls.Add(this.btnFileSaveSearch);
            this.Controls.Add(this.tbFileSave);
            this.Controls.Add(this.tbFileLoad);
            this.Controls.Add(this.btnConvert);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "skyConverter";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnConvert;
        private System.Windows.Forms.TextBox tbFileLoad;
        private System.Windows.Forms.TextBox tbFileSave;
        private System.Windows.Forms.Button btnFileSaveSearch;
        private System.Windows.Forms.Button btnFileLoadSearch;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnCancel;
        private System.ComponentModel.BackgroundWorker backgroundWorker;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label sizeLabel;
        private System.Windows.Forms.Label currentSizeLabel;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox splitPartsCheckBox;
        private System.Windows.Forms.CheckBox useDebugMode;
    }
}

