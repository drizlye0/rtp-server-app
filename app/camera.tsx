import { useRouter } from 'expo-router';
import { View, Alert, StyleSheet } from 'react-native'
import { HybridRtpServer } from '@/nitro/react-native-rtp-server/src';
import { createVideoEncoder, EncodedFrame, EncoderFormat } from 'react-native-android-encoder';
import { SafeAreaView } from 'react-native-safe-area-context';
import { Camera, Frame, useCameraDevice, useCameraFormat, useCameraPermission, useFrameProcessor } from 'react-native-vision-camera'

export default function CameraScreen() {
  const router = useRouter();

  const { hasPermission, requestPermission } = useCameraPermission();
  const device = useCameraDevice('back');
  const format = useCameraFormat(device, [
    { videoResolution: { width: 1280, height: 720 } },
    { videoAspectRatio: 4 / 3 },
    { fps: 30 },
  ])

  const videoEncoderFormat: EncoderFormat = {
    width: 1280,
    height: 720,
    bitRate: 2000000,
    frameRate: 30,
    mimeType: 'video/avc',
  };

  const onEncodedFrame = (frame: EncodedFrame) => {
    HybridRtpServer.sendFrame(frame);
  };

  const encoder = createVideoEncoder(videoEncoderFormat, onEncodedFrame);

  const frameProcessor = useFrameProcessor((frame: Frame) => {
    'worklet'
    encoder?.unbox().encodeFrame(frame);
  }, []);


  if (!hasPermission) {
    requestPermission()
  }

  if (!device) {
    Alert.alert('Camera', 'Camera not avaliable');
    router.back();
    return;
  }

  if (!encoder) {
    Alert.alert('Encoder', 'Encoder not avaliable');
    return;
  }

  return (
    <SafeAreaView style={{ flex: 1 }}>
      <View style={{ flex: 1 }}>
        <Camera
          isActive
          device={device}
          format={format}
          frameProcessor={frameProcessor}
          style={StyleSheet.absoluteFillObject}
        />
      </View>
    </SafeAreaView>
  )
}
