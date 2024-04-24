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

    std::regex reOperators(R"([\+\-\*]|\<\<|\>\>)");
    std::regex reConditionals(R"(\b(if|else)\b)");
    std::regex reLoops(R"(\b(while|for)\b)");
    std::regex reComments(R"(\/\/.*[^\n])");
    std::regex reStrings(R"(".*?")");
    std::regex reBooleans(R"(\b(true|false)\b)");
    std::regex reDatatypes(R"(\b(int|float|bool)\b)");
    std::regex reAccessKeywords(R"(\b(public|private|protected)\b)");
    std::regex reFunctions(R"(\b(\w+)\s*\()");
    std::regex reSlash(R"([^<]\/[^s])");

    while (getline(inFile, line)) {
        size_t commentPos = line.find("//");
        string codeBeforeComment;

        if (commentPos != string::npos) {
            codeBeforeComment = line.substr(0, commentPos);
            line = codeBeforeComment + "<span class='comment'>" + line.substr(commentPos) + "</span>";
        } else {
            codeBeforeComment = line;
        }
        codeBeforeComment = std::regex_replace(codeBeforeComment, reStrings, "<span class='string'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reSlash,"<span class='operator'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reOperators, "<span class='operator'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reConditionals, "<span class='conditional'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reLoops, "<span class='loop'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reBooleans, "<span class='boolean'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reDatatypes, "<span class='datatype'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reAccessKeywords, "<span class='access'>$&</span>");
        codeBeforeComment = std::regex_replace(codeBeforeComment, reFunctions, "<span class='function'>$1</span>(");

        if (commentPos != string::npos) {
            line = codeBeforeComment + line.substr(codeBeforeComment.size());
        } else {
            line = codeBeforeComment;
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
