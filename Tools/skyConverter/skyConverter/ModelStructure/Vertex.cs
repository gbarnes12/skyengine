using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    public class Vertex : ISerializer
    {
        private double[] position;
	    private double[] uv;
	    private double[] normal;
	
	    public Vertex(double[] _position, double[] _uv, double[] _normal){
		    position = _position;
		    uv = _uv;
		    normal = _normal;
	    }

        public JObject serializeObject() 
        {
		    JObject obj = new JObject();
		
		    if(position.Length > 0)
            {
		
			    JArray positionNode = new JArray();
			    positionNode.Add(position[0]);
			    positionNode.Add(position[1]);
			    positionNode.Add(position[2]);
			
			    obj.Add("Position", positionNode);
		
		    }
		
		    if(uv.Length > 0)
            {
			
			    JArray uvNode = new JArray();
			    uvNode.Add(uv[0]);
			    uvNode.Add(uv[1]);
			
			    obj.Add("UV", uvNode);
			
		    }
		
		    if(normal.Length > 0)
            {
			    JArray normalNode = new JArray();
			    normalNode.Add(normal[0]);
			    normalNode.Add(normal[1]);
			    normalNode.Add(normal[2]);
			
			    obj.Add("Normal", normalNode);
			
		    }
		
		
		    if (obj.Count > 0){
			    return obj;
		    }

		    return null;
		
	    }

        public JArray serializeArray() 
        {
		    // TODO Auto-generated method stub
		    return null;
	    }
    }
}
