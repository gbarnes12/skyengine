package Convert;

import java.io.FileWriter;
import java.io.IOException;

import toJSON.Model;

public class Exporter {
	private Model model;
	
	public Exporter(Model _model)
	{
		model = _model;
	}
	
	public void saveModel(String path) throws Exception
	{
		if(model == null)
			throw new Exception("Invalid model");
			
		try { 
			FileWriter file = new FileWriter(path);
			file.write(model.serializeObject().toJSONString());
			file.flush();
			file.close();
	 
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
