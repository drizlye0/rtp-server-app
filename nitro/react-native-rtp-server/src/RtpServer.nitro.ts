import type { HybridObject } from 'react-native-nitro-modules';
import { type EncodedFrame } from 'react-native-android-encoder'

export interface RtpServerConfig {
  addr: string;
  port: number;
}

export interface RtpServer extends HybridObject<{
  android: "c++"
}> {
  printHelloWorld(): void;
  sendFrame(frame: EncodedFrame): void;
  start(config: RtpServerConfig): boolean;
  testSend(): void;
  stop(): void;
}

