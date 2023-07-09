#include <cstdint>  // for uint8_t and size_t
#include <proxygen/lib/http/session/HTTPSessionStats.h>  // for proxygen::TLConnectionStats
#include <folly/Optional.h>  // for folly::Optional


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  proxygen::TLConnectionStats stats("test");

  // Use the data to create a size_t for the functions that require it
  size_t dataSize = 0;
  if (Size >= sizeof(size_t)) {
    dataSize = *reinterpret_cast<const size_t*>(Data);
    Data += sizeof(size_t);
    Size -= sizeof(size_t);
  }

  // Use the remaining data to create an optional uint16_t for recordResponse
  folly::Optional<uint16_t> responseCode = folly::none;
  if (Size >= sizeof(uint16_t)) {
    responseCode = folly::Optional<uint16_t>(*reinterpret_cast<const uint16_t*>(Data));
    Data += sizeof(uint16_t);
    Size -= sizeof(uint16_t);
  }

  // Call the functions with the generated data
  stats.recordConnectionOpen();
  stats.recordConnectionClose();
  stats.recordRequest();
  stats.recordResponse(responseCode);
  stats.recordDuration(dataSize);
  stats.addEgressBytes(dataSize);
  stats.addIngressBytes(dataSize);
  stats.addEgressBodyBytes(dataSize);
  stats.addIngressBodyBytes(dataSize);

  return 0;
}
