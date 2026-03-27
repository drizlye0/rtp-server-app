#include <HybridRtpServer.hpp>

namespace margelo::nitro::rtpserver {

HybridRtpServer::HybridRtpServer() : HybridObject(TAG) {}
HybridRtpServer::~HybridRtpServer() {
  if (_session) {
    _session->destroy_stream(_avcStream);
    _ctx.destroy_session(_session);
  }
}

bool HybridRtpServer::start(const RtpServerConfig& config) {
  _session = _ctx.create_session(config.addr);
  if (_session == nullptr) {
    throw std::runtime_error("invalid remote address");
  }

  int flags = RCE_SEND_ONLY;
  _avcStream = _session->create_stream(config.port, RTP_FORMAT_H264, flags);
  return _isRunning = true;
}

void HybridRtpServer::stop() {
  if (!_isRunning) {
    throw std::runtime_error("rtp server not started");
  }

  if (_session) {
    _session->destroy_stream(_avcStream);
    _ctx.destroy_session(_session);
  }
}

void HybridRtpServer::printHelloWorld() {
  __android_log_print(ANDROID_LOG_INFO, "RtpServer", "Hello world");
}

void HybridRtpServer::sendFrame(const EncodedFrame& frame) {
  if (!_isRunning) {
    throw std::runtime_error("rtp server not started");
  }

  if (!_avcStream) {
    __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Stream not initialized");
    return;
  }

  auto buffer = frame.data;
  size_t size = buffer->size();
  uint8_t* data = buffer->data();

  __android_log_print(ANDROID_LOG_INFO, "RtpServer", "First bytes: %02x %02x %02x %02x %02x", data[0], data[1], data[2], data[3], data[4]);

  rtp_error_t result = _avcStream->push_frame(data, size, RTP_NO_FLAGS);

  if (result != RTP_OK) {
    __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Failed to send frame: %d", result);
  }

  // __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "send frame: %d", result);
}

void HybridRtpServer::testSend() {
  uvgrtp::context ctx;
  uvgrtp::session* session = ctx.create_session(REMOTE_ADDRESS);
  if (session == nullptr) {
    __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Remote addres not valid!");
    return;
  }

  int flags = RCE_SEND_ONLY;
  uvgrtp::media_stream* h265 = session->create_stream(REMOTE_PORT, RTP_FORMAT_H265, flags);

  if (h265) {
    for (int i = 0; i < AMOUNT_OF_TEST_PACKETS; i++) {
      std::unique_ptr<uint8_t[]> dummyFrame = std::unique_ptr<uint8_t[]>(new uint8_t[PAYLOAD_LEN]);
      memset(dummyFrame.get(), 'a', PAYLOAD_LEN);
      memset(dummyFrame.get(), 0, 3);
      memset(dummyFrame.get() + 3, 1, 1);
      memset(dummyFrame.get() + 4, 1, (19 << 1));

      if ((i + 1) % 10 == 0 || i == 0)
        __android_log_print(ANDROID_LOG_INFO, "RtpServer", "Sending frame %d / %d", i + 1, AMOUNT_OF_TEST_PACKETS);

      if (h265->push_frame(std::move(dummyFrame), PAYLOAD_LEN, RTP_NO_FLAGS) != RTP_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Failed to send RTP frame!");
      }
    }

    session->destroy_stream(h265);
  }

  if (session)
    ctx.destroy_session(session);

  __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Finished stream");
}

} // namespace margelo::nitro::rtpserver
