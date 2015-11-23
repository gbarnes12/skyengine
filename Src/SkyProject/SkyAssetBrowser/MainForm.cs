using Sky.Core;
using Sky.NetEngine.Components.Application;
using SkyAssetBrowser.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SkyAssetBrowser
{
    public partial class MainForm : Form
    {
       
        RenderWindow mRenderWindow = new RenderWindow();

        public MainForm()
        {
            InitializeComponent();
            mRenderWindow.Show(dockPanel1);
        }

        public bool AppStillIdle
        {
            get
            {
                NativeMethods.PeekMsg msg;
                return !NativeMethods.PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        public void Application_Idle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                if (mRenderWindow != null)
                {
                    mRenderWindow.Render();
                }
            }
        }

        #region NativeMethods Class
        internal class NativeMethods
        {
            private NativeMethods() { }

            [StructLayout(LayoutKind.Sequential)]
            public struct PeekMsg
            {
                public IntPtr hWnd;
                public Message msg;
                public IntPtr wParam;
                public IntPtr lParam;
                public uint time;
                public System.Drawing.Point p;
            }

            [System.Security.SuppressUnmanagedCodeSecurity] // This prevents run-time security checks, so DON'T LEAVE THIS SOMEWHERE INSECURE
            [DllImport("User32.dll", CharSet = CharSet.Auto)]
            public static extern bool PeekMessage(out PeekMsg msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);
        }
        #endregion

        private void renderPanel_Resize(object sender, EventArgs e)
        {
            if (mRenderWindow != null)
            {
                mRenderWindow.Resize();
            }
        }
    }
}
