#ifndef ZLIB_TEST_H
#define ZLIB_TEST_H

#define CHUNK 1024*1024*1024// Определим размер буфера. Чем больше размер буфера, тем работа сжатия и распаковки будет
// происходить быстрее

#include <string>
#include <chrono>

#include "zlib.h"

using namespace std;


/* Класс Zlib предназначен для сжатия данных в файл и распаковки их из него. Класс состоит из
  2-ух методов:
        1) Метод def() <- сжимает данные входного файла и помещает их в выходной файл с помощью метода deflateInit2;
        2) Метод compress_data() <- сжимает данные с помощью функции zlib compress2
        3) Метод m_compress() <- сжимает данные с помощью библиотеки miniz
        4) Метод libdeflate_zlib_compress() <- производит сжатие при помощи библиотеки libdeflate*/
class Zlib {
public:
    /* 1) Метод def() принимает в качестве аргументов ссылку типа string на входной файл, откуда
          будут браться данные для сжатия, ссылку типа string на выходной файл, куда будут помещаться
          данные после сжатия, а также переменную level типа int, которая показывает уровень сжатия;
       2) Метод compress_data() принимает в качестве аргументов такие же параметры, как и метод def()
        */
    int def(const string &src_file, const string &dest_file, int level);

    int compress_data(const string &src_file, const string &dest_file, int level);

    void m_compress(const string &src_file, const string &dest_file, int level);

    void libdeflate_compress(const string &src_file, const string &dest_file, int level);
};

#endif //ZLIB_TEST_H
