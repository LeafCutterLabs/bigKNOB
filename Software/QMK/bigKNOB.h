#pragma once

#include "quantum.h"

#define LAYOUT_ortho_1x4( \
    k01, k02, k03, k04\
  ) { \
    { k01, k02, k03, k04 } \
}

#define LAYOUT LAYOUT_ortho_1x4 
