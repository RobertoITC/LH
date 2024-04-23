#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int main() {
    ifstream inFile("/Users/robertomoralesnieto/CLionProjects/LHmaybe/input.txt");
    ofstream outFile("/Users/robertomoralesnieto/CLionProjects/LHmaybe/output.html");

    if (!inFile.is_open()) {
        cerr << "Failed to open input.txt" << endl;
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

    std::regex reOperators(R"([\+\-\*\/])");
    std::regex reConditionals(R"(\b(if|else)\b)");
    std::regex reLoops(R"(\b(while|for)\b)");
    std::regex reComments(R"(\/\/[^\n]*)");
    std::regex reStrings(R"(".*?")");
    std::regex reBooleans(R"(\b(true|false)\b)");
    std::regex reDatatypes(R"(\b(string|int|float|bool)\b)");
    std::regex reAccessKeywords(R"(\b(public|private|protected)\b)");
    std::regex reFunctions(R"(\b(\w+)\s*\()");

    while (getline(inFile, line)) {
        line = std::regex_replace(line, reStrings, "<span class='string'>$&</span>");
        line = std::regex_replace(line, reComments, "<span class='comment'>$&</span>");
        line = std::regex_replace(line, reOperators, "<span class='operator'>$&</span>");
        line = std::regex_replace(line, reConditionals, "<span class='conditional'>$&</span>");
        line = std::regex_replace(line, reLoops, "<span class='loop'>$&</span>");
        line = std::regex_replace(line, reBooleans, "<span class='boolean'>$&</span>");
        line = std::regex_replace(line, reDatatypes, "<span class='datatype'>$&</span>");
        line = std::regex_replace(line, reAccessKeywords, "<span class='access'>$&</span>");
        line = std::regex_replace(line, reFunctions, "<span class='function'>$1</span>(");

        htmlContent << line << '\n';
    }

    htmlContent << "</pre>\n</body>\n</html>";

    outFile << htmlContent.str();

    inFile.close();
    outFile.close();

    cout << "Output generado" <<endl;

    return 0;
}
