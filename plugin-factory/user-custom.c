#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "parser.h"

#define LIM " \t(){}[].,:;"

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
    FILE *ip;
    char buf[1024], saveline[1024], *token;
    int lineno = 0;
    int next_symbol_is_class = 0;
    int next_symbol_is_object = 0;
    int next_symbol_is_trait = 0;
    int next_symbol_is_function = 0;
    bool is_comment = false;
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
            if (strstr(token, "/*") != NULL) {
                is_comment = true;
                continue;
            }
            if (strstr(token, "*/") != NULL) {
                is_comment = false;
                continue;
            }
            if (is_comment) {
                break;
            }
            if (!strcmp(token, "//"))
                break;
            if (isdigit(*token))
                continue;
            if (*token == '\'')
                continue;
            if (*token == '\"') {
                if (token[strlen(token) - 1] == '\"' && strlen(token) != 1)
                    continue;
                for (token = strtok(NULL, LIM); token != NULL && token[strlen(token) - 1] != '\"'; token = strtok(NULL, LIM))
                    ;
                continue;
            }
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
            if (isalpha(*token)) {
                if (next_symbol_is_class) {
                    param->put(PARSER_DEF,
                            token, lineno, param->file, saveline, param->arg);
                    next_symbol_is_class = 0;
                }
                else if (next_symbol_is_object) {
                    param->put(PARSER_DEF,
                            token, lineno, param->file, saveline, param->arg);
                    next_symbol_is_object = 0;
                }
                else if (next_symbol_is_trait) {
                    param->put(PARSER_DEF,
                            token, lineno, param->file, saveline, param->arg);
                    next_symbol_is_trait = 0;
                }
                else if (next_symbol_is_function) {
                    param->put(PARSER_DEF,
                            token, lineno, param->file, saveline, param->arg);
                    next_symbol_is_function = 0;
                }
                else {
                    param->put(PARSER_REF_SYM,
                            token, lineno, param->file, saveline, param->arg);
                }
            }
        }
    }
    fclose(ip);
}
