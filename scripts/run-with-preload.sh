#!/bin/sh
# Usage: run-with-preload.sh CMD ...
#
# Set the LD_PRELOAD environment variable to the value of the
# $EGLIBC_TEST_LD_PRELOAD environment variable, and run CMD ... .
#
# The EGLIBC test suite uses this to set LD_PRELOAD for test programs.
# If we simply say:
#    LD_PRELOAD=smootz \
#    $(cross-test-wrapper) \
#    tst-foo arg1 arg2
# then the LD_PRELOAD setting inteferes with the execution of
# $(cross-test-wrapper).  If we instead say:
#    EGLIBC_TEST_LD_PRELOAD=smootz \
#    $(cross-test-wrapper) \
#    run-with-preload.sh \
#    tst-foo arg1 arg2
# then things work fine.

LD_PRELOAD="$EGLIBC_TEST_LD_PRELOAD" exec "$@"
