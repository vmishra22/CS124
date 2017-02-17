#include <iostream>
#include <sstream>

using namespace std;
int main(int argc, char** argv) {
	if (argc != 5){
		cout << "Incorrect input args list" << endl;
	}
	
	istringstream ss1(argv[2]);
	int numPoints;
	if (!(ss1 >> numPoints))
		cerr << "Invalid number for numPoints" << argv[2] << '\n';

	istringstream ss2(argv[3]);
	int numTrials;
	if (!(ss2 >> numTrials))
		cerr << "Invalid number for numTrials" << argv[3] << '\n';

	istringstream ss3(argv[4]);
	int dimension;
	if (!(ss3 >> dimension))
		cerr << "Invalid number for dimension" << argv[4] << '\n';

	return 0;
}