// SPDX-License-Identifier: Apache-2.0

#include <stdlib.h>

#include "kbs_types.h"

#define CHALLENGE_BUF_MAX 256

int
kbs_challenge_parse(char *str, kbs_challenge_t *challenge)
{
        int ret;
        char *eparams, *nonce;

        eparams = malloc(CHALLENGE_BUF_MAX);
        if (!eparams)
                return 0;

        nonce = malloc(CHALLENGE_BUF_MAX);
        if (!nonce) {
                free(eparams);
                return 0;
        }

        ret = json_parse_label(str, "extra-params", &eparams);
        if (!ret) {
                free(eparams);
                free(nonce);

                return 0;
        }

        ret = json_parse_label(str, "nonce", &eparams);
        if (!ret) {
                free(eparams);
                free(nonce);

                return 0;
        }

        challenge->extra_params = (void *) eparams;
        challenge->nonce = nonce;

        return 1;
}
