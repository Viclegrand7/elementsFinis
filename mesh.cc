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

void Mesh :: VTKExport(const std :: string &fileName){
	unsigned int dimension_ = 2;
//	Timer t;
	vtkUnstructuredGrid *Grid                 = vtkUnstructuredGrid::New();
	vtkPoints *pointSet                       = vtkPoints::New();
	vtkDoubleArray *wtfIsThis                 = vtkDoubleArray::New();
	vtkXMLUnstructuredGridWriter* outputFile  = vtkXMLUnstructuredGridWriter::New();

	wtfIsThis->SetNumberOfComponents(1);
	wtfIsThis->SetNumberOfTuples(att_triangleList.size());

	for (unsigned int i = 0; i < att_pointList.size(); ++i)
	{
		double value = 0.0;
		long long ddl = att_pointList[i]->getDdl();
		if (ddl != -1)
			value = (*att_X)(ddl);
		double tmp[] = {att_pointList[i]->getX(), att_pointList[i]->getY(), 0.0, value};
		pointSet->InsertNextPoint(tmp);
		wtfIsThis->SetTuple(i, tmp + 3);
	}

	Grid->Allocate();
	Grid->SetPoints(pointSet); 
	for (unsigned int i = 0; i < att_triangleList.size(); ++i) {
		long long int tmp[]  = {(*(att_triangleList[i]))[0]->getId(), (*(att_triangleList[i]))[1]->getId(), (*(att_triangleList[i]))[2]->getId()};
		Grid->InsertNextCell(dimension_== 2 ? VTK_TRIANGLE : VTK_TETRA, dimension_+1, tmp);
	}
	(*(*Grid).GetPointData()).SetScalars(wtfIsThis);

	outputFile->SetFileName(fileName.c_str());
	outputFile->SetInputData(Grid);
	outputFile->Write();

	Grid->Delete();
	pointSet->Delete();
	wtfIsThis->Delete();
	outputFile->Delete();

//	cout << "[Importer] VTK triangulation written in "
//	<< t.getElapsedTime() << " s." << endl;

	return ;
}

void Mesh :: assemble() {
	if (att_A)
		delete att_A;
	if (att_F)
		delete att_F;
	att_A = new Eigen :: SparseMatrix <double> (att_freedomDegrees, att_freedomDegrees);
	att_F = new Eigen :: VectorXd(att_freedomDegrees);

	std :: vector<Eigen :: Triplet<double>> contributions;
	for (std :: vector <Triangle *> :: iterator triangle = att_triangleList.begin() ; triangle != att_triangleList.end() ; ++triangle) {
		for (unsigned int i = 0 ; i < 3 ; ++i) {
			unsigned char I = (**triangle)[i]->borderType();
			if (I != BORDER_NO_CONDITION)
				continue;
			for (unsigned int j = 0 ; j < 3 ; ++j) {
				{
					double x = (*triangle)->middleOpposedX(j);
					double y = (*triangle)->middleOpposedY(j);
					(*att_F)((**triangle)[i]->getDdl()) += f(x, y) * (*triangle)->phi(x, y, i) * (*triangle)->getSurface() / 3;
				}
				unsigned char J = (**triangle)[j]->borderType();
				if (J != BORDER_NO_CONDITION)
					continue;
				std :: vector<double> first((*triangle)->gradPhi(i));
				std :: vector<double> second((*triangle)->gradPhi(j));
				contributions.push_back(Eigen :: Triplet<double>((**triangle)[i]->getDdl(), (**triangle)[j]->getDdl(), std :: inner_product(first.begin(), first.end(), second.begin(), 0)));
//				std :: cout << (**triangle)[i]->getDdl() << '\t' << (**triangle)[j]->getDdl() << "\t\t" << std :: inner_product(first.begin(), first.end(), second.begin(), 0) << std :: endl;
			}
		}
	}
	att_A->setFromTriplets(contributions.begin(), contributions.end());
					std :: cout << *att_A << std :: endl;
					std :: cout << *att_F << std :: endl;
	std :: cout << "Done assembling" << std :: endl;
}

void Mesh :: solve() {
	if (att_X)
		delete att_X;
	att_X = new Eigen :: VectorXd(att_freedomDegrees);
	Eigen :: ConjugateGradient<Eigen :: SparseMatrix<double>, Eigen :: Lower | Eigen :: Upper> solver;
	solver.compute(*att_A);
	*att_X = solver.solve(*att_F);
	std :: cout << "Solved" << std :: endl;
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

		char label = val[0].front();
		//si c'est 0 ou 1 on est au bord, sinon on est au centre
		for(int i = 0; i<stoi(val[3]); ++i)
			getline(input_stream, line);//On fait sauter les nodes ID
		int iterations = stoi(val[3]);
		for(int i = 0; i<iterations; ++i)
		{
			bool isBorder = (label!='2');
			getline(input_stream, line);
			val = split(line, ' ');
			att_pointList.push_back(new Point(stod(val[0]), stod(val[1]), '2' - label));
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

/*
void Mesh :: test() {
	std :: vector<Eigen :: Triplet<double>> contributions;

	unsigned int bidule(0);
	for (std :: vector <Triangle *> :: iterator triangle = att_triangleList.begin() ; triangle != att_triangleList.end() ; ++triangle, ++bidule) {
		for (unsigned int i = 0 ; i < 3 ; ++i) {
			for (unsigned int j = 0 ; j < 3 ; ++j) {
				assert((*triangle)->phi(((**triangle)[i])->getX(), ((**triangle)[i])->getY(), j) == (i == j));
			}
		}
	}
}
*/

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
