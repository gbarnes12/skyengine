using skyConverter.ModelStructure;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skyConverter.Importers
{
    class OBJImporter : Importer
    {
        private List<String[]> _fileInArray;
        BackgroundWorker _backgroundWorker;

        public OBJImporter(String _path, BackgroundWorker backgroundWorker)
            : base(_path)
        {
            _fileInArray = new List<String[]>();
            _backgroundWorker = backgroundWorker;
        }

        public override void Import()
        {
            setFileInArray();

            _backgroundWorker.ReportProgress(10);

            for (int i = 0; i < _fileInArray.Count; i++)
            {
                String[] line = _fileInArray[i];

                // start parsing group elements 
                // to create mesh group 
                parseGroup(line, i);

                // parse vertices
                parseVertices(line, _vertices);

                // parse normals
                parseUV(line, _uvs);

                // parse uvs
                parseNormals(line, _normals);

                // parse faces
                parseFaces(line, _lastMesh);
            }

            _backgroundWorker.ReportProgress(50);


            if (this.isMultipart)
                this.SetupMultipart();
            else
                this.SetupSinglepart();
 
            _backgroundWorker.ReportProgress(55);
        }

        private void SetupMultipart()
        {
            int countModels = (int)Math.Round(((decimal)_meshes.Count / 1), 0, MidpointRounding.AwayFromZero);
            for (int i = 0; i < countModels; i++)
            {
                this._models.Add(new Model(getModelName()));
                this._models[i].setIsMultipart(true);
                this._models[i].setNumberOfPart(i + 1);
                this._models[i].setNumberOfParts(countModels);
            }


            int currentMesh = 0;
            Mesh[] meshesArray = _meshes.Values.ToArray();

            foreach (Model m in _models)
            {
                int meshesNum = 0;
                for (int i = currentMesh; i < currentMesh + 2; i++)
                {
                    meshesArray[i].SetCountVertices();
                    m.addMesh(meshesArray[i]);
                    meshesNum = i;
                }

                currentMesh = meshesNum;
            }
        }

        private void SetupSinglepart()
        {
            this._models.Add(new Model(getModelName()));

            foreach (KeyValuePair<string, Mesh> mesh in _meshes)
            {
                mesh.Value.SetCountVertices();
                this._models[0].addMesh(mesh.Value);
            }
        }

        private void parseFaces(String[] _line, Mesh _mesh)
        {
            String[] vertex1 = null;
            String[] vertex2 = null;
            String[] vertex3 = null;


            if (_mesh != null)
            {
                if (_line[0].Equals("f"))
                {
                    if (_line.Length == 4)
                    {
                        vertex1 = _line[1].Split('/');
                        vertex2 = _line[2].Split('/');
                        vertex3 = _line[3].Split('/');

                        if (vertex1.Length >= 3 && vertex2.Length >= 2 && vertex3.Length >= 3)
                        {
                            if (_vertices.Count > 0 && _uvs.Count > 0 && _normals.Count > 0)
                            {
                                double[] v1_pos = _vertices[(int.Parse(vertex1[0]) - 1)];
                                double[] v1_uv = _uvs[(int.Parse(vertex1[1]) - 1)];
                                double[] v1_normal = _normals[(int.Parse(vertex1[2]) - 1)];

                                double[] v2_pos = _vertices[(int.Parse(vertex2[0]) - 1)];
                                double[] v2_uv = _uvs[(int.Parse(vertex2[1]) - 1)];
                                double[] v2_normal = _normals[(int.Parse(vertex2[2]) - 1)];

                                double[] v3_pos = _vertices[(int.Parse(vertex3[0]) - 1)];
                                double[] v3_uv = _uvs[(int.Parse(vertex3[1]) - 1)];
                                double[] v3_normal = _normals[(int.Parse(vertex3[2]) - 1)];

                                Vertex v1 = new Vertex(v1_pos, v1_uv, v1_normal);
                                Vertex v2 = new Vertex(v2_pos, v2_uv, v2_normal);
                                Vertex v3 = new Vertex(v3_pos, v3_uv, v3_normal);

                                Face f = new Face(v1, v2, v3);
                                _mesh.AddFace(f);
                            }
                        }
                    }
                }
            }
        }

        private void setFileInArray()
        {
            StreamReader streamReader = new StreamReader(_filePath);

            String line = "";
            while ((line = streamReader.ReadLine()) != null)
            {
                String[] splitLine = line.Split(' ');
                _fileInArray.Add(splitLine);
            }

            streamReader.Close();
        }

        public void parseVertices(String[] _line, List<double[]> _vertices)
        {
            if (_line[0].Equals("v"))
            {
                if (_line.Length == 4)
                {
                    double[] vertices = { Double.Parse(_line[1], CultureInfo.InvariantCulture), Double.Parse(_line[2], CultureInfo.InvariantCulture), Double.Parse(_line[3], CultureInfo.InvariantCulture) };
                    _vertices.Add(vertices);
                }
            }
        }

        public void parseUV(String[] _line, List<double[]> _uv)
        {
            if (_line[0].Equals("vt"))
            {
                if (_line.Length == 3)
                {
                    double[] uvs = { Double.Parse(_line[1], CultureInfo.InvariantCulture), Double.Parse(_line[2], CultureInfo.InvariantCulture) };
                    _uv.Add(uvs);
                }
            }
        }

        public void parseNormals(String[] _line, List<double[]> _normal)
        {
            if (_line[0].Equals("vn"))
            {
                if (_line.Length == 4)
                {
                    double[] normals = { Double.Parse(_line[1], CultureInfo.InvariantCulture), Double.Parse(_line[2], CultureInfo.InvariantCulture), Double.Parse(_line[3], CultureInfo.InvariantCulture) };
                    _normal.Add(normals);
                }
            }
        }

        private void parseGroup(String[] _line, int _i)
        {
            String[] nextLine = null;
            int j = _i;
            j++;

            if (_line[0].Equals("g"))
            {
                bool isGroup = false;
                for (int k = _i; k < j + 5; k++)
                {
                    if (k < _fileInArray.Count - 1)
                    {
                        nextLine = _fileInArray[k];

                        // Prüfe ob nächste zeile kein Vektor ist
                        if (nextLine[0].Equals("f"))
                        {
                            isGroup = true;
                            break;
                        }
                    }
                }

                if (isGroup)
                {
                    Mesh mesh = new Mesh(_line[1]);
                    _meshes.Add(_line[1], mesh);
                    _lastMesh = mesh;
                }
            }
        }

        //Entferne Dateiendung vom File
        private String getModelName()
        {
            String[] splitPath;

            _filePath.Replace("\\", "\\\\");

            char[] delimeter = new char[] { '\\', '\\', '\\', '\\' };
            splitPath = _filePath.Split(delimeter);

            String filename = splitPath[splitPath.Length - 1];
            filename = stripExtension(filename);

            return filename;
        }

        //Entferne Dateipfad vom Path
        private String stripExtension(String str)
        {

            if (str == null)
            {
                return null;
            }

            int pos = str.LastIndexOf(".");

            if (pos == -1)
            {
                return str;
            }

            return str.Substring(0, pos);
        }
    }
}
