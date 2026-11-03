#include <iostream>
#include <string>
#include <fstream>

void CheckForParagraph(std::string line, std::ofstream& Outputfile) {
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
            } else if(line.find("*")) {
                size_t Endpos = line.rfind("*");
                size_t Startpos = line.find("*");

                if (Endpos != std::string::npos) {
                    std::string content = line.substr(Startpos + 1,Endpos - Startpos - 1);
                    std::string Newcontent = "<em>" + content + "</em>";
                    std::string StartLine = line.substr(0,Startpos);
                    std::string EndLine = line.substr(Endpos + 1);
                    std::string NewText = "";
                    NewText.append(StartLine);
                    NewText.append(Newcontent);
                    NewText.append(EndLine);
                    Outputfile << "<p>" << NewText << "</p>\n";
                }
                else {
                    Outputfile << "<p>" << line << "</p>";
                }
            }
        }
