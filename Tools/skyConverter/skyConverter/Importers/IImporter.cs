using skyConverter.ModelStructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.Importers
{
    abstract class Importer
    {
        #region Private Members
        protected String _filePath;
        protected List<Model> _models;
        protected Dictionary<String, Mesh> _meshes;
        protected List<double[]> _vertices = new List<double[]>();
        protected List<double[]> _uvs = new List<double[]>();
        protected List<double[]> _normals = new List<double[]>();
        protected Mesh _lastMesh = null;
        protected bool isMultipart = false;
        #endregion

        /// <summary>
        /// 
        /// </summary>
        /// <param name="_path"></param>
        public Importer(String _path)
        {
            this._filePath = _path;
            _meshes = new Dictionary<String, Mesh>();
            _models = new List<Model>();
        }

        /// <summary>
        /// 
        /// </summary>
        public abstract void Import();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public List<Model> GetModels()
        {
            return this._models;
        }

        public Model GetFirstModel()
        {
            return this._models[0];
        }

        public void SetIsMultipart(bool val)
        {
            this.isMultipart = val;
        }
    }
}
