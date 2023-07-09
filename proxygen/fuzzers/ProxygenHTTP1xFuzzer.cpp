#include "proxygen/ConnectionCloseReason.h"
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < sizeof(unsigned int)) {
    return 0;
  }
  
  unsigned int index = *reinterpret_cast<const unsigned int*>(Data);
  proxygen::getConnectionCloseReasonStringByIndex(index);
  return 0;
}
