#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  

//统计英文文本文件中字符个数
int count_characters(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}
//统计英文文本文件中单词个数
int count_words(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        return -1; // Return -1 if the file cannot be opened
    }

    int word_count = 0;
    int in_word = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        }
        else {
            in_word = 1;
        }
    }

    //如果最后一个字符是一个单词的一个字母，将它当作一个单词计数
    if (in_word) {
        word_count++;
    }

    fclose(file);
    return word_count;
}
//argc是输入参数个数，argv[]是输入的参数组成的列表
//输入两个参数，但最后argc是三，因为系统会将程序名当作第一个参数传入argv中，那么argv中就是3个参数
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[2];
    int count;

    if (strcmp(argv[1], "-c") == 0) {
        count = count_characters(filename);
        printf("字符数：%d\n", count);
    }
    else if (strcmp(argv[1], "-w") == 0) {
        count = count_words(filename);
        printf("单词数：%d\n", count);
    }
    else {
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
