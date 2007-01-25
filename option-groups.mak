# Setup file for subdirectory Makefiles that define EGLIBC option groups.

# EGLIBC shouldn't need to override this.  However, the
# cross-build-friendly localedef includes this makefile to get option
# group variable definitions; it uses a single build tree for all the
# multilibs, and needs to be able to specify a different option group
# configuration file for each multilib.
option_group_config_file ?= $(objdir)/option-groups.config

# Read the default settings for all options.
include $(..)option-groups.defaults

# Read the developer's option group selections, overriding the
# defaults from option-groups.defaults.
-include $(option_group_config_file)

# Establish 'routines-y', etc. as simply expanded variables.
routines-y     :=
others-y       :=
install-bin-y  :=
install-sbin-y :=
extra-objs-y   :=
tests-y        :=
xtests-y       :=
test-srcs-y    :=
