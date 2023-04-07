#ifndef RECCHECK

#endif

#include "wordle.h"
#include "dict-eng.h"
#include <string>
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(std::string in,
    std::string floating,
    std::set<std::string>& solutions, const std::set<std::string>& dict, int num_empty);




// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> solutions;
    int num_empty = 0;
    for (size_t i=0; i < in.size(); i++){
      if (in[i] == '-'){
        num_empty++;
      }
    }
    wordle_helper(in, floating, solutions, dict, num_empty);

    return solutions;
    
}




// Define any helper functions here
void wordle_helper(std::string in,
    std::string floating,
    std::set<std::string>& solutions, const std::set<std::string>& dict, int num_empty)
{
  //base case
  if (num_empty == 0){
    if (dict.find(in) != dict.end()){
      solutions.insert(in);
      return;
    }
  }

  size_t index = in.find('-'); // index of the first '-'
  string chars;
  if (floating.size() == num_empty){
    chars = floating;
  }
  else{
    chars = "abcdefghijklmnopqrstuvwxyz";
  }
  for (auto x : chars){
      in[index] = x;
      string new_f = floating;
      if (floating.find(x) != string::npos){
        new_f.erase(new_f.begin()+new_f.find(x));
      }
      wordle_helper(in, new_f, solutions, dict, num_empty-1);
  }

}

