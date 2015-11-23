using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    class Material : ISerializer
    {
        private String file = "";
	    private String name = "";

        public double diffuseIntensity = -1.0, ambientIntensity = -1.0, specularIntensity = -1.0;

        public double[] color = null, diffuse = null, specular = null;
        public int n = -1;

        public Texture diffuseTexture = null;
	
	    public Material(String _file, String _name)
        {
		    file = _file;
		    name = _name;
	    }

	    public JObject serializeObject() 
        {
		    JObject obj = new JObject();
		    obj.Add("File", file);
		    obj.Add("Name", name.ToUpper());
		
		    JObject parametersNode = new JObject();

            JArray colorArray = new JArray();

		    if(color != null) {
                colorArray.Add(color[0]);
                colorArray.Add(color[1]);
                colorArray.Add(color[2]);
                colorArray.Add(color[3]);
                parametersNode.Add("Color", colorArray);
            }


		    if(diffuse != null || diffuseIntensity >= 0 || diffuseTexture != null )
            {
			    JObject diffuseNode = new JObject();
			
			    if(diffuse != null)
                {
                    JArray colorDiffuseArray = new JArray();
                    colorDiffuseArray.Add(diffuse[0]);
                    colorDiffuseArray.Add(diffuse[1]);
                    colorDiffuseArray.Add(diffuse[2]);
                    colorDiffuseArray.Add(diffuse[3]);
				    diffuseNode.Add("Color", colorDiffuseArray);
			    }
			    if(diffuseIntensity >= 0){
				    diffuseNode.Add("Intensity", diffuseIntensity);
			    }
			    if(diffuseTexture != null){
				    diffuseNode.Add("Texture", diffuseTexture.serializeObject());
			    }
			
			    parametersNode.Add("Diffuse", diffuseNode);
		    }
		
		
		    if(specular != null || specularIntensity >= 0 || n >= 0 )
            {
			    JObject specularNode = new JObject();

                if (specular != null)
                {
                    JArray colorSpecularArray = new JArray();
                    colorSpecularArray.Add(specular[0]);
                    colorSpecularArray.Add(specular[1]);
                    colorSpecularArray.Add(specular[2]);
                    colorSpecularArray.Add(specular[3]);
                    specularNode.Add("Color", colorSpecularArray);
			    }
			    if(diffuseIntensity >= 0){
				    specularNode.Add("Intensity", specularIntensity);
			    }
			    if(n >= 0){
				    specularNode.Add("Shinieness", n);
			    }
			
			    parametersNode.Add("Specular", specularNode);
		    }
		
		
		    if(ambientIntensity >= 0)
            {
			    JObject ambientNode = new JObject();
			
			    ambientNode.Add("Intensity", ambientIntensity);
			    parametersNode.Add("Ambient", ambientNode);
		    }
		
		
		    obj.Add("Parameters", parametersNode);
		
		    return obj;
	    }

	    public JArray serializeArray() 
        {
		    return null;
	    }
    }
}
