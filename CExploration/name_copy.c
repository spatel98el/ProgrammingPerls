// read the input file containing {name sirname}
// split it and write back to other file in format {sirname,name}

#include <stdio.h>

void main() {
    FILE *infp = fopen("./data/names.txt", "r");
    if(infp == NULL) {
        printf("Unable to open file!\n");
    } else {
        printf("Successfully opened file\n");
    }

    // read names
    char c;
    char fname[10];
    char lname[10];
    int state = 0; // 0: first name 1: last name

    for(int i=0, j=0; (c = getc(infp)) != EOF;) {

        if(c == '\n') {
            state = 0; lname[i] = '\0'; i = 0;
            printf("%s, %s\n", lname, fname);
            continue;
        } else if (c == ' ') {
            state = 1; fname[j] = '\0'; j = 0;
            continue;
        }

        if(state) {
            lname[i++] = c;
        } else {
            fname[j++] = c;
        }
    }

    fclose(infp);

}