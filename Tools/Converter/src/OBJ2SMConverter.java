import java.io.IOException;

import Convert.Exporter;
import Convert.Importer;


public class OBJ2SMConverter 
{
	public static void main(String args[])
	{
		Importer importer = new Importer("C:\\Users\\Gavin Barnes\\Desktop\\cube.obj");
		try {
			importer.importFile();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		System.out.println("Finished importing and converting.");
		
		Exporter exporter = new Exporter(importer.getModel());
		try {
			exporter.saveModel("C:\\Users\\Gavin Barnes\\Desktop\\cube.json");
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println("Finished exporting.");
	}
}
