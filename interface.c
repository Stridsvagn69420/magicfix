#include "interface.h"
#include "cJSON.h"
#include "magicfix.h"
#include <string.h>

/// @brief: A tool function used to return the entire content in a file
/// @return: char*
unsigned char* read_file(char* filename) {
    unsigned char *buffer = NULL;
    long length;
    FILE *f = fopen (filename, "rb");

    if (f) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (unsigned char*) malloc (length + 1);
        if (buffer) {
            fread (buffer, 1, length, f);
            buffer[length] = '\0'; // Ensure the buffer ends with EOF
        }
        else
            return NULL;
        fclose (f);
    }
    else
        return NULL;
    return buffer;
}

enum MagicResult process(char* filename, char* result) {
    unsigned char *buf1 = read_file("sig.json"), *buf2 = read_file(filename);
    cJSON *json, *backup;
    if((json = cJSON_Parse(buf1)) == NULL) {
        errno = ERR_JSON;
        return MagicBuffErr;
    }

    backup = json; // used to deallocate the cjson item
    for(json = json->child; json; json = json->next) {
        cJSON *t;
        bool flag;
        char *end;
        int cnt;
        if(cJSON_GetArraySize(json->child) > strlen(buf2))
            continue;
        for(t = json->child, cnt = 0, flag = true; t; t = t->next, ++cnt) {
            if((int)strtol(t->valuestring, &end, 16) != (int)buf2[cnt]) {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            strcpy(result, json->string);
            cJSON_Delete(backup);
            return MagicTrue;
        }
    }
    cJSON_Delete(backup);
    return MagicFalse;
}