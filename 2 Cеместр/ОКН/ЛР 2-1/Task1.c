#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

int main() {
    char text[500];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;
    
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    
    // Разделяем строку на слова
    char *token = strtok(text, " \n");
    while (token != NULL && word_count < MAX_WORDS) {
        strcpy(words[word_count++], token);
        token = strtok(NULL, " \n");
    }
    
    // Проверяем, есть ли слова в строке
    if (word_count == 0) {
        printf("The length of the shortest word: 0\n");
        printf("The length of the longest word: 0\n");
    } else {
        int shortest_length = strlen(words[0]);
        int longest_length = strlen(words[0]);
        
        for (int i = 1; i < word_count; i++) {
            int length = strlen(words[i]);
            if (length < shortest_length) {
                shortest_length = length;
            }
            if (length > longest_length) {
                longest_length = length;
            }
        }
        
        printf("The length of the shortest word: %d\n", shortest_length);
        printf("The length of the longest word: %d\n", longest_length);
    }

    return 0;
}