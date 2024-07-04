#include <iostream>
#include<bits/stdc++.h>
using namespace::std;

vector<string> extractTokens(string s);
string exec(const char* cmd); 

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;
  string commandNotFoundError(": command not found");

  // Uncomment this block to pass the first stage
  while (true){
      cout << "$ ";
      string input;
      getline(std::cin, input);
      vector<string> tokens = extractTokens(input);

      //int resultCode  = system("which " + tokens )

      if(tokens[0].compare("exit") == 0) {
        exit(0);
      }
      else if(tokens[0].compare("echo") == 0) {
        cout << input.substr(5);
      }
      else if(tokens[0].compare("type") == 0) {
        string tpCommand = "type "+ tokens[1]; 
        string result = exec(tpCommand.c_str());
        cout << result.substr(0, result.size() - 1); // Removing the extra "\n";
      }
      else{
        cout << input << commandNotFoundError;
      }
      
      cout<<"\n";
  }
}

vector<string> extractTokens(string s) {
    vector<string> tokens;
    string del = " ";

    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        tokens.push_back(s.substr(start, end - start));
    } while (end != -1);
    
    return tokens;
}

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
      result += buffer.data();
    }


    return result;
}