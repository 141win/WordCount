#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  

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

    // If the last character was part of a word, count it as a word
    if (in_word) {
        word_count++;
    }

    fclose(file);
    return word_count;
}

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
