#include <folly/portability/GFlags.h>
#include <folly/SocketAddress.h>
#include <glog/logging.h>
#include <proxygen/lib/http/codec/HTTP1xCodec.h>
#include <proxygen/lib/http/codec/test/TestUtils.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 3) {
    return 0;
  }

  // Initialize Folly and Fizz
  folly::init(nullptr, nullptr, true);
  fizz::client::FizzClientContext context;
  fizz::CertificateVerifier verifier;

  // Create an EventBase
  folly::EventBase eventBase;

  // Create a SocketAddress from the fuzzer data
  folly::SocketAddress connectAddr(reinterpret_cast<const char*>(Data), Size);

  // Create a shared_ptr to the FizzClientContext and CertificateVerifier
  std::shared_ptr<const fizz::client::FizzClientContext> contextPtr(&context);
  std::shared_ptr<const fizz::CertificateVerifier> verifierPtr(&verifier);

  // Create an HTTPConnectorWithFizz and attempt to connect
  proxygen::HTTPConnectorWithFizz connector;
  connector.connectFizz(&eventBase, connectAddr, contextPtr, verifierPtr);

  // Run the EventBase loop
  eventBase.loop();

  return 0;
}
