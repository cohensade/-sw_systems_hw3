#include "StrList.h"
#include <stdio.h>

#define STRING_SIZE1 101

int main() {
    int number;
    StrList* Strlist = StrList_alloc();
    
    scanf("%d", &number);
    while (number != 0) {
        switch (number) {
            case 1: {
                int size;
                scanf("%d", &size);
                for (int i = 0; i < size; i++) {
                    char *word = (char *)malloc(STRING_SIZE1 * sizeof(char));
                    scanf("%s", word);
                    StrList_insertLast(Strlist, word);
                    free(word);
                }
                break;
            }
            case 2: {
                int index;
                scanf("%d", &index);
                char *word;
                word = (char *)malloc(STRING_SIZE1 * sizeof(char));  
                scanf("%s", word);
                StrList_insertAt(Strlist, word, index);
                free(word);
                break;
            }
            case 3:
                StrList_print(Strlist);
                break;
            case 4: {
                int size = StrList_size(Strlist);
                printf("%d", size);
                break;
            }
            case 5: {
                int index;
                scanf("%d", &index);
                StrList_printAt(Strlist, index);
                break;
            }
            case 6: {
                int len = StrList_printLen(Strlist);
                printf("%d", len);
                break;
            }
            case 7: {
                char *word;
                word = (char *)malloc(STRING_SIZE1 * sizeof(char));  
                scanf("%s", word);
                int count = StrList_count(Strlist, word);
                printf("%d", count);
                free(word);
                break;
            }
            case 8: {
                char *word;
                word = (char *)malloc(STRING_SIZE1 * sizeof(char));  
                scanf("%s", word);
                StrList_remove(Strlist, word);
                free(word);
                break;
            }
            case 9: {
                int index;
                scanf("%d", &index);
                StrList_removeAt(Strlist, index);
                break;
            }
            case 10:
                StrList_reverse(Strlist);
                break;
            case 11:
                while (StrList_size(Strlist) > 0) {
                    StrList_removeAt(Strlist, (StrList_size(Strlist) - 1));
                }
                break;
            case 12:
                StrList_sort(Strlist);
                break;
            case 13: {
                int a = StrList_isSorted(Strlist);
                if (a == 1) {
                    printf("%s\n", "true");
                } else {
                    printf("%s\n", "false");
                }
                break;
            }    
            default:
                break;
        }
        scanf("%d", &number);
    }
    StrList_free(Strlist);
    return 0;
}
