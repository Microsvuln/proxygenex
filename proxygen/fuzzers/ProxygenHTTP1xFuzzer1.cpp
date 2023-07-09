
#include <folly/portability/GFlags.h>
#include <glog/logging.h>
#include <proxygen/lib/http/codec/HTTP1xCodec.h>
#include <proxygen/lib/http/codec/test/TestUtils.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 3) {
    return 0;
  }
  size_t part = Size / 3;
  proxygen::HTTPHeaders headers;
  headers.set(folly::StringPiece((const char *)Data, part),
              std::string((const char *)Data + part, part));
  return 0;
}
