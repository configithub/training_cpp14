#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>

int get_vote(std::set<std::string>& voters, 
          std::map<std::string, int>& vote_counts,
          std::vector<std::string>& choices) {
  std::string name;
  std::cout << "type your name:" << std::endl;
  getline(std::cin, name);
  if(name == "") { return 0; }
  std::cout << "your name : " << name << std::endl;

  std::string choice_str;
  std::cout << "type your choice:" << std::endl;
  getline(std::cin, choice_str);
  int choice = atoi(choice_str.c_str());

  if(choice < 0 or choice > choices.size()) {
    std::cout << "invalid choice" << std::endl;
  }else{
    std::cout << "your choice: " << choice << " " 
            << choices[choice-1] << std::endl;
  }

  //std::set<std::string>::iterator find_voter = voters.find(name);
  auto find_voter = voters.find(name);
  if(find_voter != voters.end()) {
    std::cout << "already voted" << std::endl;
  }else{
    voters.insert(name);
    vote_counts[choices[choice-1]]++;
  }

  return choice;

}

int main(int argc, char** argv) {
  // build the list of restaurant
  std::vector<std::string> choices{ "resto1", "resto2", "resto3" };
  int i = 1;
  for(auto c : choices) {
    std::cout << "#" << i << " " << c << std::endl;
    ++i;
  }
  // voters and vote_counts
  std::set<std::string> voters;
  std::map<std::string, int> vote_counts;
  
  
  while(get_vote(voters, vote_counts, choices) != 0) {
    std::cout << "next voter" << std::endl;
  }

  std::cout << "Results:" << std::endl;
  //for(std::map<std::string,int>::iterator itvc = vote_counts.begin(); 
    //itvc != vote_counts.end(); ++itvc) { 
  for(auto vc : vote_counts) {
    //std::cout << itvc->first << " " << itvc->second << std::endl;
    std::cout << vc.first << " " << vc.second << std::endl;
  } 

  return 0;
}
