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

  rtp_error_t result = _avcStream->push_frame(data, size, RTP_NO_H26X_SCL);

  if (result != RTP_OK) {
    __android_log_print(ANDROID_LOG_ERROR, "RtpServer", "Failed to send frame: %d", result);
  }
}

} // namespace margelo::nitro::rtpserver
