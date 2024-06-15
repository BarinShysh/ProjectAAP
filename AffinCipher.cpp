#include "AffinCipher.h"

#include <iostream>
#include <string>
/**
 * @brief Encode a text using the Affine cipher.
 *
 * This function encodes a given text using the Affine cipher algorithm,
 * which involves shifting each character in the text by a certain linear
 * transformation defined by parameters 'a' and 'b'.
 *
 * @param alphabet The alphabet used for encoding.
 * @param text The text to be encoded.
 * @param a The first key for the Affine cipher (must be coprime with the size
 * of alphabet).
 * @param b The second key for the Affine cipher.
 * @return The encoded text.
 */
std::string EncodeAffin(std::string alphabet, std::string text, int a, int b) {
  std::string rezult;
  std::cout << "Enter the first key\n";
  int mod = alphabet.size();
  for (int i = 0; i < text.size(); i++)
    rezult += alphabet[((a * alphabet.find(text[i])) + b) % mod];
  return rezult;
}
/**
 * @brief Decode a text encoded with the Affine cipher.
 *
 * This function decodes a text that has been encoded using the Affine cipher
 * algorithm. It reverses the encoding process based on the same keys 'a' and
 * 'b'.
 *
 * @param alphabet The alphabet used for decoding.
 * @param text The encoded text to be decoded.
 * @param a The first key used in the Affine cipher (must be coprime with the
 * size of alphabet).
 * @param b The second key used in the Affine cipher.
 * @return The decoded text.
 */
std::string DecodeAffin(std::string alphabet, std::string text, int a, int b) {
  std::string rezult;
  int mod = alphabet.size();
  int r = 0;
  while (true) {
    if (r % a == 0 && r % mod == 1) break;
    r += 1;
  }
  int a1 = ((r / a) % mod);
  
  int mx = 0;
  if (a >= mod)
    mx = a;
  else
    mx = mod;
  int nod = 1;
  for (int i = 1; i <= mx; i++) {
    if (a % i == 0 && mod % i == 0) nod = i;
  }
  if (nod == 1) {
    for (int i = 0; i < text.size(); i++) {
      rezult += alphabet[((alphabet.find(text[i]) - b + mod) * a1) % mod];
    }
    return rezult;
  } 
}