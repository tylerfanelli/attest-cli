// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <stdlib.h>

#include "kbs/kbs_types.h"

int
main(int argc, char *argv[])
{
        int ret;
        char *request_json;
        kbs_request_t kbs_req;
        snp_request_t snp_req;
        kbs_challenge_t kbs_chal;

        snp_req.workload_id = "id";

        kbs_req.version = "0.0.0";
        kbs_req.tee = TEE_SNP;
        kbs_req.extra_params = (void *) &snp_req;

        request_json = kbs_request_marshal(&kbs_req);

        printf("EXPECTED:\t%s\n", TEST_KBS_REQUEST);

        if (request_json == NULL)
                printf("ERROR: JSON\n");
        else
                printf("ACTUAL:\t\t%s\n", request_json);

        ret = kbs_challenge_parse(TEST_KBS_CHALLENGE, &kbs_chal);
        if (!ret)
                printf("ERROR: kbs_challenge_parse()\n");
        else
                printf("kbs_chal {\n\tnonce: \"%s\";\n\textra-params: \"%s\";\n}\n",
                        kbs_chal.nonce, (char *) kbs_chal.extra_params);

        return 0;
}
