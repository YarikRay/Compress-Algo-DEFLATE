#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/zlib_test.h"
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES
#include "../miniz-3.0.2/miniz.h"

using namespace std;

void Zlib::m_compress(const string &src_file, const string &dest_file, int level) {
    // Считывание "сырых" данных в файл
    ifstream in(src_file, ios::binary);
    if (in.is_open()) {
        cout << src_file << endl;
    }
    ofstream out_stream(dest_file, ios::binary);
    if (out_stream.is_open()) {
        cout << dest_file << endl;
    }
    in.seekg(0, ios::end);
    int size = in.tellg();
    vector<char> data_info(0, size);
    in.seekg(0, ios::beg);
    in.read(data_info.data(), size);

    mz_ulong compress_size = mz_compressBound(data_info.size());
    vector<unsigned char> compressed(compress_size); // определили максимальный объем
                                                     // буфера для сжатых данные
    int result = mz_compress2(compressed.data(), &compress_size,
                                reinterpret_cast<const unsigned char *>(data_info.data()),
                                data_info.size(), level);
    if (result == MZ_OK) {
        cout << "Level " << level << ": " << compress_size;
    }

    out_stream.write(reinterpret_cast<char*>(compressed.data()), compress_size);
}
