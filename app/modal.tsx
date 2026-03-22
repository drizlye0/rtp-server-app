import { StyleSheet, View, Text } from 'react-native';

export default function ModalScreen() {
  return (
    <View style={styles.container}>
      <Text>this is a modal screen</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    padding: 20,
  },
  link: {
    marginTop: 15,
    paddingVertical: 15,
  },
});
