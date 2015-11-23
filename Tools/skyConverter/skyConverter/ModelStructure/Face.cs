using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    class Face : ISerializer
    {
        private Vertex[] vertices = new Vertex[3];

	    public Face(Vertex v1, Vertex v2, Vertex v3)
        {
		    vertices[0] = v1;
		    vertices[1] = v2;
		    vertices[2] = v3;
	    }

        public JObject serializeObject()
        {
		    return null;
	    }

        public JArray serializeArray() 
        {

            JArray verticesNode = new JArray();
		
		    if(vertices[0] != null)
            {
			    verticesNode.Add(vertices[0].serializeObject());
		    }
		
		    if(vertices[1] != null)
            {
                verticesNode.Add(vertices[1].serializeObject());
		    }
		
		    if(vertices[2] != null)
            {
                verticesNode.Add(vertices[2].serializeObject());
		    }
		
		    if(verticesNode.Count > 0)
            {
			    return verticesNode;
		    }
		
		    return null;
	    }
    }
}
