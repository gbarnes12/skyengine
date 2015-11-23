package toJSON;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Material implements ISerializer{

	private String file = "";
	private String name = "";
	
	private double diffuseIntensity, ambientIntensity, specularIntensity;
	
	private double[] color, diffuse, specular;
	private int n;
	
	private Texture diffuseTexture;
	
	public Material(String _file, String _name, double _diffuseIntensity, double _ambientIntensity,
			double _specularIntensity, double[] _color, double[] _diffuse, double[] _specular, int _n){
		file = _file;
		name = _name;
		diffuseIntensity = _diffuseIntensity;
		ambientIntensity = _ambientIntensity;
		specularIntensity = _specularIntensity;
		color = _color;
		diffuse = _diffuse;
		specular = _specular;
		n = _n;
		
	}

	@Override
	public JSONObject serializeObject() {
		JSONObject obj = new JSONObject();
		obj.put("File", file);
		obj.put("Name", name.toUpperCase());
		
		JSONObject parametersNode = new JSONObject();
		if(color != null){}
		parametersNode.put("Color", color);
		
		
		if(diffuse != null || diffuseIntensity >= 0 || diffuseTexture != null ){
			JSONObject diffuseNode = new JSONObject();
			
			if(diffuse != null){
				diffuseNode.put("Color", diffuse);
			}
			if(diffuseIntensity >= 0){
				diffuseNode.put("Intensity", diffuseIntensity);
			}
			if(diffuseTexture != null){
				diffuseNode.put("Texture", diffuseTexture.serializeObject());
			}
			
			parametersNode.put("Diffuse", diffuseNode);
		}
		
		
		if(specular != null || specularIntensity >= 0 || n >= 0 ){
			JSONObject specularNode = new JSONObject();
			
			if(diffuse != null){
				specularNode.put("Color", specular);
			}
			if(diffuseIntensity >= 0){
				specularNode.put("Intensity", specularIntensity);
			}
			if(n >= 0){
				specularNode.put("Shinieness", n);
			}
			
			parametersNode.put("Specular", specularNode);
		}
		
		
		if(ambientIntensity >= 0){
			JSONObject ambientNode = new JSONObject();
			
			ambientNode.put("Intensity", ambientIntensity);
			
			
			parametersNode.put("Ambient", ambientNode);
		}
		
		
		obj.put("Parameters", parametersNode);
		
		return obj;
	}

	@Override
	public JSONArray serializeArray() {
		return null;
	}
}
