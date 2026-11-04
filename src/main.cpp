#include <iostream>
#include <fstream>
#include <string>
#include "Headings/CheckForParagraph.hpp"
#include "Headings/CheckForImgTag.hpp"

int main() {
    std::string fileName;
    bool insidecodeblock = false;

    std::cout << "Enter the name off the file (with the .md)" << std::endl << ">_";
    std::getline(std::cin, fileName);

    std::ifstream Inputfile(fileName);
    std::ofstream Outputfile("output.html");

    if(!Inputfile.is_open()) {
        std::cout << "There was an error opening the readme File";
        return 1;
    }
    if(!Outputfile.is_open()) {
        std::cout << "There was an error creating the html file";
        return 1;
    }
    Outputfile << "<!DOCTYPE html>\n";
    Outputfile << "<html>\n";
    Outputfile << "<body>\n";


    std::string line;
    while(std::getline(Inputfile, line)) {
        if(line == "```") {
            if (!insidecodeblock) {
                Outputfile << "<pre><code>\n";
                insidecodeblock = true;
            }
            else {
                Outputfile << "</code></pre>\n";
                insidecodeblock = false;
            }
            continue;
        }
        else if(insidecodeblock) {
            Outputfile << line << "\n"; 
        }
       else if(line.find("### ") == 0) {
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
        else if(line.find("*") == 0) {
            size_t Endpos = line.rfind("*");

            if(Endpos != std::string::npos) {
                std::string content = line.substr(1,Endpos - 1);
                Outputfile << "<em>" << content << "</em>\n";
            }
        }
        else if(line.find("https://") != std::string::npos || line.find("http://") != std::string::npos) {
            size_t Endpos = line.rfind(")");
            size_t Startpos = line.find("(");

            if(Endpos != std::string::npos && Startpos != std::string::npos) {
                std::string content = line.substr(Startpos + 1, Endpos -Startpos - 1);
                size_t TextEndpos = line.rfind("]");
                size_t TextStartpos = line.find("[");
                std::string Text = line.substr(TextStartpos + 1, TextEndpos - TextStartpos - 1);
                Outputfile << "<a href=\"" << content << "\"" << ">" << Text << "</a>\n";
            }
        }
        else if(line.rfind(".png") != std::string::npos || line.rfind(".jpeg") != std::string::npos) {
            CheckForImgTag(line,Outputfile);
        }
        else if(line.find("<div>") != std::string::npos) {
            Outputfile << "<div>\n";
        }
        else if(line.find("</div>") != std::string::npos ) {
            Outputfile << "</div>\n";
        }
         else if(line == "---") {
            Outputfile << "<hr>\n";
        }
        else if(line.find("~") == 0) {
            size_t Endpos = line.rfind("~");
            size_t Startpos = line.find("~");
            if (Endpos != std::string::npos) {
                std::string content = line.substr(Startpos + 3,Endpos - 4);
                Outputfile << "<del>" << content << "</del>\n";
            }
        }
        else if(!line.empty()) {
            CheckForParagraph(line,Outputfile);
        }
    }


    Outputfile << "</body>\n";
    Outputfile << "</html>";

    std::cout << "Conversion finished";

    Inputfile.close();
    Outputfile.close();

    return 0;
}
