/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cstdint>
#include <string>
#include <proxygen/lib/dns/SyncDNSResolver.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  std::string hostname(reinterpret_cast<const char*>(data), size);

  try {
    proxygen::SyncDNSResolver resolver;
    std::chrono::milliseconds timeout(100);
    std::vector<folly::SocketAddress> result = resolver.resolveHostname(hostname, timeout, AF_UNSPEC, true);
  } catch (...) {
    // Ignore exceptions
  }

  return 0;
}
