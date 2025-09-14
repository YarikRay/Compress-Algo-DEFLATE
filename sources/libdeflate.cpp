#include <iostream>
#include <string>
#include <fstream>
#include "libdeflate.h"
#include "../headers/zlib_test.h"

void Zlib::libdeflate_compress(const string &src_file, const string &dest_file, int level) {
    ifstream in(src_file);
    in.seekg(0, ios::end);
    int size = in.tellg();
    vector<char> info(size);

    /* Открываем файл на чтение и считываем в выделенную память */
    if (in.is_open()) {
        in.read(info.data(), size);
    }

    ofstream out(dest_file); // файл отрыт на чтение

    /* Выделяtм память под функцию сжатия */
    libdeflate_compressor* compressor = libdeflate_alloc_compressor(level);

    /* Вычисляем максимально возможный размер сжатых данных.
     * Выделяем память под сматые данные */
    size_t max_size = libdeflate_deflate_compress_bound(compressor, info.size());
    vector<uint8_t> compressed_data(max_size);

    /* Сжимаем данные */
    size_t compressed_size = libdeflate_deflate_compress(
        compressor, // функция сжатия
        info.data(), // указатель на память, в которой находятся "сырые" данные
        size, // размер сырых даных
        compressed_data.data(), // указатель на выделенную под сжатые данные память
        max_size // максимально возможный размер сжатых данных
    );

    /* Освобождаем память выделенную под функцию сжатия */
    libdeflate_free_compressor(compressor);

    if (compressed_size == 0) {
        std::cerr << "Compress error";
    }

    /* Уменьшаем размер до реального размера */
    compressed_data.resize(compressed_size);

    /* Записываем сжатые данные в файл */
    out.write(reinterpret_cast<char*>(compressed_data.data()), compressed_size);
}
