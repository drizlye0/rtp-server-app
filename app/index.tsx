import { View, Text, StyleSheet, Alert, Button } from "react-native"
import { SafeAreaView } from "react-native-safe-area-context"
import { HybridRtpServer, type RtpServerConfig } from "@/nitro/react-native-rtp-server/src"
import { Link, useRouter } from "expo-router"

const config: RtpServerConfig = {
  addr: "10.0.2.2",
  port: 8080
}

export default function HomeScreen() {
  const router = useRouter();

  const startServer = () => {
    try {
      const result = HybridRtpServer.start(config);
      if (!result) {
        Alert.alert("RtpServer", "Failed to start rpt server")
      }
      console.log("server started")
    } catch (error) {
      Alert.alert("RtpServer", `an error as occurred: ${error}`);
    }
  }

  const stopServer = () => {
    HybridRtpServer.stop();
    console.log("server stopped")
  }

  const sendPackages = () => {
    HybridRtpServer.testSend();
  }

  return (
    <SafeAreaView style={{ flex: 1 }}>
      <View style={styles.container}>
        <Text style={styles.title}>Hello world</Text>
        <Button title="start rtp server" onPress={startServer} />
        <Button title="stop rtp server" onPress={stopServer} />
        <Button title="test send packages" onPress={sendPackages} />
        <Button title="go to camera screen" onPress={() => router.navigate('/camera')} />
      </View>
    </SafeAreaView>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center"
  },

  title: {
    fontSize: 18,
    fontWeight: "bold",
  }
})
