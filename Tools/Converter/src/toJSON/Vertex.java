package toJSON;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Vertex implements ISerializer {

	private double[] position;
	private double[] uv;
	private double[] normal;
	
	public Vertex(double[] _position, double[] _uv, double[] _normal){
		position = _position;
		uv = _uv;
		normal = _normal;
	}

	@Override
	public JSONObject serializeObject() {
		JSONObject obj = new JSONObject();
		
		if(position.length > 0){
		
			JSONArray positionNode = new JSONArray();
			positionNode.add(position[0]);
			positionNode.add(position[1]);
			positionNode.add(position[2]);
			
			obj.put("Position", positionNode);
		
		}
		
		if(uv.length > 0){
			
			JSONArray uvNode = new JSONArray();
			uvNode.add(uv[0]);
			uvNode.add(uv[1]);
			
			obj.put("UV", uvNode);
			
		}
		
		if(normal.length > 0){
			JSONArray normalNode = new JSONArray();
			normalNode.add(normal[0]);
			normalNode.add(normal[1]);
			normalNode.add(normal[2]);
			
			obj.put("Normal", normalNode);
			
		}
		
		
		if (!obj.isEmpty()){
			return obj;
		}
		return null;
		
	}

	@Override
	public JSONArray serializeArray() {
		// TODO Auto-generated method stub
		return null;
	}
	
}
