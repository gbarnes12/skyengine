package toJSON;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Face implements ISerializer {

	private Vertex[] vertices = new Vertex[3];

	public Face(Vertex v1, Vertex v2, Vertex v3){
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
	}
	
	@Override
	public JSONObject serializeObject() {
		return null;
	}

	@Override
	public JSONArray serializeArray() {
		
		JSONArray verticesNode = new JSONArray();
		
		if(vertices[0] != null){
			verticesNode.add(vertices[0].serializeObject());
		}
		
		if(vertices[1] != null){
			verticesNode.add(vertices[1].serializeObject());
		}
		
		if(vertices[2] != null){
			verticesNode.add(vertices[2].serializeObject());
		}
		
		if(!verticesNode.isEmpty()){
			return verticesNode;
		}
		
		return null;
	}
}
