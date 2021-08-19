# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= PKMNEMER
ICON ?= icon.png
DESCRIPTION ?= "POKEMON EMERALD CE V0.0.3A"
COMPRESSED ?= NO
ARCHIVED ?= NO
HAS_PRINTF := NO
CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz -Wno-reorder-ctor

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
