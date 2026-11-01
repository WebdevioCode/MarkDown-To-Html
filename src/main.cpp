#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string fileName;

    std::cout << "Enter the name off the file (without the .md)";
    std::cin >> fileName;

    std::ifstream Inputfile(fileName + ".md");
    std::ofstream Outputfile("output.html");

    if(!Inputfile.is_open()) {
        std::cout << "There was an error opening the readme File";
        return 1;
    }
    if(!Outputfile.is_open()) {
        std::cout << "There was an error creating/opening the html file";
        return 1;
    }

    std::string line;
    while(std::getline(Inputfile, line)) {
        if(line.rfind("### ", 0) == 0) {
            std::string content = line.substr(4);
            Outputfile << "<h3>" << content << "</h3>\n";
        }
        else if(line.rfind("## ", 0) == 0) {
            std::string content = line.substr(3);
            Outputfile << "<h2>" << content << "</h2>\n";
        }
        else if(line.rfind("# ", 0) == 0) {
            std::string content = line.substr(2);
            Outputfile << "<h1>" << content << "</h1>\n";
        }

    }

    Inputfile.close();
    Outputfile.close();

    return 0;
}
