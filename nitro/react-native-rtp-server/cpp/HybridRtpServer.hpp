#pragma once

#include <HybridRtpServerSpec.hpp>
#include <android/log.h>
#include <uvgrtp/lib.hh>

constexpr char REMOTE_ADDRESS[] = "10.0.2.2";
constexpr uint16_t REMOTE_PORT = 8000;

constexpr size_t PAYLOAD_LEN = 100;
constexpr int AMOUNT_OF_TEST_PACKETS = 100;
constexpr auto END_WAIT = std::chrono::seconds(5);

namespace margelo::nitro::rtpserver {
class HybridRtpServer : public HybridRtpServerSpec {
public:
  HybridRtpServer();
  ~HybridRtpServer();

  void printHelloWorld() override;
  void sendFrame(const EncodedFrame& frame) override;
  bool start(const RtpServerConfig& config) override;
  void stop() override;

private:
  uvgrtp::context _ctx;
  uvgrtp::session* _session;
  uvgrtp::media_stream* _avcStream;

  bool _isRunning;
};
} // namespace margelo::nitro::rtpserver
