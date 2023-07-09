#include <proxygen/lib/stats/BaseStats.h>
#include <proxygen/lib/http/stats/ResponseCodeStatsMinute.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1)
    return 0;

  std::string name(reinterpret_cast<const char*>(Data), Size);
  proxygen::ResponseCodeStatsMinute stats(name);

  for(size_t i = 0; i < Size; i++) {
    int status = static_cast<int>(Data[i]);
    stats.addStatus(status);
  }

  return 0;
}
