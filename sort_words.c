#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void sort_words(char *words[], int count)
{
    char * temp;
    
    // Use a simple selection sort in descending order based on the first character
    for (int i = 0; i < count - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (words[j][0] > words[max_idx][0]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            temp = words[i];
            words[i] = words[max_idx];
            words[max_idx] = temp;
        }
    }
}

#ifndef RunTests
int main()
{
    #include <time.h>
    #include <sys/resource.h>

    char *words[] = {
        "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew",
        "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry",
        "strawberry", "tangerine", "ugli", "vanilla", "watermelon", "xigua", "yam", "zucchini",
        "apricot", "blackberry", "cantaloupe", "dragonfruit", "eggplant", "feijoa", "guava",
        "hackberry", "imbe", "jackfruit", "kumquat", "lime", "mulberry", "nutmeg", "olive",
        "persimmon", "quararibea", "rambutan", "soursop", "tomato", "ugni", "voavanga", "wolfberry",
        "ximenia", "yumberry", "ziziphus", "avocado", "bilberry", "cloudberry", "damson", "elder",
        "fingerlime", "grapefruit", "hawthorn", "ilama", "jabuticaba", "kiwano", "longan", "miracle",
        "naranjilla", "olive", "plantain", "quenepa", "roseapple", "sapote", "tamarind", "ugli",
        "voavanga", "waxapple", "ximenia", "yangmei", "ziziphus", "acerola", "breadfruit", "currant",
        "dewberry", "emblic", "farkleberry", "gooseberry", "huckleberry", "indianfig", "jostaberry",
        "kaffir", "loganberry", "medlar", "nance", "oregano", "pineapple", "quandong", "rowan",
        "salak", "tangelo", "umbu", "vaccinium", "whitecurrant", "xango", "yellowpassion", "zinfandel"
    };

    int count = sizeof(words) / sizeof(words[0]);

    struct rusage usage_start, usage_end;
    clock_t start, end;

    getrusage(RUSAGE_SELF, &usage_start);
    start = clock();

    sort_words(words, count);

    end = clock();
    getrusage(RUSAGE_SELF, &usage_end);

    for (int i = 0; i < count; i++)
    {
        printf("%s ", words[i]);
    }
    printf("\n");

    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    long mem_used = usage_end.ru_maxrss - usage_start.ru_maxrss;

    printf("CPU time used: %f seconds\n", cpu_time);
    printf("Memory used: %ld KB\n", mem_used);
}
#endif