#include <iostream>

#include "time_def.h"

using namespace std;


void end_time(chrono::steady_clock::time_point tStartSteady) {
    cout << endl;
    // Время конца работы
    chrono::steady_clock::time_point tEndSteady = chrono::steady_clock::now();
    //auto tStartSteady = start_time();
    chrono::nanoseconds diff = tEndSteady - tStartSteady;
    chrono::seconds sec = chrono::duration_cast<chrono::seconds>(diff);
    time_t endWallTime = chrono::system_clock::to_time_t(chrono::system_clock::now());

    // Вывод результатов
    cout << "Time end: " << ctime(&endWallTime) << endl;
    cout << "Time taken: " << sec.count() << " seconds";
}