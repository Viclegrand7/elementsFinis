#include "triangle.hh"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

long long Point :: globalId = -1;

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}


void open_file()
{
	std::vector<std::string> val;
	// define your file name
	// attach an input stream to the wanted file
	std::ifstream input_stream ("./square.msh");
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

	while (line != "$EndNodes")
	{
		getline(input_stream, line);
		val = split(line, ' ');
		if (val.size() == 4)
		{
			const char* label = val[0].c_str();
			//si c'est 0 ou 1 on est au bord, sinon on est au centre
			for(int i = 0; i<stoi(val[3]); ++i)
				getline(input_stream, line);
			int iterations = stoi(val[3]);
			for(int i = 0; i<iterations; ++i)
			{
				bool isBorder = (*label!='2');
				getline(input_stream, line);
				val = split(line, ' ');
				Point tmp(stod(val[0]), stod(val[1]), isBorder);
				std::cout<<tmp<<std::endl;
			}
		}

	}

}


int main() {
	Point a(1,2,3);
	Point b(2,3,4);
	Point c(3,4,5);
	Triangle test(&a,&b,&c);
	open_file();
	std :: cout << test[1]->getId() << std :: endl;
}