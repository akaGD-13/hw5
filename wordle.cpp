

#include "wordle.h"
#include "dict-eng.h"
#include <string>
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(std::string in,
    std::string floating,
    std::set<std::string>& solutions, const std::set<std::string>& dict, int num_empty);

//check if the string contains the floating
// bool check(std::string s, const std::string& in, const std::string& floating);

int numofchar(string s, char c);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> solutions;
    int num_empty = numofchar(in, '-');
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

// bool check(std::string s, const std::string& in, const std::string& floating){

//     // replace original letters with '-'
//     for (size_t i=0; i< s.size(); i++){
//       if (in[i] != '-'){
//         s[i] = '-';
//       }
//     }

//     for (size_t i=0; i < floating.size(); i++){
//       if (s.find(floating[i]) == string::npos){
//         // floating doesn't exist
//         return false;
//       }
//       else{
//         //found;
//         s[s.find(floating[i])] = '-';
//       }      
//     }

//     return true;
// }

int numofchar(string s, char c){
  int count = 0;
  for (size_t i=0; i < s.size(); i++){
    if (s[i] == c){
      count++;
    }
  }
  return count;
}