using Newtonsoft.Json;
using skyConverter.ModelStructure;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.Exporters
{
    class Exporter
    {
        private List<Model> _models;
        private bool isMultipart;

        public Exporter(bool isMultipart)
	    {
            _models = new List<Model>();
            this.isMultipart = isMultipart;
	    }

        public void SetModels(Model model)
        {
            this._models.Add(model);
        }

        public void SetModels(List<Model> models)
        {
            this._models = models;
        }

	    public void Save(String path)
	    {
            if (!isMultipart)
                SaveSinglePart(path);
            else
                SaveMultiPart(path);
	    }

        private void SaveMultiPart(String path)
        {
            if (_models.Count <= 0)
                throw new Exception("Invalid models");

            String pathName = Path.GetDirectoryName(path);
            String fileName = Path.GetFileNameWithoutExtension(path);

            foreach (Model m in _models)
            {
                String filePath = @pathName + "\\" + fileName;
                filePath += (m.GetNumberOfPart() == 1) ? ".sm" : "." + m.GetNumberOfPart() + ".smpart" ;

                using (StreamWriter file = File.CreateText(filePath))
                using (JsonTextWriter writer = new JsonTextWriter(file))
                {
                    writer.Formatting = Formatting.None;
                    m.serializeObject().WriteTo(writer);
                }
            }
        }

        private void SaveSinglePart(String path)
        {
            if (_models[0] == null)
                throw new Exception("Invalid model");

            using (StreamWriter file = File.CreateText(@path))
            using (JsonTextWriter writer = new JsonTextWriter(file))
            {
                writer.Formatting = Formatting.None;
                _models[0].serializeObject().WriteTo(writer);
            }
        }
    }
}
