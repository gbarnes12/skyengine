package toJSON;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public interface ISerializer {
	public JSONObject serializeObject();
	
	public JSONArray serializeArray();
}
