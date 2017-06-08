#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "parser.h"

#define LIM " \t(){}[].,:;"
#define BUF_SIZE 128

/*
 * NOP PARSER
 *
 * This is a skeleton parser. Nothing has been implemented yet.
 * You can invoke this parser by the following command.
 *
 * $ gtags --gtagsconf=/usr/local/share/gtags/gtags.conf --gtagslabel=user
 */
void
cheapruby(const struct parser_param *param)
{
    FILE *ip;
    char buf[1024], saveline[1024], *token;
    int lineno = 0;
    int next_symbol_is_class = 0;
    assert(param->size >= sizeof(*param));
    ip = fopen(param->file, "r");
    if (ip == NULL)
        param->die("cannot open file '%s'", param->file);
    while (fgets(buf, sizeof(buf), ip)) {
        char *p, *line = buf;
        int def = 0;

        lineno++;
        buf[strlen(buf) - 1] = '\0';
        strcpy(saveline, buf);
        for (token = strtok(line, LIM); token != NULL; token = strtok(NULL, LIM)) {
            if (*token == '#')
                break;
            if (isdigit(*token))
                continue;
            if (*token == '\'')
                continue;
            if (!strcmp(token, "while") || !strcmp(token, "end"))
                continue;
            if (!strcmp(token, "class")) {
                next_symbol_is_class = 1;
                continue;
            }
            if (isalpha(*token)) {
                param->put(next_symbol_is_class ? PARSER_DEF : PARSER_REF_SYM,
                    token, lineno, param->file, saveline, param->arg);
                next_symbol_is_class = 0;
            }
        }
    }
    fclose(ip);
}

void
cheapscala(const struct parser_param *param)
{
    char token[BUF_SIZE];
    int next_symbol_is_class = 0;
    int next_symbol_is_object = 0;
    int next_symbol_is_trait = 0;
    int next_symbol_is_function = 0;

    assert(param->size >= sizeof(*param));

    FILE *fp;
    fp = fopen(param->file, "r");
    if (fp == NULL)
        param->die("cannot open file '%s'", param->file);

    int c = 0;
    int lineno = 1;
    while ((c = fgetc(fp)) != EOF) {


        if (c=='\n') {
            lineno++;
            continue;
        }


        if (isdigit(c)) continue;


        if (c=='\"') {
            while ((c = fgetc(fp)) != EOF) {
                if (c=='\n') lineno++;
                if (c=='\"') break;
            }
            continue;
        }


        if (c=='\'') {
            while ((c = fgetc(fp)) != EOF) {
                if (c=='\'') break;
            }
            continue;
        }


        if (c=='/') {
            c = fgetc(fp);
            if (c=='/') {
                while ((c = fgetc(fp)) != EOF) {
                    if (c=='\n') {
                        lineno++;
                        break;
                    }
                }
                continue;
            }
            else if (c=='*') {
                while ((c = fgetc(fp)) != EOF) {
                    if (c=='\n') lineno++;
                    if (c=='*') {
                        c = fgetc(fp);
                        if (c=='\n') lineno++;
                        if (c=='/') {
                            break;
                        } else {
                            continue;
                        }
                    }
                }
                continue;
            }
        }


        if (c=='(') {
            while ((c = fgetc(fp)) != EOF) {
                if (c=='\n') lineno++;
                if (c==')') break;
            }
            continue;
        }


        if (c=='[') {
            while ((c = fgetc(fp)) != EOF) {
                if (c=='\n') lineno++;
                if (c==']') break;
            }
            continue;
        }


        if (isalpha(c)) {
            token[0] = (char)c;
            for (int i = 1; i < BUF_SIZE; i++) {
                c = fgetc(fp);
                // TODO: やる気があれば英数字以外を追加する
                if (isalnum(c)) {
                    token[i] = (char)c;
                } else {
                    ungetc(c, fp);
                    token[i] = '\0';
                    break;
                }
            }
        } else {
            continue;
        }


        // printf("%s\n", token);
        // printf("%c", c);
        // printf("%c=%d, ", c, c);


        if (!strcmp(token, "AnyVal") ||
                !strcmp(token, "Char") ||
                !strcmp(token, "Double") ||
                !strcmp(token, "Float") ||
                !strcmp(token, "Long") ||
                !strcmp(token, "Int") ||
                !strcmp(token, "Short") ||
                !strcmp(token, "Byte") ||
                !strcmp(token, "Boolean") )
            continue;
        if (!strcmp(token, "Any") ||
                !strcmp(token, "AnyRef") ||
                !strcmp(token, "ScalaObject") ||
                !strcmp(token, "String") ||
                !strcmp(token, "Iterable") ||
                !strcmp(token, "Seq") ||
                !strcmp(token, "Nil") ||
                !strcmp(token, "List") ||
                !strcmp(token, "Array") ||
                !strcmp(token, "Vector") ||
                !strcmp(token, "Map") ||
                !strcmp(token, "Set") ||
                !strcmp(token, "Option") ||
                !strcmp(token, "Some") ||
                !strcmp(token, "None") ||
                !strcmp(token, "Null") ||
                !strcmp(token, "Nothing") )
            continue;
        if (!strcmp(token, "while") ||
                !strcmp(token, "case") ||
                !strcmp(token, "for") ||
                !strcmp(token, "if") ||
                !strcmp(token, "else") ||
                !strcmp(token, "new") ||
                !strcmp(token, "val") ||
                !strcmp(token, "var") ||
                !strcmp(token, "override") ||
                !strcmp(token, "abstract") ||
                !strcmp(token, "extends") )
            continue;
        if (!strcmp(token, "class")) {
            next_symbol_is_class = 1;
            continue;
        }
        if (!strcmp(token, "object")) {
            next_symbol_is_object = 1;
            continue;
        }
        if (!strcmp(token, "trait")) {
            next_symbol_is_trait = 1;
            continue;
        }
        if (!strcmp(token, "def")) {
            next_symbol_is_function = 1;
            continue;
        }


        if (next_symbol_is_class) {
            param->put(PARSER_DEF,
                    token, lineno, param->file, token, param->arg);
            next_symbol_is_class = 0;
        }
        else if (next_symbol_is_object) {
            param->put(PARSER_DEF,
                    token, lineno, param->file, token, param->arg);
            next_symbol_is_object = 0;
        }
        else if (next_symbol_is_trait) {
            param->put(PARSER_DEF,
                    token, lineno, param->file, token, param->arg);
            next_symbol_is_trait = 0;
        }
        else if (next_symbol_is_function) {
            param->put(PARSER_DEF,
                    token, lineno, param->file, token, param->arg);
            next_symbol_is_function = 0;
        }
        else {
            param->put(PARSER_REF_SYM,
                    token, lineno, param->file, token, param->arg);
        }


    }
    fclose(fp);
}
