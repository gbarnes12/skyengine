using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkySuite
{
    class Settings
    { 
        private int _width = 0;
        private int _height = 0;
        private int _depthBits = 0;
        private int _colorBits;
        private int _alphaBits;
        private bool _isFullscreen;
        private int[] _version;
        private bool _deferredDebugMode;
        private bool _showFPS;
        private float[] _position;
        private float[] _lookAt;
        private bool _isDebugMode;
        private String _assetDirectory;
        private String _host;
        private int _port;
        private bool _attach;

        public Settings()
        {

        }

        public Settings(dynamic stuff)
        {
            try
            {
                this.Width = stuff.Settings.Window.Width;
                this.Height = stuff.Settings.Window.Height;
                this.DepthBits = stuff.Settings.Window.DepthBits;
                this.ColorBits = stuff.Settings.Window.ColorBits;
                this.AlphaBits = stuff.Settings.Window.AlphaBits;
                this.IsFullscreen = stuff.Settings.Window.IsFullscreen;
                this.Version = stuff.Settings.Renderer.Version;
                this.DeferredDebugMode = stuff.Settings.Renderer.DeferredDebugMode;
                this.ShowFPS = stuff.Settings.Renderer.ShowFPS;
                this.Position = stuff.Settings.Renderer.Camera.Position;
                this.LookAt = stuff.Settings.Renderer.Camera.LookAt;
                this.IsDebugMode = stuff.Settings.Development.IsDebugMode;
                this.AssetDirectory = stuff.Settings.Development.AssetDirectory;
                this.Host = stuff.Settings.Development.skySuite.Host;
                this.Port = stuff.Settings.Development.skySuite.Port;
                this.Attach = stuff.Settings.Development.skySuite.Attach;
            }
            catch (Exception e)
            {
                
            }
        }

        // Save
        public dynamic save(dynamic stuff)
        {
            stuff.Settings.Window.Width = this.Width;
            stuff.Settings.Window.Height = this.Height ;
            stuff.Settings.Window.DepthBits = this.DepthBits;
            stuff.Settings.Window.ColorBits = this.ColorBits;
            stuff.Settings.Window.AlphaBits = this.AlphaBits;
            stuff.Settings.Window.IsFullscreen = this.IsFullscreen;
            stuff.Settings.Renderer.Version = this.Version;
            stuff.Settings.Renderer.DeferredDebugMode = this.DeferredDebugMode;
            stuff.Settings.Renderer.ShowFPS = this.ShowFPS;
            stuff.Settings.Renderer.Camera.Position = this.Position;
            stuff.Settings.Renderer.Camera.LookAt = this.LookAt;
            stuff.Settings.Development.IsDebugMode = this.IsDebugMode;
            stuff.Settings.Development.AssetDirectory = this.AssetDirectory;
            stuff.Settings.Development.skySuite.Host = this.Host;
            stuff.Settings.Development.skySuite.Port = this.Port;
            stuff.Settings.Development.skySuite.Attach = this.Attach;
            return stuff;
        }

        [Category("Window")]
        public int Width
        {
            get { return _width; }
            set { _width = value; }
        }

        [Category("Window")]
        public int Height
        {
            get { return _height; }
            set { _height = value; }
        }

        [Category("Window")]
        public int DepthBits
        {
            get { return _depthBits; }
            set { _depthBits = value; }
        }

        [Category("Window")]
        public int ColorBits
        {
            get { return _colorBits; }
            set { _colorBits = value; }
        }

        [Category("Window")]
        public int AlphaBits
        {
            get { return _alphaBits; }
            set { _alphaBits = value; }
        }

        [Category("Window")]
        public bool IsFullscreen
        {
            get { return _isFullscreen; }
            set { _isFullscreen = value; }
        }

        [Category("Renderer")]
        public int[] Version
        {
            get { return _version; }
            set { _version = value; }
        }

        [Category("Renderer")]
        public bool DeferredDebugMode
        {
            get { return _deferredDebugMode; }
            set { _deferredDebugMode = value; }
        }

        [Category("Renderer")]
        public bool ShowFPS
        {
            get { return _showFPS; }
            set { _showFPS = value; }
        }

        [Category("Camera")]
        public float[] Position
        {
            get { return _position; }
            set { _position = value; }
        }

        [Category("Camera")]
        public float[] LookAt
        {
            get { return _lookAt; }
            set { _lookAt = value; }
        }

        [Category("Development")]
        public bool IsDebugMode
        {
            get { return _isDebugMode; }
            set { _isDebugMode = value; }
        }

        [Category("Development")]
        public string AssetDirectory
        {
            get { return _assetDirectory; }
            set { _assetDirectory = value; }
        }

        [Category("SkySuite")]
        public string Host
        {
            get { return _host; }
            set { _host = value; }
        }

        [Category("SkySuite")]
        public int Port
        {
            get { return _port; }
            set { _port = value; }
        }

        [Category("SkySuite")]
        public bool Attach
        {
            get { return _attach; }
            set { _attach = value; }
        }
          
    }
}
