PROG_NAME = attest-cli

SRC = ./src
KBS = $(SRC)/kbs

CURL_FLAG = -lcurl

UPROGS = $(SRC)/attest_cli.c	\
	 $(KBS)/kbs_types.h	\
	 $(KBS)/kbs_request.c	\
	 $(KBS)/kbs_util.c	\
	 $(KBS)/kbs_challenge.c	\

all:
	gcc -Wall -o $(PROG_NAME) $(UPROGS) $(CURL_FLAG)

clean:
	rm -f $(PROG_NAME)
