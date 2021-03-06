#include<iostream>
using std::cout;
using std::cerr;
using std::move;
using std::endl;

#include<fstream>
using std::ios;
using std::ios_base;
using std::ifstream;
using std::ofstream;

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<algorithm>
using std::sort;
using std::find_if;

#include<windows.h>

// gets string literals from file
vector<string> get_string_literals(const string& filename) {
	vector<string> result;

	ifstream file(filename);
	if (file.is_open()) {
		for (string literal; getline(file, literal);) {
			if (find_if(result.begin(), result.end(), [&](string& s) -> bool { return s == literal; }) == result.end())
				result.push_back(literal);
		}
		file.close();
	}
	else
		cerr << "Error: unable to open " << filename << ".\n";

	return result;
}

// write elements on file
template<typename InputIterator>
void write_elements(InputIterator first, InputIterator last, const string& filename, ios_base::openmode mode = ios::out) {
	ofstream file(filename, mode);

	if (file.is_open()) {
		for (; first != last; (void)++first) file << *first << '\n';
		file.close();
	}
	else
		cerr << "Error: something went wrong...\n";
}

// displays help
inline void display_help() {
	cout << "This program reads a file and sorts its lines into an output file.\n";
	cout << "Note: duplicates are removed.\n";
	cout << "\nUsage:\n";
	cout << "organize input_filename\n";
	cout << "\nGeneral commands:\n";
	cout << "--h\t show this help message\n";
	cout << "--help\t show this help message" << endl;
}

// checks if an element is present in a container
template<typename Container, typename value_type = typename Container::value_type>
bool inline is_present(value_type& searched, Container& c) {
	using const_iterator = typename Container::const_iterator;
	const_iterator it = find_if(c.begin(), c.end(), [&](value_type& val) -> bool { return val == searched; });
	if (it != c.end()) return true;
	return false;
}

int main(int argc, char* argv[]) {
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	const vector<string> help_triggers{ "-h", "--help", "help" };
	const string output_filename{ "output.txt" };

	if (argc == 2) {
		const string input_filename{ (string)argv[1] };

		if (is_present(input_filename, help_triggers)) display_help();
		else {
			vector<string> literals = get_string_literals(input_filename);
			if (!literals.empty()) {
				sort(literals.begin(), literals.end());
				write_elements(literals.begin(), literals.end(), output_filename);
			}
		}
	}
	else display_help();
	return 0;
}
