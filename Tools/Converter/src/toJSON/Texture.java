package toJSON;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class Texture implements ISerializer{
	private String file = "";
	//private Sampler sampler;
	
	public Texture(String _file /*, Sampler _sampler*/){
		file = _file;
		//sampler = _sampler
	}

	@Override
	public JSONObject serializeObject() {
		
		JSONObject obj = new JSONObject();
		
		obj.put("File", file);
		//obj.put("Sampler", sampler);
		
		return obj;
	}

	@Override
	public JSONArray serializeArray() {
		return null;
	}
	
	
}
