#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "files_parser.h"

using std::stof;
using std::to_string;





/**
 * Load data from already generated simulations in a vector
 *
 * @param values Container whose values are summed.
 * @return vector of vectors of floar with the return paths.
 */
std::vector<std::vector<float>> DataParser::ReturnPaths(std::string s_asset) {
  std::vector<std::vector<float>> rtns_paths;
  std::string line;
  std::ifstream stream(kDataDirectory + s_asset + ".csv");
  int ii = 0;
  char c;
  if (stream.is_open()) {
    // read just the first line of the file
    while (std::getline(stream, line))
    {
      std::istringstream this_row(line);
      rtns_paths.emplace_back(std::vector<float>());
      float this_value;
      int jj = 0;
      while (this_row >> this_value >> c && c == ',')
      {
          rtns_paths[ii].emplace_back(this_value);
          ++ jj;
      }
      ++ii;
      // std::cout << "next columns # " << ii
      //           << " rows filled # " << jj
      //           << "  rtns_paths[ii-1].back() = " << rtns_paths[ii-1].back()
      //           << "  rtns_paths[ii-1].size() = " << rtns_paths[ii-1].size()
      //           << std::endl;
    }
  }
  return std::move(rtns_paths);
}



// vector<int> ParseLine(string line) {
//     istringstream sline(line);
//     int n;
//     char c;
//     vector<int> row;
//     while (sline >> n >> c && c == ',') {
//       row.push_back(n);
//     }
//     return row;
// }

// vector<vector<int>> ReadBoardFile(string path) {
//   ifstream myfile (path);
//   vector<vector<int>> board{};
//   if (myfile) {
//     string line;
//     while (getline(myfile, line)) {
//       vector<int> row = ParseLine(line);
//       board.push_back(row);
//     }
//   }
//   return board;
// }

// void PrintBoard(const vector<vector<int>> board) {
//   for (int i = 0; i < board.size(); i++) {
//     for (int j = 0; j < board[i].size(); j++) {
//       cout << board[i][j];
//     }
//     cout << "\n";
//   }
// }

// int main() {
//   auto board = ReadBoardFile("1.board");
//   PrintBoard(board);
// }
