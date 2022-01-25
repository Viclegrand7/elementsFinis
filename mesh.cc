#include "mesh.hh"

double f(double x, double y) {
	return x + y;
}

std :: vector<std :: string> split (const std :: string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
void Mesh :: VTKExport()
{
	return ;
}
void Mesh :: assemble() {
	if (att_A)
		delete att_A;
	if (att_F)
		delete att_F;
	att_A = new Eigen :: SparseMatrix <double> (att_freedomDegrees, att_freedomDegrees);
	att_F = new Eigen :: VectorXd(att_freedomDegrees);

	std :: cout << "freedom degrees: " << att_freedomDegrees << std :: endl;
	std :: cout << Point :: globalDdl << std :: endl;

	std :: vector<Eigen :: Triplet<double>> contributions;
	for (auto triangle = att_triangleList.begin() ; triangle != att_triangleList.end() ; ++triangle) {
		for (unsigned int i = 0 ; i < 2 ; ++i) {
			unsigned char I = (**triangle)[i]->borderType();
			if (I != BORDER_NO_CONDITION)
				continue;
			for (unsigned int j = 0 ; j < 2 ; ++j) {
				{
					double x = (*triangle)->middleOpposedX(j);
					double y = (*triangle)->middleOpposedY(j);
					(*att_F)((**triangle)[i]->getDdl()) += f(x, y) * (*triangle)->phi(x, y, i) * (*triangle)->surface() / 3;
				}
				unsigned char J = (**triangle)[j]->borderType();
				if (J != BORDER_NO_CONDITION)
					continue;
				contributions.push_back(Eigen :: Triplet<double>((**triangle)[i]->getDdl(), (**triangle)[j]->getId(), (*triangle)->gradPhi(i) * (*triangle)->gradPhi(j)));
			}
		}
	}
	att_A->setFromTriplets(contributions.begin(), contributions.end());
	std :: cout << "finito pipo" << std :: endl;
}

Mesh :: Mesh(std :: string filename) : att_freedomDegrees(0), att_A(NULL), att_F(NULL), att_X(NULL) {
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
//	int jmax = stoi(val[1]);

	while(true)
	{
		getline(input_stream, line);
		if (line == "$EndNodes")
			break;
		val = split(line, ' ');

		const char* label = val[0].c_str();		// char label = val[0] ; //Plus simple non ?
		//si c'est 0 ou 1 on est au bord, sinon on est au centre
		for(int i = 0; i<stoi(val[3]); ++i)
			getline(input_stream, line);//On fait sauter les nodes ID
		int iterations = stoi(val[3]);
		for(int i = 0; i<iterations; ++i)
		{
			bool isBorder = (*label!='2');
			getline(input_stream, line);
			val = split(line, ' ');
//			att_pointList.push_back(new Point(stod(val[0]), stod(val[1]), isBorder));
							att_pointList.push_back(new Point(stod(val[0]), stod(val[1]), '2' - *label));
							att_freedomDegrees += !isBorder; //ZNGIZEIGBZEIGIUEZGIZEGG IL FAUDRA LE CHANGER
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

Mesh :: ~Mesh() {
	if (att_A)
		delete att_A;
	if (att_F)
		delete att_F;
	if (att_X)
		delete att_X;
	for (unsigned int i = 0 ; i < att_pointList.size() ; ++i)
		delete att_pointList[i];
	for (unsigned int i = 0 ; i < att_triangleList.size() ; ++i)
		delete att_triangleList[i];
}