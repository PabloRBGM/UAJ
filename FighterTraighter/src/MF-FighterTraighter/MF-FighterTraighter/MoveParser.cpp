#include "MoveParser.h"
#include <fstream>

std::vector<AnimationChain*> MoveParser::parseFile(string filePath)
{
	fstream stream = fstream(filePath);
	if (stream.is_open()) {
		std::vector<AnimationChain*> chains;
		string str = "";
		getline(stream, str, '\n');
		while (str != "0") {
			std::vector<Move*> mov;
			getline(stream, str, '\n');
			
			while (str != "0") {
				mov.push_back(new Move(std::stoi(str), nullptr, nullptr, nullptr));
				getline(stream, str, '\n'); //habrá que ver cómo pasamos de string a callback AAAAAAAAAAAAAA NO SÉ CÓMO
				getline(stream, str, '\n');
			}
			chains.push_back(new AnimationChain(mov));
			getline(stream, str, '\n');
		}
		stream.close();
		return chains;
	}
	else {
		//crashialo
	}
}
