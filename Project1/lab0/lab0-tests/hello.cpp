    #include <iostream>
	#include <sstream>
	#include <fstream>
	#include <cctype>
using namespace std;
     int main(int argc, char* argv[]) {
		//cout << "argc: " << argc << endl;
		//cout << "argv[0]: " << argv[0] << endl;
		//cout << "argv[1]: " << argv[1] << endl;
		//cout << "*** Start of Input ***" << endl;
		string filename = argv[1];
		ifstream in;
		in.open(filename);
		stringstream ss;
		ss << in.rdbuf();
		string input = ss.str();
		
		//cout << input << endl;
		//cout << "*** End of Input ***" << endl;


		int char_count = 0, line_count = 0, space_count = 0, digit_count = 0, letter_count = 0;
		for (int i = 0; i < input.length(); i++) { 
			if (isspace(input[i])) {
		
				space_count++;
			} else if (isdigit(input[i])){
				
				digit_count++;
			} else if (isalpha(input[i])){
				
				letter_count++;
			}
			if (input[i] == '\n'){
				
				line_count++;
			}
			char_count++;
		}


		cout << "chars: " << char_count << endl;
		cout << "lines: " << line_count << endl;
		cout << "spaces: " << space_count << endl;
		cout << "digits: " << digit_count << endl;
		cout << "letters: " << letter_count << endl;
		
		in.close();

}
