using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    class Model : ISerializer
    {
        private String _name = "";
	    private List<Mesh> _meshes;
        private Material _material;
        private bool isMultipart = false;
        private int numberOfParts = 0;
        private int numberOfPart = 0;

	    public Model(String _name) 
        {
            this._name = _name;
		    this._meshes = new List<Mesh>();
            this._material = new Material("Materials/Phong.mat", "PHONG");
            this._material.specular = new double[] { 1.0, 1.0, 1.0, 1.0 };
            this._material.specularIntensity = 0.0;
	    }

        public void setIsMultipart(bool isMultiPart)
        {
            this.isMultipart = isMultiPart;
        }

        public void setNumberOfParts(int parts)
        {
            this.numberOfParts = parts;
        }

        public void setNumberOfPart(int part)
        {
            this.numberOfPart = part;
        }

        public int GetNumberOfPart()
        {
            return this.numberOfPart;
        }

	    public void addMesh(Mesh mesh)
        {
		    _meshes.Add(mesh);
	    }

        public JObject serializeObject()
        {

            JObject obj = new JObject();

            obj.Add("Name", _name);
            obj.Add("Material", this._material.serializeObject());

            JObject multipartObj = new JObject();
            multipartObj.Add("UseMultipart", isMultipart);
            multipartObj.Add("Part", numberOfPart);
            multipartObj.Add("TotalParts", numberOfParts);
            obj.Add("Multipart", multipartObj);

		    if(_meshes.Count != 0){
                JArray meshesNode = new JArray();

                for (int i = 0; i < _meshes.Count; i++)
                {
                    Mesh m = _meshes[i];
				    meshesNode.Add(m.serializeObject());
			    }
			    obj.Add("Meshes", meshesNode);
			
			    return obj;
		    }		
		    return null;
	    }

        public JArray serializeArray()
        {
		    return null;
	    }
	
    }
}
