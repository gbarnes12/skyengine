using Sky.NetEngine.Components.Application;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace SkyAssetBrowser.Forms
{
    public partial class RenderWindow : DockContent
    {
        D3D11Application mApplication = null;

        public RenderWindow()
        {
            InitializeComponent();
            bool result = D3D11Application.Spawn(renderPanel.Handle.ToInt32(), (uint)renderPanel.Width, (uint)renderPanel.Height, ref mApplication);
        }

        public void Render()
        {
            if (mApplication != null)
            {
                mApplication.Run();
            }
        }

        public void Resize()
        {
            if (mApplication != null)
            {
                mApplication.Resize((uint)renderPanel.Width, (uint)renderPanel.Height);
            }
        }
    }
}
