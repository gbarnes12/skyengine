/*import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class Obj_to_Sm {
	
	FileReader fr;
	BufferedReader br;
	
	public Obj_to_Sm(FileReader f, BufferedReader b){
		fr = f;
		br = b;
	}
	
	public void createFile() throws IOException{
		
		String filepath = "";
		String savepath = "";
		String filename = "";
		String newFilename = "";
		String readline = "";
	    String vertices = "";
	    String uvs = "" +
	    		"";
	    String normals = "";
	    String faces = "";
	    String groups = "";
	    int countG;
	    int stringLength = 0;
	    
	    String[] splitLine;
	    String[] splitFaces;
	    String[] splitPath;
		
	    JSONArray meshes = new JSONArray();
		JSONArray list2 = new JSONArray();
		JSONObject obj = new JSONObject();
		// Alle Zeilen der Datei auslesen
	    while ((readline = br.readLine()) != null) {
		    splitLine = readline.split(" ");
		    
	    }
		
		list2.add("ID2");
		
		
        obj.put("Name", "Name");
        obj.put("Vertices", list2);
		
		
		meshes.add(obj);
		meshes.add("msg 2");
		meshes.add("msg 3");
	 
		try {
	 
			FileWriter file = new FileWriter("C:\\Users\\drotzsche\\Desktop\\test.json");
			file.write("\"Meshes\" : " + meshes.toJSONString());
			file.flush();
			file.close();
	 
		} catch (IOException e) {
			e.printStackTrace();
		}
	 
		System.out.print("\"Meshes\" : " + meshes);
 	}
}*/
