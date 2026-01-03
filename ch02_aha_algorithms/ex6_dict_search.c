// Exercise 6:
// given a dictionary of names in format {sirname name} format
//  - Dictionary is text file - read using file
//  - names are in all small case, no aphanum chars
//  - max names : 10k ?

// user enters names from telephone keybord to search in format {sirname*first letter of name*}
//  - mapping of phone key pad to char set

// return all the matches from the dictionary
//  - return set, print of the screen as a list of names

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME_LEN 10
#define MAX_RECORDS 10

typedef struct {
    char lname[MAX_NAME_LEN];
    char fname[MAX_NAME_LEN];
    int  OrgRecIdx;
} NameRec;

#define KBD_SIZE 8
#define CHARS_KEY 3

struct charSetMap
{
    char c[CHARS_KEY];
    int button;
} chMap[KBD_SIZE] = {
    {{'a', 'b', 'c'}, '2'},
    {{'d', 'e', 'f'}, '3'},
    {{'g', 'h', 'i'}, '4'},
    {{'j', 'k', 'l'}, '5'},
    {{'n', 'm', 'o'}, '6'},
    {{'p', 'r', 's'}, '7'},
    {{'t', 'u', 'v'}, '8'},
    {{'w', 'x', 'y'}, '9'},
};

int comp (const void *r1, const void *r2) {
    NameRec *l = (NameRec*) r1, *r = (NameRec *) r2;
    // lname code comparator
    return strcmp(l->lname, r->lname);
}

void sortRecords(NameRec *nameRec, int numRec) {
    // sort records
    qsort(nameRec, numRec, sizeof(NameRec), comp);
}

typedef struct {
    char c;
    int pos;
}Key;

int recComp(const void *r, const void *key) {
    Key *k = (Key *)key;
    NameRec *nr = (NameRec *)r;
    char l = nr->lname[k->pos];

    if(l < k->c) {
        return -1;
    } else if (l > k->c) {
        return 1;
    } else {
        return 0;
    }
}

// To be completed
int bsearchWithRange(NameRec *nameRec, Key *key, int numRec, int *rr, int *rl) {
    
    bsearch(key, nameRec, numRec, sizeof(NameRec), recComp);
}

int isMatch(char *lname, char *inputKey){
    int i;
    for(i = 0; (lname[i] != '\0' || inputKey[i] != '*'); i++) {
        if(lname[i] != inputKey[i]) {
            break;
        }
    }
    return(i > 0 ? 1: 0);
}

int lineraSearchRec(char* inputKey, int pos, NameRec *nameRec, int recCount) {
    for(int i = 0; i < recCount; i++) {
        if(isMatch(nameRec[i].lname, inputKey)) {
            printf("Rec %d: %s, %s\n", nameRec[i].OrgRecIdx, nameRec[i].lname, nameRec[i].fname);
        }
    }
}


char getButtonCode(char c) {
    for(int i = 0; i < KBD_SIZE; i++) {
        for (int j = 0; j < CHARS_KEY; j++) {
            if(c == chMap[i].c[j])
                return chMap[i].button;
        }
    }

    return 0;
}

int parseInputDataFile(FILE *fp, NameRec *nameRec) {
    char c;
    int recIdx = 0;
    int state = 0; //state 0: lname, state 1 : fname
    int lidx = 0, fidx = 0;


    while((c = getc(fp)) != EOF) {
        if (c == ' ')
        {
            state = 1;
            nameRec[recIdx].lname[fidx++] = '\0';
            lidx = 0;
            continue;
        }
        else if (c == '\n')
        {
            state = 0;
            nameRec[recIdx].fname[lidx++] = '\0';
            fidx = 0;
            nameRec[recIdx].OrgRecIdx = recIdx;
            // printf("Parsed record : %d, %s, %s\n", 
            //         nameRec[recIdx].OrgRecIdx, nameRec[recIdx].lname, nameRec[recIdx].fname);
            recIdx++;
            continue;
        }

        if(state) {
            nameRec[recIdx].fname[lidx++] = getButtonCode(c);
        } else {
            nameRec[recIdx].lname[fidx++] = getButtonCode(c);
        }
    }

    return recIdx;
}


int main() {
    FILE *fp = fopen("./data/name_dict.txt", "r");

    if(fp == NULL) {
        printf("Error in opening file!");
        return -1;
    }

    // read all the names
    NameRec *nameRec = (NameRec *)malloc(sizeof(NameRec)*MAX_RECORDS);

    int numRecs = parseInputDataFile(fp, nameRec);

    for(int i = 0; i < numRecs; i++) {
        printf("OrgRecIdx = %d, lnameCode = %s, fnameCode = %s\n", 
                nameRec[i].OrgRecIdx, nameRec[i].lname, nameRec[i].fname);
    }

    printf("Enter key:");
    char inputKey[10] = {0};
    scanf("%s", inputKey);

    for(int i = 0; inputKey[i] != '\0'; i++) {
        printf("Key : %c\n", inputKey[i]);
        lineraSearchRec(inputKey, i, nameRec, numRecs);
    }

    sortRecords(nameRec, numRecs);

    for(int i = 0; i < numRecs; i++) {
        printf("OrgRecIdx = %d, lnameCode = %s, fnameCode = %s\n", 
                nameRec[i].OrgRecIdx, nameRec[i].lname, nameRec[i].fname);
    }   

    int rr = 0, rl = 0;
    for(int i = 0; inputKey[i] != '\0'; i++) {
        printf("Key : %c\n", inputKey[i]);
        Key k = {inputKey[i], i};
        bsearchWithRange(nameRec, &k, numRecs, &rr, &rl);
    }

    free(nameRec);
    fclose(fp);
}