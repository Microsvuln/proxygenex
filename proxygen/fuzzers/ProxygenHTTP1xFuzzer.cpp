#include <cstdint>
#include <string>
#include "proxygen/lib/http/HTTPMethod.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size != sizeof(proxygen::HTTPMethod)) {
    return 0;
  }
  proxygen::HTTPMethod method = *reinterpret_cast<const proxygen::HTTPMethod*>(Data);
  std::string methodStr = proxygen::methodToString(method);
  return 0;
}
