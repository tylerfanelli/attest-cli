// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "kbs_types.h"

#define BLK_SIZE 256

static int kbs_request_json_marshal(char *, kbs_request_t *);
static void kbs_request_snp_json_marshal(char *, char *, void *);

char *
kbs_request_marshal(kbs_request_t *req)
{
        int ret;
        char *json;

        json = (char *) malloc(JSON_MAX_LEN);
        if (json == NULL) {
                fprintf(stderr, "ERROR: malloc(3)\n");
                return NULL;
        }
        *json = '\0';

        ret = kbs_request_json_marshal(json, req);

        return (ret) ? json : NULL;
}

static int
kbs_request_json_marshal(char *json, kbs_request_t *req)
{
        char *blk;

        blk = (char *) malloc(BLK_SIZE);
        if (blk == NULL) {
                fprintf(stderr, "ERROR: malloc(3)\n");
                return 0;
        }
        *blk = '\0';

        strcpy(json, "{");

        switch (req->tee) {
        case TEE_SEV:
                // TODO
                break;
        case TEE_SGX:
                // TODO
                break;
        case TEE_SNP:
                kbs_request_snp_json_marshal(json, blk, req->extra_params);
                break;
        case TEE_TDX:
                // TODO
                break;
        default:
                // TODO
                break;
        }

        sprintf(blk, "\"tee\":\"%s\",", tee_str(req->tee));
        strcat(json, blk);

        sprintf(blk, "\"version\":\"%s\"", req->version);
        strcat(json, blk);

        strcat(json, "}");

        free(blk);

        return 1;
}

static void
kbs_request_snp_json_marshal(char *json, char *blk, void *extra_params)
{
        snp_request_t *snp;

        snp = (snp_request_t *) extra_params;

        strcpy(blk, "\"extra-params\":\"{");
        strcat(json, blk);

        sprintf(blk, "\"workload_id\":\"%s\"}\",", snp->workload_id);
        strcat(json, blk);
}
