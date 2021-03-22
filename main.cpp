#include <iostream>
#include <vector>
#include <fstream>


int main() {
  std::vector<std::string> lines;
  std::string line;

  std::ifstream Settings;
  Settings.open("adaship_config.ini");
  while (!Settings.eof()) {
      std::getline(Settings, line);
      lines.push_back(line);
  }
  Settings.close();
  for (auto& a : lines) {
    std::cout << a << std::endl;
  }
  std::cout << lines.size();
}