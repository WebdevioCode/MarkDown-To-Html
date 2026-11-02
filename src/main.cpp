#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string fileName;

    std::cout << "Enter the name off the file (with the .md)" << std::endl << ">_";
    std::getline(std::cin, fileName);

    std::ifstream Inputfile(fileName);
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
        if(line.find("### ") == 0) {
            std::string content = line.substr(4);
            Outputfile << "<h3>" << content << "</h3>\n";
        }
        else if(line.find("## ") == 0) {
            std::string content = line.substr(3);
            Outputfile << "<h2>" << content << "</h2>\n";
        }
        else if(line.find("# ") == 0) {
            std::string content = line.substr(2);
            Outputfile << "<h1>" << content << "</h1>\n";
        }
        else if(line.find("**") == 0) {
            size_t Endpos = line.rfind("**");

            if (Endpos != std::string::npos) {
                std::string content = line.substr(2,Endpos - 2);
                Outputfile << "<strong>" << content << "</strong>\n";
            }
        }
        else if(!line.empty()) {
            if(line.find("**")) {
                size_t Endpos = line.rfind("**");
                size_t Startpos = line.find("**");

                if (Endpos != std::string::npos) {
                    std::string content = line.substr(Startpos + 2,Endpos - Startpos - 2);
                    std::string Newcontent = "<strong>" + content + "</strong>";
                    std::string StartLine = line.substr(0,Startpos);
                    std::string EndLine = line.substr(Endpos + 2);
                    std::string NewText = "";
                    NewText.append(StartLine);
                    NewText.append(Newcontent);
                    NewText.append(EndLine);
                    Outputfile << "<p>" << NewText << "</p>\n";
                }
            } else {
                Outputfile << "<p>" << line << "</p>\n";
            }
        }
    }

    std::cout << "Conversion finished";

    Inputfile.close();
    Outputfile.close();

    return 0;
}
