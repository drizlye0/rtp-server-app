import { NitroModules } from 'react-native-nitro-modules';
import type { RtpServer } from './RtpServer.nitro';

export type { RtpServerConfig } from './RtpServer.nitro.ts'

export const HybridRtpServer = NitroModules.createHybridObject<RtpServer>('RtpServer');

