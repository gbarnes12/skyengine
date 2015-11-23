package toJSON;

import java.util.ArrayList;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Mesh implements ISerializer{

	private String name="";
	private int countVertices;
	private ArrayList<Face> faces;
	
	public Mesh(String _name){
		name = _name;
		
		faces = new ArrayList<Face>();
	}
	
	
	public void addFace(Face face){
		faces.add(face);
	}

	public void setCountVertices(int _countVertices){
		countVertices = _countVertices;
	}
	@Override
	public JSONObject serializeObject() {
		
		JSONObject obj = new JSONObject();
		
		obj.put("Name", name);
		obj.put("Vertices", countVertices);
		
		if(!faces.isEmpty()){
			JSONArray facesNode = new JSONArray();
			for(int i = 0; i < faces.size(); i++){
				facesNode.add(faces.get(i).serializeArray());
			}
			obj.put("Faces", facesNode);
			return obj;
		}
		return null;
	}


	@Override
	public JSONArray serializeArray() {
		return null;
	}
	
	
}
