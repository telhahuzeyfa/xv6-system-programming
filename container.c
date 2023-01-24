#include "user.h"
#include "jsmn.h"
#include "jsmn.c"

#define TOK_CNT 7
#define MAX_CMD_LENGTH 1024
#define MAX_PATH 1024

static const char *JSON_STRING =
	"{\"init\": \"/sh\", \"fs\": \"/c1/\", \"nproc\": 4 }";



void jsonstrcpy(const char *json_config, jsmntok_t *tok, char *str);
void jsonintcpy(const char *json_config, jsmntok_t *tok, int *n); 
int  jsoneq(const char *json, jsmntok_t *tok, char *s);
int  parse_config(const char* json_config, char* command, char* root_dir, int* nproc);

int main (void) {
    // printf(0,"Hello World\n");
    char command[MAX_CMD_LENGTH];
    char root_dir[MAX_PATH];
    int nproc = 0;

    int f = parse_config(JSON_STRING,command,root_dir,&nproc);
    printf(0,"%d\n",f);
    printf(0,"%s %s %d\n", command,root_dir,nproc);

    exit();
}

int parse_config(const char* json_config, char* command, char* root_dir, int* nproc){  /* return 0 or 1 */
                                                                                       /* create command, root_dir, nproc in calling function then pass them in */
    jsmn_parser p;
    jsmntok_t t[TOK_CNT]; /* If tokens greate needed */
    jsmn_init(&p); /* Init jsmn parser */

    int j = jsmn_parse(&p, json_config, strlen((char *)json_config), t, TOK_CNT);

    if(j != TOK_CNT) {
        printf(0,"j: %d\n", j);
        printf(0,"fail 1\n");
        return 0;
    } else if (t[0].type != JSMN_OBJECT) {
        printf(0,"fail 2\n");
        return 0;
    }

    for (int i=1;i<TOK_CNT;++i) {
        if ((jsoneq(json_config, &t[i], "init") == 0) && t[i].type == JSMN_STRING) {
            i++;
            jsonstrcpy(json_config, &t[i], command);
        } else if ((jsoneq(json_config, &t[i], "fs") == 0) && t[i].type == JSMN_STRING) {
           i++;
           jsonstrcpy(json_config, &t[i], root_dir); 
        } else if ((jsoneq(json_config, &t[i], "nproc") == 0) && t[i+1].type == JSMN_PRIMITIVE) {
           i++;
           jsonintcpy(json_config, &t[i], nproc); 
        } else {
            printf(0,"fail 3\n");
            printf(0,"i: %d, t[i].type: %d\n",i,t[i].type);
            return 0;
        }
    }
    return 1;
}

void jsonstrcpy(const char *json_config, jsmntok_t *tok, char *str) {
     for(int i=tok->start, jcnt = 0;i<tok->end;i++,jcnt++) {
        str[jcnt] = json_config[i];
     }
 }

 void jsonintcpy(const char *json_config, jsmntok_t *tok, int *n) {
     char arr[10];
     int jcnt = 0; /* Must be visible outside of loop for arr */
     for(int i=tok->start;i<tok->end;i++,jcnt++) {
        arr[jcnt] = json_config[i]; /* Copy string to arr*/
     }
     arr[jcnt] = 0;
     *n = atoi(arr); /* Convert to int */
 }
 
 int jsoneq(const char *json, jsmntok_t *tok, char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start) {
        for(int i=tok->start, jcnt = 0;i<tok->end;i++,jcnt++) {
            if(json[i] != s[jcnt]) return -1;
        }
    } else {
        return -1;
    }
    return 0;
}