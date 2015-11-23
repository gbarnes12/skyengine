using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    class Mesh : ISerializer
    {
        private String _name = "";
	    private int _countVertices;
        private List<Face> _faces;
        private Material _material;

	    public Mesh(String _name)
        {
		    this._name = _name;
		    _faces = new List<Face>();

            this._material = new Material("Materials/Phong.mat", "PHONG");
            this._material.specular = new double[] { 1.0, 1.0, 1.0, 1.0 };
            this._material.specularIntensity = 0.0;

            this._material.diffuse = new double[] { 1.0, 1.0, 1.0, 1.0 };
	    }
	
	    public void AddFace(Face face)
        {
		    _faces.Add(face);
	    }

	    public void SetCountVertices()
        {
            this._countVertices = _faces.Count * 3;
	    }


	    public JObject serializeObject() 
        {
		    JObject obj = new JObject();
		
		    obj.Add("Name", _name);
		    obj.Add("Vertices", _countVertices);

            if (_faces.Count > 0)
            {
			    JArray facesNode = new JArray();

                for (int i = 0; i < _faces.Count; i++)
                {
                    facesNode.Add(_faces[i].serializeArray());
			    }

			    obj.Add("Faces", facesNode);
                obj.Add("Material", this._material.serializeObject());

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
