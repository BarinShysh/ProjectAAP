#include <iostream>
#include <string>
#include "VigenereCipher.h"
/**
 * @brief Calculate the index of a character in the alphabet.
 *
 * This function returns the index of a character `s` in the provided alphabet.
 *
 * @param s The character whose index is to be found.
 * @return The index of the character in the alphabet (0-indexed).
 */
int keycode(char s) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < alphabet.size(); i++) {
    if (s == alphabet[i]) return i;
  }
  return 0;
}
/**
 * @brief Encode a message using the Vigenere cipher.
 *
 * This function encodes a given message using the Vigenere cipher with the
 * provided key.
 *
 * @param alphabet The alphabet used for encoding.
 * @param text The message to be encoded.
 * @param key The encryption key for the Vigenere cipher.
 * @return The encoded message.
 */
std::string EncodeVigenere(std::string alphabet, std::string text,
                           std::string key) {
  std::string cipher;
  for (int i = 0; i < text.size(); i++) {
    cipher += alphabet[(keycode(text[i]) + keycode(key[i % key.size()])) %
                       alphabet.size()];
  }
  return cipher;
}

/**
 * @brief Decode a message encoded with the Vigenere cipher.
 *
 * This function decodes a message that has been encoded using the Vigenere
 * cipher with the provided key.
 *
 * @param alphabet The alphabet used for decoding.
 * @param text The encoded message to be decoded.
 * @param key The decryption key for the Vigenere cipher.
 * @return The decoded message.
 */
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