#include "../headers/path.h"
#include "filesystem"

using namespace std;

filesystem::path directoryPath = filesystem::current_path();
string file_name = "compressed_data.txt";

filesystem::path fullPath = directoryPath / file_name;
string dest_file = fullPath.string();