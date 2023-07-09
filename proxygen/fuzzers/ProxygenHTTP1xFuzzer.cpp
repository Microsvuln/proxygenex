#include <chrono>
#include <vector>
#include <proxygen/lib/pools/generators/ServerListGenerator.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    std::string name((const char*)Data, Size);
    folly::SocketAddress address;
    std::map<std::string, std::string> properties;
    proxygen::ServerListGenerator::ServerConfig config(name, address, properties);
    std::vector<proxygen::ServerListGenerator::ServerConfig> results;
    results.push_back(config);

    proxygen::ServerListGenerator generator;
    try {
        generator.listServersBlocking(&results, std::chrono::milliseconds(1000));
    } catch (...) {
        // Ignore exceptions for the purpose of fuzzing
    }

    return 0;
}
