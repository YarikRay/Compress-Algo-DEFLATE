#ifndef ZLIB_TEST_H
#define ZLIB_TEST_H

#define CHUNK 1024*1024 // Определим размер буфера. Чем больше размер буфера, тем работа сжатия и распаковки будет
                    // происходить быстрее

#include <string>
#include <chrono>

#include "zlib.h"

using namespace std;

extern const string src_fie; // исходный файл
extern const string dest_file; // файл, куда отпраляются сжатые данные

/* Класс Zlib предназначен для сжатия данных в файл и распаковки их из него. Класс состоит из
  2-ух методов:
        1) Метод def() <- сжимает данные входного файла и помещает их в выходной файл;
        2) Метод inf() <- распаковывает данные из входного файла и записывает их в выходной файл.
        3) Метод time_def() <- подсчитывает время выполнения функии*/
class Zlib {
public:
    /* 1) Метод def() принимает в качестве аргументов ссылку типа string на входной файл, откуда
          будут браться данные для сжатия, ссылку типа string на выходной файл, куда будут помещаться
          данные после сжатия, а также переменную level типа int, которая показывает уровень сжатия;
       2) Метод compress_data() принимает в качестве аргументов такие же параметры, как и метод def()
        */
    int def(const string& src_file, const string& dest_file, int level);
    int compress_data(const string& src_file, const string& dest_file, int level);
};

#endif //ZLIB_TEST_H

