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

        char *buf = (char *) malloc(500);

        ret = json_parse_label(TEST_KBS_CHALLENGE, "nonce", &buf);
        if (!ret)
                printf("ERROR: json_parse_label()\n");

        printf("buf: %s\n", buf);

        return 0;
}
