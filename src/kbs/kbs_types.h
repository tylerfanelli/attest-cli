// SPDX-License-Identifier: Apache-2.0

#define JSON_MAX_LEN 1024

#define TEST_KBS_REQUEST \
"{\"extra-params\":\"{\"workload_id\":\"id\"}\",\"tee\":\"snp\",\"version\":\"0.0.0\"}"

#define TEST_KBS_CHALLENGE \
"{\"extra-params\":\"\",\"nonce\":\"abc123def456ghi789\"}"

// kbs_util.c
char *tee_str(int);
int json_parse_label(char *, char *, char **);

enum tee {
        TEE_SEV,
        TEE_SGX,
        TEE_SNP,
        TEE_TDX,
};

typedef struct {
        char *version;
        int tee;
        void *extra_params;
} kbs_request_t;

typedef struct {
        char *workload_id;
} snp_request_t;

// kbs_request.c
char *kbs_request_marshal(kbs_request_t *);

typedef struct {
        char *nonce;
        void *extra_params;
} kbs_challenge_t;

// kbs_challenge.c
int kbs_challenge_parse(char *, kbs_challenge_t *);
