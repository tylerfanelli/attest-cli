// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "kbs_types.h"

#define JSON_VAL_MAX 128

static char *json_find_label(char *, const char *);
static int json_collect_value(char *, char **);

char *
tee_str(int tee)
{
        switch (tee) {
        case TEE_SEV:
                return "sev";
        case TEE_SGX:
                return "sgx";
        case TEE_SNP:
                return "snp";
        case TEE_TDX:
                return "tdx";
        default:
                fprintf(stderr, "ERROR: tee_str(): Invalid tee input\n");
                return NULL;
        }
}

int
json_parse_label(char *json_str, char *label, char **location)
{
        char *val_start;

        val_start = json_find_label(json_str, label);
        if (!val_start)
                return 0;

        return json_collect_value(val_start, location);
}

static char *
json_find_label(char *json_str, const char *label)
{
        int ret;
        size_t json_sz, label_sz;
        char buf[JSON_VAL_MAX], *p;

        json_sz = strlen(json_str);
        sprintf(buf, "\"%s\":\"", label);
        label_sz = strlen(buf);
        p = json_str;

        while (json_sz >= (label_sz + 2)) {
                ret = strncmp(p, buf, label_sz);
                if (ret == 0)
                        return (p + label_sz);

                p++;
                json_sz--;
        }

        return NULL;
}

static int
json_collect_value(char *start, char **location)
{
        char *loc_str;

        loc_str = *location;

        while (*start != '"' && *start != '\0')
                *(loc_str++) = *(start++);

        if (*start == '\0')
                return 0;

        *(loc_str) = '\0';

        return 1;
}
