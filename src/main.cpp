#include <iostream>
#include<bits/stdc++.h>
#include <sstream>
#include <filesystem>
using namespace::std;

vector<string> extractTokens(string s);
string exec(const char* cmd); 
string get_path(std::string command);

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;
  string commandNotFoundError(": command not found");

  set<string> validCommands({"echo", "exit", "type", "pwd"});

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
        if(validCommands.find(tokens[1]) != validCommands.end()) {
          cout<< tokens[1] <<" is a shell builtin";
        }
        else{
          // string tpCommand = "type "+ tokens[1]; 
          // string result = exec(tpCommand.c_str());
          // cout << result.substr(0, result.size() - 1); // Removing the extra "\n";

          std::string path = get_path(tokens[1]);
          if(path.empty()){
              std::cout<<tokens[1]<<": not found";
          }
          else{
              std::cout<<tokens[1]<<" is "<<path;
          }
        }
      }
      else if(tokens[0].compare("pwd")  == 0) {
          cout << filesystem::current_path();
      }
      else{
          std::string path = get_path(tokens[0]);

          for(int i=1; i < tokens.size(); i++) {
            path.append(" ").append(tokens[i]);
          }

          if(path.empty()) {
            cout << input << commandNotFoundError;
          }
          else {

              // cout << path <<"\n";
              string result = exec(path.c_str());
              cout << result.substr(0, result.size() - 1); // Removing the extra "\n";
          }
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

string get_path(string command){
    string path_env = std::getenv("PATH");
    stringstream ss(path_env);
    string path;
    while(!ss.eof()){
        getline(ss, path, ':');
        string abs_path = path + '/' + command;
        if(filesystem::exists(abs_path)){
            return abs_path;
        }
    }
    return "";  
}