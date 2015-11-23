/*import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Converter {

	/*public static void main(String args[]) throws IOException{
		
		String filepath = "";
		String savepath = "";
		String filename = "";
		String newFilename = "";
		String readline = "";
	    String vertices = "";
	    String uvs = "";
	    String normals = "";
	    String faces = "";
	    String groups = "";
	    int countG;
	    int stringLength = 0;
	    
	    String[] splitLine;
	    String[] splitFaces;
	    String[] splitPath;
		
		// Angabe der Datei mit Pfad
		System.out.print("Bitte gib hier die Datei an: ");
		filepath = nextLineFromKeyboard();			
		filepath.replace("\\", "\\\\");
		
		// Dateipfad lesbar machen
		splitPath = filepath.split("\\\\");
		
		
		//Speicherpfad setzen
		int splitCount = 0; 
		do{
			savepath += splitPath[splitCount] + "\\";
			splitCount++;
		}
		while(splitPath.length-1 != splitCount);
		
		//Dateinamen setzen
		filename = splitPath[splitPath.length-1];
		newFilename = stripExtension(filename) + ".sm";
		
		File file = new File(savepath + newFilename);
		FileWriter fw = new FileWriter(file);
		
		// Dateien einlesen
		FileReader fr = new FileReader(filepath);
	    BufferedReader br = new BufferedReader(fr);
		
		
		Obj_to_Sm sm = new Obj_to_Sm(fr, br);
		sm.createFile();
	}
	
	// Methode zur Extrahierung des Dateinamens ohne Endung
		static String stripExtension (String str) {
	        
			if (str == null) {
				return null;
			}
			
	        int pos = str.lastIndexOf(".");
	        
	        if (pos == -1) {
	        	return str;
	        }
	        
	        return str.substring(0, pos);
	    }
		
		/** ******************************************
		  * 
		  * Diese Hilfsmethode liest eine Zeile von der Konsole ein
		  * 
		  * @return eingelesene Zeile als String
		  * 
		  ************************************************
		public static String nextLineFromKeyboard(){
			String line = "";
			try{ BufferedReader Tast = new BufferedReader(new
				InputStreamReader(System.in));
				line = Tast.readLine();
			} catch(Exception e) { }
			return line;
		} // Ende nextLineFromKeyboard()
}*/
