#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int main() {
    ifstream inFile("/Users/robertomoralesnieto/CLionProjects/LHmaybe/input.txt");
    ofstream outFile("/Users/robertomoralesnieto/CLionProjects/LHmaybe/output.html");

    if (!inFile.is_open()) {
        cerr << "No se pudo abrir input.txt" << endl;
        return 1;
    }

    string line;
    ostringstream htmlContent;

    htmlContent << "<!DOCTYPE html>\n<html>\n<head>\n<style>\n"
                   ".operator { color: red; }\n"
                   ".conditional { color: darkblue; }\n"
                   ".loop { color: lightblue; }\n"
                   ".comment { color: green; }\n"
                   ".string { color: orange; }\n"
                   ".boolean { color: purple; }\n"
                   ".datatype { color: pink; }\n"
                   ".access { color: darkred; }\n"
                   ".function { color: yellow; }\n"
                   "</style>\n</head>\n<body>\n<pre>\n";

    std::regex reOperators(R"([\+\-\*]|\<\<|\>\>|[^<]\/[^s])");
    std::regex reConditionals(R"(\b(if|else)\b)");
    std::regex reLoops(R"(\b(while|for)\b)");
    std::regex reComments(R"(\/\/.*[^\n])");
    std::regex reStrings(R"(".*?")");
    std::regex reBooleans(R"(\b(true|false)\b)");
    std::regex reDatatypes(R"(\b(int|float|bool)\b)");
    std::regex reAccessKeywords(R"(\b(public|private|protected)\b)");
    std::regex reFunctions(R"(\b(\w+)\s*\()");
    //std::regex reSlash(R"([^<]\/[^s])");

    while (getline(inFile, line)) {
        size_t commentPos = line.find("//");
        string lineaTemporal;

        if (commentPos != string::npos) {
            lineaTemporal = line.substr(0, commentPos);
            line = lineaTemporal + "<span class='comment'>" + line.substr(commentPos) + "</span>";
        } else {
            lineaTemporal = line;
        }
        lineaTemporal = std::regex_replace(lineaTemporal, reStrings, "<span class='string'>$&</span>");
        //lineaTemporal = std::regex_replace(lineaTemporal, reSlash,"<span class='operator'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reOperators, "<span class='operator'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reConditionals, "<span class='conditional'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reLoops, "<span class='loop'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reBooleans, "<span class='boolean'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reDatatypes, "<span class='datatype'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reAccessKeywords, "<span class='access'>$&</span>");
        lineaTemporal = std::regex_replace(lineaTemporal, reFunctions, "<span class='function'>$1</span>(");

        if (commentPos != string::npos) {
            line = lineaTemporal + line.substr(lineaTemporal.size());
        } else {
            line = lineaTemporal;
        }
        htmlContent << line << '\n';
    }
    htmlContent << "</pre>\n</body>\n</html>";
    outFile << htmlContent.str();
    inFile.close();
    outFile.close();
    cout << "Output generado" <<endl;
    return 0;
}
