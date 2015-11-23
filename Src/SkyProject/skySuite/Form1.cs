using Newtonsoft.Json;
using Sky.Core.Network;
using skySuite.DataLists;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SkySuite
{
    public enum skyBuilds
    {
        release,
        debug,
        master
    }

    public partial class Form1 : Form
    {
        public skyUDPServer m_pServer;
        skyLogList list;
        bool exitWorker = false;
        skyBuilds m_eCurrentBuild = skyBuilds.debug;

        public Form1()
        {
            InitializeComponent();

            skyUDPServer.Spawn(ref m_pServer);
            list = new skyLogList();
            Thread thread = new Thread(new ThreadStart(this.Work));
            thread.IsBackground = true;
            thread.Name = "My Worker.";
            thread.Start();

            dataGridView.DataSource = list;

            buildModeCBox.DataSource = Enum.GetValues(typeof(skyBuilds)).Cast<skyBuilds>();
            buildModeCBox.SelectedIndex = 1;
        }

        private void Work()
        {
            while (exitWorker == false)
            {
                if (m_pServer != null)
                {
                    string s = m_pServer.Process();

                    if (s != null)
                    {
                        System.Console.WriteLine(s);
                        lock (list)
                        {
                            try
                            {
                                String[] aMessage = s.Split(';');

                                if (aMessage.Length == 5)
                                {
                                    if (aMessage[0].Equals("log"))
                                    {
                                        skyLogEntry l_cEntry = new skyLogEntry(skyLogType.INFO, DateTime.Now, aMessage[2], aMessage[3], aMessage[4]);
                                        list.Add(l_cEntry);
                                        this.Invoke((Action)(() => dataGridView.DataSource = typeof(skyLogList)));
                                        this.Invoke((Action)(() => dataGridView.DataSource = list));
                                        
                                    }
                                }
                                //this.Dispatcher.Invoke((Action)(() => Grid.CurrentItem = Grid.Items[list.Count-1]));

                            }
                            catch (Exception e)
                            {

                            }
                        }
                    }
                }

                Thread.Sleep(100);
            }
        }

        private void startWorldEditBtn_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Not Yet Implemented");
        }

        private void startGameBtn_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process[] l_cProcess = Process.GetProcessesByName("Game");
            if (l_cProcess.Length == 0)
            {
                StartGame();
            }
            else
            {
                foreach (Process p in l_cProcess)
                {
                    p.Kill();// Normales ende
                }

                StartGame();
            }
        }

        private void StartGame()
        {
            try
            {
                list.Clear();
                System.Diagnostics.Process.Start("Game.exe");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void editEngineconf_Click(object sender, EventArgs e)
        {
            // Neues Fenster öffnen
            Form newWindow = new Form();
            newWindow.Size = new System.Drawing.Size(800, 600);
            
            // Property Grid erstellen
            PropertyGrid newWin = new PropertyGrid();
            newWin.Top = 25;
            newWin.Size = new System.Drawing.Size(800, 600);

            Button saveButton = new Button();
            saveButton.Select();
            saveButton.Text = "Speichern";
            saveButton.Click += new System.EventHandler(saveButton_Click);
            
            // Füge Property Grid in neues Fenster ein
            newWindow.Controls.Add(newWin);
            newWindow.Controls.Add(saveButton);

            // Wir lesen zuerst die Config Datei ein
            // Dateipfad
            string path = "../Common/engine.conf";
            
            // Alles in einen string packen
            string text = File.ReadAllText(path);

            dynamic stuff = JsonConvert.DeserializeObject(text);

            Settings conf = new Settings(stuff);

            newWin.SelectedObject = conf;

            newWindow.Show();

        }

        private void saveButton_Click(Object sender, System.EventArgs e)
        {

        }

    }
}
