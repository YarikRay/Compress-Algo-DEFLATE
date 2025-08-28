#include <iostream>
#include <vector>
#include <zlib.h>
#include <fstream>

#include "zlib_test.h"

int Zlib::compress_data(const string &src_file, const string &dest_file, int level = Z_BEST_COMPRESSION) {
    ifstream in(src_file, ios::binary); // открыли файл на чтение
    if (!in.is_open()) {
        cout << "File is not open" << endl;
    }
    in.seekg(0, ios::end);
    int size_file = in.tellg(); // определили размер файла
    cout << "Size of file: " << size_file << endl;
    in.seekg(0, ios::beg);
    int pos = in.tellg();

    vector<unsigned char>data_info_read(size_file); // выделили память под считывание
    in.read(reinterpret_cast<char*>(data_info_read.data()), size_file); // считали данные

    uLongf compressed_size = compressBound(size_file); // определили максимальный объем
                                                       // буфера для сжатых данные
    cout << "Compressed size: " << compressed_size << endl;
    vector<unsigned char>data_compress(compressed_size); // выделили память под запись сжатых данных

    int ret = compress2( // сжатие данных
    data_compress.data(),
         &compressed_size,
    data_info_read.data(),
         size_file,
         level
    );
    if (ret != Z_OK) {
        cout << "error";
        return ret;
    }

    data_compress.resize(compressed_size); // изменили размер вектора на реальный размер сжатых данных
    ofstream out(dest_file, ios::binary);
    out.write(reinterpret_cast<char*>(data_compress.data()), compressed_size);

    return Z_OK;
}
