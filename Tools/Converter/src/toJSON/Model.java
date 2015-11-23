package toJSON;

import java.util.ArrayList;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Model implements ISerializer{
	private String name = "";
	private ArrayList<Mesh> meshes;
	
	public Model(String _name){
		name = _name;
		
		meshes = new ArrayList<Mesh>();
	}
	
	public void addMesh(Mesh mesh){
		meshes.add(mesh);
	}

	@Override
	public JSONObject serializeObject() {
		
		JSONObject obj = new JSONObject();
		
		obj.put("Name", name);
		
		if(!meshes.isEmpty()){
			JSONArray meshesNode = new JSONArray();
			
			for(int i = 0; i < meshes.size(); i++) {
				Mesh m = meshes.get(i);
				meshesNode.add(m.serializeObject());
			}
			obj.put("Meshes", meshesNode);
			
			return obj;
		}		
		return null;
	}

	@Override
	public JSONArray serializeArray() {
		return null;
	}
	
	
}
