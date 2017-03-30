#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

#define LIM " \t(){}."

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
