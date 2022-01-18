#include "mesh.hh"

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

double **Mesh :: assemble() {
	for (int i=0; i<att_triangleList.size(); ++i)
	{
		std::cout<<*att_triangleList[i]<<std::endl;
	}
	return NULL;
}


Mesh::Mesh(std::string filename)
{
	std::vector<std::string> val;
	// define your file name
	// attach an input stream to the wanted file
	std::ifstream input_stream (filename);
	// check stream status
	if (!input_stream) std::cerr << "Can't open input file!";
	// file contents  
	std::vector<std::string> text;
	// one line
	std::string line;
	// extract all the text from the input file

	while (getline(input_stream, line)) 
	{
	    // store each line in the vector
	    text.push_back(line);
	    if (line == "$Nodes")
	    	break;
	    //std::cout<<line<<std::endl;
	}

	getline(input_stream, line);
	val = split(line, ' ');
	int jmax = stoi(val[1]);

	while(true)
	{
		getline(input_stream, line);
		if (line == "$EndNodes")
			break;
		val = split(line, ' ');

		const char* label = val[0].c_str();
		//si c'est 0 ou 1 on est au bord, sinon on est au centre
		for(int i = 0; i<stoi(val[3]); ++i)
			getline(input_stream, line);//On fait sauter les nodes ID
		int iterations = stoi(val[3]);
		for(int i = 0; i<iterations; ++i)
		{
			bool isBorder = (*label!='2');
			getline(input_stream, line);
			val = split(line, ' ');
			att_pointList.push_back(new Point(stod(val[0]), stod(val[1]), isBorder));

		}
	}

	getline(input_stream, line);
	getline(input_stream, line);
	val = split(line, ' ');
	getline(input_stream, line);
	int i_init = stoi(val[2]);
	int i_max  = stoi(val[3]);


	for (int i = i_init; i <= i_max; ++i)
	{
		getline(input_stream, line);
		val = split(line, ' ');
		att_triangleList.push_back(new Triangle(att_pointList[stoi(val[1])-1], att_pointList[stoi(val[2])-1], att_pointList[stoi(val[3])-1]));
	}
}