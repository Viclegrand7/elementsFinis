#include "mesh.hh"

#define dirichlet_hot_condition 24
#define dirichlet_cold_condition 5

/*
double f(double x, double y) {
	return 2 * M_PI * M_PI * sin(M_PI * x) * sin(M_PI * y);
}
*/

double f(double x, double y) {
	return 2 * M_PI * M_PI * sin(M_PI * x) * cos(M_PI * y);
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

void Mesh :: GNUPlotExport(const std :: string &fileName){
	std::ofstream myfile;
  myfile.open (fileName); 
  for (unsigned int i = 0; i < att_pointList.size(); ++i)
  {
  	double value = 0.0;
		long long ddl = att_pointList[i]->getDdl();
		unsigned char border = att_pointList[i]->borderType();
		if ((border == BORDER_NO_CONDITION) || (border == BORDER_NEUMANN))
			value = (*att_X)(ddl);
		else if (border == BORDER_DIRICHLET_COLD)
			value = dirichlet_cold_condition;
		else
			value = dirichlet_hot_condition;
  	myfile << att_pointList[i]->getX() << " " << att_pointList[i]->getY() << " " << value << std::endl;
  }
  std :: cout << "Exported for GNUPlot" << std :: endl;
  return;
}

void Mesh :: ParaviewExport(const std :: string &fileName){
	std::ofstream myfile;
  myfile.open (fileName); 
  myfile << "x,y,val" << std::endl;
  for (unsigned int i = 0; i < att_pointList.size(); ++i)
  {
  	double value = 0.0;
		long long ddl = att_pointList[i]->getDdl();
		unsigned char border = att_pointList[i]->borderType();
		if (border == BORDER_NO_CONDITION || border == BORDER_NEUMANN)
			value = (*att_X)(ddl);
		else if (border == BORDER_DIRICHLET_COLD)
			value = dirichlet_cold_condition;
		else
			value = dirichlet_hot_condition;
  	myfile << att_pointList[i]->getX() << "," << att_pointList[i]->getY() << "," << value << std::endl;
  }
  std :: cout << "Exported for Paraview" << std :: endl;
  return;
}

void Mesh :: assemble() {
	std :: cout << "freedomDegrees detected: " << att_freedomDegrees << std :: endl;
	if (att_A)
		delete att_A;
	if (att_F)
		delete att_F;
	att_A = new Eigen :: SparseMatrix <double> (att_freedomDegrees, att_freedomDegrees);
	att_F = new Eigen :: VectorXd(att_freedomDegrees);

	std :: vector<Eigen :: Triplet<double>> contributions;
	for (std :: vector <Triangle *> :: iterator triangle = att_triangleList.begin() ; triangle != att_triangleList.end() ; ++triangle) {
		for (unsigned int i = 0 ; i < 3 ; ++i) {
			long long I = (**triangle)[i]->getDdl();
			if (I == -1)
				continue;
			for (unsigned int j = 0 ; j < 3 ; ++j) {
				{
					double x = (*triangle)->middleOpposedX(j);
					double y = (*triangle)->middleOpposedY(j);
					(*att_F)(I) += f(x, y) * (*triangle)->phi(x, y, i) * (*triangle)->getSurface() / 3;
				}
				long long J = (**triangle)[j]->getDdl();
				if (J == -1) {
					std :: vector<double> first((*triangle)->gradPhi(i));
					std :: vector<double> second((*triangle)->gradPhi(j));
					if ((**triangle)[j]->borderType() == BORDER_DIRICHLET_COLD)
						(*att_F)(I) -= dirichlet_cold_condition * (*triangle)->getSurface() * std :: inner_product(first.begin(), first.end(), second.begin(), 0);
					else
						(*att_F)(I) -= dirichlet_hot_condition * (*triangle)->getSurface() * std :: inner_product(first.begin(), first.end(), second.begin(), 0);
					continue;
				}
				std :: vector<double> first((*triangle)->gradPhi(i));
				std :: vector<double> second((*triangle)->gradPhi(j));
				contributions.push_back(Eigen :: Triplet<double>((**triangle)[i]->getDdl(), (**triangle)[j]->getDdl(), (*triangle)->getSurface() * std :: inner_product(first.begin(), first.end(), second.begin(), 0)));
//				std :: cout << (**triangle)[i]->getDdl() << '\t' << (**triangle)[j]->getDdl() << "\t\t" << std :: inner_product(first.begin(), first.end(), second.begin(), 0) << std :: endl;
			}
		}
	}
//				for (unsigned int i = 0 ; i < contributions.size() ; ++i)
//					std :: cout << contributions[i].col() << "\t" << contributions[i].row() << "\t" << contributions[i].value() << std :: endl;

	att_A->setFromTriplets(contributions.begin(), contributions.end());
//					std :: cout << "A = " << *att_A << std :: endl;
//					std :: cout << "F = " << *att_F << std :: endl;
	std :: cout << "Done assembling" << std :: endl;
}

void Mesh :: solve() {
	if (att_X)
		delete att_X;
	att_X = new Eigen :: VectorXd(att_freedomDegrees);
	Eigen :: ConjugateGradient<Eigen :: SparseMatrix<double>, Eigen :: Lower | Eigen :: Upper> solver;
	solver.compute(*att_A);
	*att_X = solver.solve(*att_F);
	std :: cout << "Solved";
//	std :: cout << ". X = " << *att_X;
	std :: cout << std :: endl;
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
	//On load les points
	int iter = stoi(val[0]);
	for (int i = 0; i < iter; ++i)
	{
		getline(input_stream, line);
		val = split(line, ' ');
		att_pointList.push_back(new Point(stod(val[1]), stod(val[2]), BORDER_NO_CONDITION));
		att_isNeumann.push_back(false);
		++att_freedomDegrees;
	}
	//On skip $EndNodes
	getline(input_stream, line);
  //On skip $Elements
	getline(input_stream, line);
	//On load le nombre d'elements
	getline(input_stream, line);
	val = split(line, ' ');
	iter = stoi(val[0]);
	for (int i = 0; i < iter; ++i)
	{
		getline(input_stream, line);
		val = split(line, ' ');
		if (val[1] == "1")
		{
			//On est sur un bord, on va update les labels des points en fonction des conditions de bord
			//Le label est dans val[3], on peut définir ce qu'on veut
			if (val[3] == "97"){//On set le label des points val[5] et val[6] à Dirichlet
				if (att_pointList[stoi(val[5])-1]->setBorderType(BORDER_DIRICHLET_COLD))
					decreaseDdlFromPoint(stoi(val[5]) - 1);
				if (att_pointList[stoi(val[6])-1]->setBorderType(BORDER_DIRICHLET_COLD))
					decreaseDdlFromPoint(stoi(val[6]) - 1);
			}
			if (val[3] == "98"){//On set le label des points val[5] et val[6] à Dirichlet
				if (att_pointList[stoi(val[5])-1]->setBorderType(BORDER_DIRICHLET_HOT))
					decreaseDdlFromPoint(stoi(val[5]) - 1);
				if (att_pointList[stoi(val[6])-1]->setBorderType(BORDER_DIRICHLET_HOT))
					decreaseDdlFromPoint(stoi(val[6]) - 1);
			}
			else if (val[3] == "99"){//On set le label des points val[5] et val[6] à Neumann
				att_pointList[stoi(val[5])-1]->setBorderType(BORDER_NEUMANN);
				att_pointList[stoi(val[6])-1]->setBorderType(BORDER_NEUMANN);
			}
		}
		else if (val[1] == "2")
		{
			att_triangleList.push_back(new Triangle(att_pointList[stoi(val[5])-1], att_pointList[stoi(val[6])-1], att_pointList[stoi(val[7])-1]));
			//On définit un triangle
		}
	}
}

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


void Mesh :: decreaseDdlFromPoint(unsigned int figure) {
	if (att_isNeumann[figure])
		return;
	att_isNeumann[figure] = 1;
	--att_freedomDegrees;
	--Point :: globalDdl;
	att_pointList[figure]->deleteDdl();
	for (++figure; figure < att_pointList.size() ; ++figure)
		att_pointList[figure]->decreaseDdl();
}
/*
double realSolutionSquare(double x, double y) {
	return sin(M_PI * x) * sin(M_PI * y);
}
*/
double realSolutionSquare(double x, double y) {
	return sin(M_PI * x) * cos(M_PI * y);
}

double Mesh :: computeError() {
	double squaredError(0.);
	std :: vector <double> deltaU(3);
	for (std :: vector <Triangle *> :: iterator triangle = att_triangleList.begin() ; triangle != att_triangleList.end() ; ++triangle) {
		std :: vector <double> tmpArray(2);
		for (int i = 0 ; i < 3 ; ++i) {
			long long I = (**triangle)[i]->getDdl();
			if (I == -1)
				continue;
			deltaU[i] = realSolutionSquare((**triangle)[i]->getX(), (**triangle)[i]->getY()) - (*att_X)[I];
			std :: vector <double> purelyTmpArray((*triangle)->gradPhi(i));
			tmpArray[0] += purelyTmpArray[0] * deltaU[i];
			tmpArray[1] += purelyTmpArray[1] * deltaU[i];
		}
		squaredError += (*triangle)->getSurface() * std :: inner_product(tmpArray.begin(), tmpArray.end(), tmpArray.begin(), 0);
	}
	return sqrt(squaredError);
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
