#include <iostream>
#include <zlib.h>
#include <vector>


#include "headers/time_def.h"
#include "headers/path.h"
#include "headers/zlib_test.h"

using namespace std;

int main() {
    string method;
    string source_file;
    cout << "Enter compress method: ";
    cin >> method;
    cout << "Enter sorce file path: ";
    cin >> source_file;
    Zlib lib;
    chrono::steady_clock::time_point tStartSteady = chrono::steady_clock::now();
    time_t startWallTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Time start: " << ctime(&startWallTime) << endl;
    if (method == "d") {
        int ret = lib.def(source_file, dest_file, Z_BEST_COMPRESSION);
        if (ret != Z_OK) {
            cout << "Error: " << ret;
        }
    }
    else if (method == "c") {
        int ret = lib.compress_data(source_file, dest_file, Z_BEST_COMPRESSION);
        if (ret != Z_OK) {
            cout << "Error: " << ret;
        }
    }
    else if (method == "m") {
        lib.m_compress(source_file, dest_file, 9);
    }
    else if (method == "l") {
        lib.libdeflate_compress(source_file, dest_file, 9);
    }
    else {
        cout << "Bad option";
    }
    end_time(tStartSteady);
}
