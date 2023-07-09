#include <cstdint> // for uint8_t and size_t
#include <memory> // for std::unique_ptr and std::make_unique
#include <folly/io/async/EventBase.h> // for folly::EventBase
#include <folly/io/IOBuf.h> // for folly::IOBuf
#include <proxygen/lib/http/session/test/MockQuicSocketDriver.h>
#include <proxygen/lib/httpserver/HQUpstreamSession.h> // for proxygen::HQUpstreamSession
#include <proxygen/lib/httpserver/H3DatagramAsyncSocket.h> // for proxygen::H3DatagramAsyncSocket
#include <proxygen/lib/httpserver/H3DatagramAsyncSocketTest.h> // for proxygen::H3DatagramAsyncSocketTest
#include <MockUDPReadCallback.h> // for MockUDPReadCallback


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  folly::EventBase eventBase;
  std::unique_ptr<quic::MockQuicSocketDriver> socketDriver = 
    std::make_unique<quic::MockQuicSocketDriver>(&eventBase);
  std::unique_ptr<proxygen::H3DatagramAsyncSocket> datagramSocket = 
    std::make_unique<proxygen::H3DatagramAsyncSocket>(socketDriver.get());
  MockUDPReadCallback readCallbacks;
  proxygen::HQUpstreamSession* session = nullptr;
  proxygen::H3DatagramAsyncSocket::Options options;
  char buf[kMaxDatagramSize];

  proxygen::H3DatagramAsyncSocketTest testObj;
  testObj.setUpstreamSession(session);
  
  // Create a unique_ptr for the datagram from the fuzzer data
  auto datagram = folly::IOBuf::copyBuffer(Data, Size);

  // Send the datagram
  testObj.sendDatagramUpstream(std::move(datagram));

  return 0;
}
