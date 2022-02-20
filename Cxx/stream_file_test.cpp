#include <string>       // for strings
#include <iostream>     // for I/O
#include <fstream>      // for file I/O
#include <iomanip>      // for setw()
#include <cstdlib>      // for exit()


using namespace std;

void write_charset_to_file(const string &file_name)
{
    ofstream file(file_name);

    if(!file) {
        cerr << "Can't open file: " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    for(int i=32; i<256; i++) {
        file << "index: " << setw(3) << i << " "
             << "char: " << static_cast<char>(i) << endl;
    }


}

void print_from_file(const string &file_name)
{
    ifstream file(file_name);

    if(!file) {
        cerr << "Can't open file: " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    char c;
    while(file.get(c)) {
        cout.put(c);
    }
}

int main(int argc, char **argv)
{
    string file_name = "stream_test.txt";

    write_charset_to_file(file_name);
    print_from_file(file_name);

    return 0;
}
