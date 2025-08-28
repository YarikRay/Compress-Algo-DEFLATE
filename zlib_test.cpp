#include <iostream>
#include <vector>
#include <zlib.h>
#include <fstream>
#include <cassert>

#include "zlib_test.h"

// В файле zlib_test_def.cpp реализован метод def() класса Zlib

int Zlib::def(const string &src_file, const string &dest_file, int level) {
    /* Определим локальные переменные
       1) Переменная ret типа int служит для кодов возврата;
       2) Переменная flush типа int необходима для указания нужно ли немедленно обработать
          текущие данные или можно накапливать их для более эффективного сжатия;
       3) Переменная have типа unsigned int накапливает данные, которые готовы для записи в
          выходной буфер;
       4) Структурная переменная strm требуется для использования всех параметров структуры z_stream
          необходимых для реализации алгоритмов DEFLATE
       5) Векторы типа Bytef in и out объема CHUNK (константа определена в заголовочном файле
          zlib_test.h) выполняют роли входых и выходных буферов */
    int ret, flush;
    unsigned int have;
    z_stream strm;
    /*unsigned char in[CHUNK];
    unsigned char out[CHUNK];*/
    vector<unsigned char>in(CHUNK);
    vector<unsigned char>out(CHUNK);

    // Инициализация состояния deflate
    /* Поля структуры strm инициализированы Z_NULL с целью указать бибилиотеке zlib.h использовать память
       по умолчанию (использовать встроенные в библиотеку механизмы управления памятью) */
    strm.zalloc = Z_NULL;
    strm.zfree  = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit2(&strm,
                       level,
                       Z_DEFLATED, // единственный доступный метод
                       15,         // стандартный размер пропускного окна
                       8,          // стандартное значение memlevel
                       Z_HUFFMAN_ONLY // стратегия, для сжатия применяется только алгоритм Хаффмана
    ); /* вызвали состояние zlib для сжатия deflateInit.
                                       Передали указатель на структуру strm и уровень сжатия level*/

    if (ret != Z_OK) {
        return ret;
    }

    // Открываем файл с исходными данными на чтение
    ifstream in_stream(src_file, ios::binary);
    // Открываем файл для записи сжатых данных
    ofstream out_stream(dest_file, ios::binary);
    if (!in_stream.is_open()) {
        cout << "File is not open!";
        return Z_ERRNO;
    }
    cout << "File is open!";
    // Сжатие данных
    do {
        // 1. Обработка начинается с чтения данных
        in_stream.read(reinterpret_cast<char*>(in.data()), CHUNK);
        strm.next_in = in.data(); // передали указатель на данные, которые необходимо считать
        strm.avail_in = in_stream.gcount(); // передали количество считанных данных
        if (!in_stream.eof()) { // если есть еще не записанные данные
            flush = Z_NO_FLUSH;
        }
        else {
            flush = Z_FINISH;
        }

        // 2. Сжатие данных
        do {
           strm.avail_out = CHUNK; // передали объем пространства, требуемого на запись
           strm.next_out = out.data();

           ret = deflate(&strm, flush); // сжали данные и вернули код ошибки/успеха
           if (ret == Z_STREAM_ERROR) {
               cout << "Compressing Error";
               deflateEnd(&strm);
               return ret;
           }
           have = CHUNK - strm.avail_out;
           if (!out_stream.write(reinterpret_cast<char*>(out.data()), have) || !out_stream.good()) {
               deflateEnd(&strm);
               return Z_ERRNO;
           }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);
    }while (flush != Z_FINISH);
    //assert(ret == Z_STREAM_END);
    deflateEnd(&strm);
    return Z_OK;
}
