#include "index.h"

int main()
{
    JRB dict = create_dict();

    // Load stopwords list from file
    int num_of_stopw = 0;
    char stopw[MAX_NUM_STOPWORDS][MAX_LENGTH_STOPWORD];

    FILE* f = fopen(stopw_filepath, "r");
    while (fscanf(f, "%s", stopw[num_of_stopw]) != EOF)
        num_of_stopw++;
    fclose(f);

    f = fopen(text_filepath, "r");
    char lines[MAX_LINE_LENGTH];
    char delim[] = " \n\t\r!#$%%&'()*+,/:;<=>?@[]^_`{|}~0123456789"; // Không dùng "." và "-" để phân tách
    char *token, *context, *prev;
    int num_line = 1;
    int num_column = 1;

    prev = NULL;
    while (fgets(lines, MAX_LINE_LENGTH, f))
    {
        num_column = 1;
        token = strtok_r(trim(lines), delim, &context);
        while(token != NULL)
        {
            // Processing
            if (strcmp(token, ".") != 0 && strcmp(token, "-") != 0) // need check valid word
                if (prev == NULL || prev[strlen(prev)-1] == '.')
                    insert_word_to_dict(dict, to_lowercase(remove_dot_after(strdup(token))), num_line, num_column);
                else
                    insert_word_to_dict(dict, remove_dot_after(strdup(token)), num_line, num_column); // bỏ strdup là tha hồ bug

            // Next token
            prev = token;
            token = strtok_r(NULL, delim, &context);
            if (token == NULL)
                prev = strdup(prev); // 
            num_column++;
        }
        num_line++;
    }

    remove_stopw_from_dict(dict, stopw, num_of_stopw);
    show_dict(dict);
    delete_dict(dict);
    fclose(f);
    return 0;
}