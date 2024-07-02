#include <iostream>
#include<bits/stdc++.h>
using namespace::std;

vector<string> extractTokens(string s);

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

      if(tokens[0].compare("exit") == 0) {
        exit(0);
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