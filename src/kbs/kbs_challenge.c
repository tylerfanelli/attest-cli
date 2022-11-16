// SPDX-License-Identifier: Apache-2.0

#include <stdlib.h>

#include "kbs_types.h"

int
kbs_challenge_parse(char *str, kbs_challenge_t *challenge)
{
        int ret;
        char *eparams, *nonce;

        eparams = malloc(BUF_MAX);
        if (!eparams)
                return 0;

        nonce = malloc(BUF_MAX);
        if (!nonce)
                goto err_eparams;

        ret = json_parse_label(str, "extra-params", &eparams);
        if (!ret)
                goto err;

        ret = json_parse_label(str, "nonce", &eparams);
        if (!ret)
                goto err;

        challenge->extra_params = (void *) eparams;
        challenge->nonce = nonce;

        return 1;


err:
        free(nonce);

err_eparams:
        free(eparams);

        return 0;
}
