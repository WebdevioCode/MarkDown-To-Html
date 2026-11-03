#include <iostream>
#include <fstream>
#include <string>

void CheckForImgTag(std::string line, std::ofstream& Outputfile) {
    if (line.rfind(".png") != std::string::npos) {
            size_t Endpos = line.rfind(")");
            size_t Startpos = line.rfind("(");
            if (Endpos && Startpos !=std::string::npos) {
                std::string content = line.substr(Startpos + 1, Endpos - Startpos - 1);
                Outputfile << "<img src=" << content << ">\n";
            }
            }
            else if (line.rfind(".jpeg") != std::string::npos) {
                size_t Endpos = line.rfind(")");
                size_t Startpos = line.rfind("(");

                if (Endpos && Startpos !=std::string::npos) {
                    std::string content = line.substr(Startpos + 1, Endpos - Startpos - 1);
                    Outputfile << "<img src=" << content << ">\n";
                }
            }
}
