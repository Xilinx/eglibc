# Setup file for subdirectory Makefiles that define EGLIBC option groups.

# Read the default settings for all options.
include $(..)option-groups.defaults

# Read the developer's option group selections, overriding the
# defaults from option-groups.defaults.
-include $(objdir)/option-groups.config

# Establish 'routines-y', etc. as simply expanded variables.
routines-y     :=
others-y       :=
install-bin-y  :=
install-sbin-y :=
extra-objs-y   :=
tests-y        :=
test-srcs-y    :=
