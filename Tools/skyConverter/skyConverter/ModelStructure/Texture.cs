using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.ModelStructure
{
    class Texture : ISerializer
    {
        private String file = "";
	    //private Sampler sampler;
	
	    public Texture(String _file /*, Sampler _sampler*/)
        {
		    file = _file;
		    //sampler = _sampler
	    }

	    public JObject serializeObject() 
        {
            JObject obj = new JObject();
		    obj.Add("File", file);
		
		    return obj;
	    }


	    public JArray serializeArray() 
        {
		    return null;
	    }
	
    }
}
