package Convert;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import toJSON.Face;
import toJSON.Mesh;
import toJSON.Model;
import toJSON.Vertex;

public class Importer {
	
	private Model model;
	private HashMap<String, Mesh> meshes;
	private String path;
	private ArrayList<String[]> fileInArray;
	List<double[]> vertices = new LinkedList<double[]>(); 
    List<double[]> uvs = new LinkedList<double[]>(); 
    List<double[]> normals = new LinkedList<double[]>(); 
    Mesh lastMesh = null;
    
	public Importer(String _path) {
		path = _path;
		meshes = new HashMap<String, Mesh>();
		
		fileInArray = new ArrayList<String[]>();
	}
	
	public void importFile() throws IOException {
		setFileInArray();
	    
	    model = new Model(getModelName());
	    
	    for(int i = 0; i < fileInArray.size(); i++){
	    	String[] line = fileInArray.get(i);
	    	
	    	// start parsing group elements 
	    	// to create mesh group 
	    	parseGroup(line, i);
	    	
	    	// parse vertices
	    	parseVertices(line, vertices);
	    	
	    	// parse normals
	    	parseUV(line, uvs);    	
	    	
	    	// parse uvs
	    	parseNormals(line, normals);
	    	
	    	// parse faces
	    	parseFaces(line, lastMesh);
	    	
	    }
	    Object[] collection = meshes.values().toArray();
	    for(int i = 0; i < collection.length; i++) {
	    	model.addMesh((Mesh)collection[i]);
	    }
	    
	}
	
	private void parseFaces(String[] _line, Mesh _mesh) {
		String[] vertex1 = null;
		String[] vertex2 = null;
		String[] vertex3 = null;
		
		try {
			if(_mesh != null) {
				if(_line[0].equals("f")) {
					if(_line.length == 4) {
						vertex1 = _line[1].split("/");
						vertex2 = _line[2].split("/");
						vertex3 = _line[3].split("/");
						
						if(vertex1.length >= 3 && vertex2.length >= 2 && vertex3.length >= 3) {
							if(vertices.size() > 0 && uvs.size() > 0 && normals.size() > 0) {
								double[] v1_pos = vertices.get(Integer.parseInt(vertex1[0])-1); 
								double[] v1_uv = uvs.get(Integer.parseInt(vertex1[1])-1);
								double[] v1_normal = normals.get(Integer.parseInt(vertex1[2])-1);
								
								double[] v2_pos = vertices.get(Integer.parseInt(vertex2[0])-1); 
								double[] v2_uv = uvs.get(Integer.parseInt(vertex2[1])-1);
								double[] v2_normal = normals.get(Integer.parseInt(vertex2[2])-1);
								
								double[] v3_pos = vertices.get(Integer.parseInt(vertex3[0])-1); 
								double[] v3_uv = uvs.get(Integer.parseInt(vertex3[1])-1);
								double[] v3_normal = normals.get(Integer.parseInt(vertex3[2])-1);
								
								Vertex v1 = new Vertex(v1_pos, v1_uv, v1_normal);
								Vertex v2 = new Vertex(v2_pos, v2_uv, v2_normal);
								Vertex v3 = new Vertex(v3_pos, v3_uv, v3_normal);
								
								Face f = new Face(v1, v2, v3);
								_mesh.addFace(f);
							}
						}
					}
				}
			}
		}
		catch(Exception e)
		{
			System.out.println("Blabla");
		}
	}

	private void setFileInArray() throws IOException{
		FileReader fr = new FileReader(path);
	    BufferedReader br = new BufferedReader(fr);
	    
	    String readline = "";
	    while ((readline = br.readLine()) != null) {
	    	String splitLine[] = readline.split(" ");
	    	fileInArray.add(splitLine);
	    }
	    br.close();
	    fr.close();
	}
	
	public void parseVertices(String[] _line, List<double[]> _vertices){
		if(_line[0].equals("v")){
    		if(_line.length == 4){
    			double[] vertices = { Double.parseDouble(_line[1]), Double.parseDouble(_line[2]), Double.parseDouble(_line[3]) };
    			_vertices.add(vertices);
    		}
    	}	
	}
	
	public void parseUV(String[] _line, List<double[]> _uv){
		if(_line[0].equals("vt")){
    		if(_line.length == 3){
    			double[] uvs = { Double.parseDouble(_line[1]), Double.parseDouble(_line[2]) };
    			_uv.add(uvs);
    		}
    	}
	}
	
	public void parseNormals(String[] _line, List<double[]> _normal){
		if(_line[0].equals("vn")){
    		if(_line.length == 4){
    			double[] normals = { Double.parseDouble(_line[1]), Double.parseDouble(_line[2]), Double.parseDouble(_line[3]) };
    			_normal.add(normals);
    		}
    	}
	}
	
	private void parseGroup(String[] _line, int _i) {
		String[] nextLine = null;
		int j = _i;
    	j++;
  
		if (_line[0].equals("g")){
    		boolean isGroup = false;
    		for(int k = _i; k < j+5; k++){
    			if(k < fileInArray.size()-1){
    				nextLine = fileInArray.get(k);
    			
		    		// Prüfe ob nächste zeile kein Vektor ist
		    		if(nextLine[0].equals("f")){
		    			isGroup = true;
		    			break;
		    		}
    			}
    		}
    		
    		if(isGroup){
    			Mesh mesh = new Mesh(_line[1]);
    			meshes.put(_line[1], mesh);
    			lastMesh = mesh;
    		}
    	}
	}
	
	//Entferne Dateiendung vom File
	private String getModelName(){
		String splitPath[];
		
		path.replace("\\", "\\\\");
		 
		
		splitPath = path.split("\\\\");
		String filename = splitPath[splitPath.length-1];
		filename = stripExtension(filename);
	    
		return filename;
	}
	
	//Entferne Dateipfad vom Path
	private String stripExtension (String str) {
        
		if (str == null) {
			return null;
		}
		
        int pos = str.lastIndexOf(".");
        
        if (pos == -1) {
        	return str;
        }
        
        return str.substring(0, pos);
    }
	
	
	public Model getModel() {
		return model;
	}
}
