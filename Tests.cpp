#include <gtest/gtest.h>

#include "AffinCipher.h"
#include "SimpleSubCipher.h"
#include "VigenereCipher.h"


int keycode(char s) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < alphabet.size(); i++) {
    if (s == alphabet[i]) return i;
  }
  return 0;
}

std::string EncodeVigenere(std::string alphabet, std::string text,
                           std::string key) {
  std::string cipher;
  for (int i = 0; i < text.size(); i++) {
    cipher += alphabet[(keycode(text[i]) + keycode(key[i % key.size()])) %
                       alphabet.size()];
  }
  return cipher;
}

std::string DecodeVigenere(std::string alphabet, std::string text,
                           std::string key) {
  std::string code;
  for (int i = 0; i < text.size(); i++) {
    code += alphabet[(keycode(text[i]) - keycode(key[i % key.size()]) +
                      alphabet.size()) %
                     alphabet.size()];
  }
  return code;
}

TEST(AffineCipherTest, EncodeTest) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  EXPECT_EQ(EncodeAffin(alphabet, "HELLO", 5, 8), "RCLLA");
}

TEST(AffineCipherTest, DecodeTest) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  EXPECT_EQ(DecodeAffin(alphabet, "RCLLA", 5, 8), "HELLO");
}

TEST(SimpleCipherTest, EncodeSimpleTest) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_EQ(EncodeSimple(alphabet, "hello", "defghijklmnopqrstuvwxyzabc"),
            "khoor");
}

TEST(SimpleCipherTest, DecodeSimpleTest) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_EQ(DecodeSimple(alphabet, "khoor", "defghijklmnopqrstuvwxyzabc"),
            "hello");
}

TEST(SimpleCipherTest, IncorrectKeySizeTest) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_EQ(EncodeSimple(alphabet, "hello", "abc"),
            "Error. Key entered incorrectly.");
  EXPECT_EQ(DecodeSimple(alphabet, "khoor", "abc"),
            "Error. Key entered incorrectly.");
}

TEST(SimpleCipherTest, IncorrectKeyContentTest) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_EQ(EncodeSimple(alphabet, "hello", "defghijklmnopqrstuvwxyz"),
            "Error. Key entered incorrectly.");
  EXPECT_EQ(DecodeSimple(alphabet, "khoor", "defghijklmnopqrstuvwxyz"),
            "Error. Key entered incorrectly.");
}

TEST(VigenereCipherTest, EncodeVigenereTest) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  EXPECT_EQ(EncodeVigenere(alphabet, "HELLO", "KEY"), "RIJVS");
}

TEST(VigenereCipherTest, DecodeVigenereTest) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  EXPECT_EQ(DecodeVigenere(alphabet, "RIJVS", "KEY"), "HELLO");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
