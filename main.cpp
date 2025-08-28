#include <iostream>
#include <zlib.h>

#include "zlib_test.h"
#include "time_def.h"

using namespace std;

int main(int argc, char* argv[]) {
    Zlib lib;

    chrono::steady_clock::time_point tStartSteady = chrono::steady_clock::now();
    time_t startWallTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Time start: " << ctime(&startWallTime) << endl;
    //lib.def(src_fie, dest_file, Z_BEST_COMPRESSION);
    lib.compress_data(src_fie, dest_file, Z_BEST_COMPRESSION);
    end_time(tStartSteady);
}
