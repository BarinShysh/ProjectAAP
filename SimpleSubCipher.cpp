#include <iostream>
#include <string>
#include "SimpleSubCipher.h"
/**
 * @brief Encode a message using a simple substitution cipher.
 *
 * This function encodes a given message using a simple substitution cipher,
 * where each character in the message is replaced according to the provided
 * key.
 *
 * @param alphabet The alphabet used for encoding.
 * @param text The message to be encoded.
 * @param key The substitution key (must be a permutation of the alphabet).
 * @return The encoded message.
 * @note If the size of the key does not match the size of the alphabet, returns
 * an error message.
 */
std::string EncodeSimple(std::string alphabet, std::string text,
                         std::string key) {
  int ind;
  std::string encoded_text;
  if (key.size() == alphabet.size()) {
    for (int i = 0; i < text.size(); i++) {
      ind = alphabet.find(text[i]);
      encoded_text += key[ind];
    }
    return encoded_text;
  } else
    return "Error. Key entered incorrectly.";
}
/**
 * @brief Decode a message encoded with a simple substitution cipher.
 *
 * This function decodes a message that has been encoded using a simple
 * substitution cipher with the provided key.
 *
 * @param alphabet The alphabet used for decoding.
 * @param text The encoded message to be decoded.
 * @param key The substitution key used for encoding (must be a permutation of
 * the alphabet).
 * @return The decoded message.
 * @note If the size of the key does not match the size of the alphabet, returns
 * an error message.
 */
std::string DecodeSimple(std::string alphabet, std::string text,
                         std::string key) {
  int ind;
  std::string Decoded_text;
  if (key.size() == alphabet.size()) {
    for (int i = 0; i < text.size(); i++) {
      ind = key.find(text[i]);
      Decoded_text += alphabet[ind];
    }
    return Decoded_text;
  } else
    return "Error. Key entered incorrectly.";
}