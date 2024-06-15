#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "AffinCipher.h"
#include "SimpleSubCipher.h"
#include "VigenereCipher.h"
/**
 * @brief Encode a message using the Caesar cipher.
 *
 * This function encodes a given message using the Caesar cipher algorithm,
 * which shifts each character in the message by a specified shift value.
 *
 * @param alphabet The alphabet used for encoding.
 * @param message The message to be encoded.
 * @param shift The shift value for the Caesar cipher.
 * @return The encoded message.
 */
std::string encodeCaesar(const std::string &alphabet,
                         const std::string &message, int shift) {
  std::string encoded_message;
  for (char c : message) {
    if (alphabet.find(c) != std::string::npos) {
      int index = (alphabet.find(c) + shift) % alphabet.size();
      encoded_message += alphabet[index];
    } else {
      encoded_message += c;
    }
  }
  return encoded_message;
}
/**
 * @brief Decode a message encoded with the Caesar cipher.
 *
 * This function decodes a message that has been encoded using the Caesar cipher
 * algorithm. It reverses the encoding process based on the specified shift
 * value.
 *
 * @param alphabet The alphabet used for decoding.
 * @param message The encoded message to be decoded.
 * @param shift The shift value used in the Caesar cipher.
 * @return The decoded message.
 */
std::string decodeCaesar(const std::string &alphabet,
                         const std::string &message, int shift) {
  std::string decoded_message;
  for (char c : message) {
    if (alphabet.find(c) != std::string::npos) {
      int index =
          (alphabet.find(c) - shift + alphabet.size()) % alphabet.size();
      decoded_message += alphabet[index];
    } else {
      decoded_message += c;
    }
  }
  return decoded_message;
}
/**
 * @brief Class representing an Enigma machine.
 *
 * The EnigmaMachine class simulates the functionality of an Enigma machine,
 * which was a cipher device used during World War II for encoding and decoding
 * messages.
 */
class EnigmaMachine {
 public:
  /**
   * @brief Constructor for EnigmaMachine class.
   *
   * Initializes the Enigma machine with a set of rotors and a reflector.
   *
   * @param rotors A vector of strings representing the rotors of the Enigma
   * machine.
   * @param reflector A string representing the reflector of the Enigma machine.
   */
  EnigmaMachine(const std::vector<std::string> &rotors,
                const std::string &reflector)
      : rotors_(rotors),
        reflector_(reflector),
        rotor_positions_(rotors.size(), 0) {}
  /**
   * @brief Set the positions of the rotors.
   *
   * Sets the starting positions of the Enigma machine's rotors.
   *
   * @param positions A vector of integers representing the positions of the
   * rotors.
   * @throw std::invalid_argument if the number of positions does not match the
   * number of rotors.
   */
  void setRotorPositions(const std::vector<int> &positions) {
    if (positions.size() != rotors_.size()) {
      throw std::invalid_argument(
          "Number of positions must match number of rotors");
    }
    rotor_positions_ = positions;
  }
  /**
   * @brief Encode a single character using the Enigma machine.
   *
   * Encodes a single uppercase letter using the current rotor positions and
   * reflector settings of the Enigma machine.
   *
   * @param ch The character to encode (must be an uppercase letter A-Z).
   * @return The encoded character.
   * @throw std::invalid_argument if the input character is not an uppercase
   * letter.
   */
  char encodeChar(char ch) {
    if (ch < 'A' || ch > 'Z') {
      throw std::invalid_argument(
          "Input character must be an uppercase letter A-Z");
    }
    stepRotors();
    return transformCharacter(ch);
  }
  /**
   * @brief Encode a message using the Enigma machine.
   *
   * Encodes a message using the current rotor positions and reflector settings
   * of the Enigma machine.
   *
   * @param message The message to encode.
   * @return The encoded message.
   */
  std::string encodeMessage(const std::string &message) {
    std::string encoded_message;
    for (char ch : message) {
      if (ch >= 'A' && ch <= 'Z') {
        encoded_message += encodeChar(ch);
      } else {
        encoded_message += ch;
      }
    }
    return encoded_message;
  }
  /**
   * @brief Decode a message using the Enigma machine.
   *
   * Decodes a message encoded using the Enigma machine by simulating the
   * encoding process in reverse.
   *
   * @param message The encoded message to decode.
   * @return The decoded message.
   */
  std::string decodeMessage(const std::string &message) {
    return encodeMessage(message);
  }

 private:
  std::vector<std::string> rotors_;
  std::string reflector_;
  std::vector<int> rotor_positions_;
  /**
   * @brief Step the rotors of the Enigma machine.
   *
   * Advances the rotor positions of the Enigma machine after each character
   * encoding. When a rotor completes a full revolution (26 steps), it resets to
   * the starting position.
   */
  void stepRotors() {
    for (size_t i = 0; i < rotors_.size(); ++i) {
      if (++rotor_positions_[i] < 26) {
        break;
      }
      rotor_positions_[i] = 0;
    }
  }
  /**
   * @brief Transform a character through the Enigma machine.
   *
   * Performs the character transformation through the Enigma machine's rotors
   * and reflector.
   *
   * @param ch The character to transform.
   * @return The transformed character.
   */
  char transformCharacter(char ch) {
    int index = ch - 'A';
    for (size_t i = 0; i < rotors_.size(); ++i) {
      index = (index + rotor_positions_[i]) % 26;
      index = rotors_[i][index] - 'A';
      index = (index - rotor_positions_[i] + 26) % 26;
    }
    index = reflector_[index] - 'A';
    for (int i = rotors_.size() - 1; i >= 0; --i) {
      index = (index + rotor_positions_[i]) % 26;
      index = std::find(rotors_[i].begin(), rotors_[i].end(), 'A' + index) -
              rotors_[i].begin();
      index = (index - rotor_positions_[i] + 26) % 26;
    }
    return 'A' + index;
  }
};

int main() {
  std::vector<std::string> rotors = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                                     "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                                     "BDFHJLCPRTXVZNYEIWGAKMUSQO"};
  std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
  EnigmaMachine enigma(rotors, reflector);

  while (true) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string text;
    std::cout << "Enter your text: ";
    std::cin >> text;
    for (auto &c : text) c = toupper(c);

    int choice_cipher;
    std::cout << "\nChoose your cipher:\n"
              << "(1) - Simple substitution cipher\n"
              << "(2) - Vigenere cipher\n"
              << "(3) - Affine cipher\n"
              << "(4) - Enigma cipher\n"
              << "(5) - Caesar cipher\n";
    std::cin >> choice_cipher;

    if (choice_cipher == 1) {
      std::string key;
      std::cout << "Enter your key: ";
      std::cin >> key;
      for (auto &c : key) c = toupper(c);

      int choice;
      std::cout << "\nChoose what you want: (1) - Encode, (2) - Decode\n";
      std::cin >> choice;
      if (choice == 1)
        std::cout << EncodeSimple(alphabet, text, key) << "\n";
      else if (choice == 2)
        std::cout << DecodeSimple(alphabet, text, key) << "\n";
    } else if (choice_cipher == 2) {
      std::string key;
      std::cout << "Enter your key: ";
      std::cin >> key;
      for (auto &c : key) c = toupper(c);

      int choice;
      std::cout << "\nChoose what you want: (1) - Encode, (2) - Decode\n";
      std::cin >> choice;
      if (choice == 1)
        std::cout << EncodeVigenere(alphabet, text, key) << "\n";
      else if (choice == 2)
        std::cout << DecodeVigenere(alphabet, text, key) << "\n";
    } else if (choice_cipher == 3) {
      int key1, key2;
      std::cout << "Enter your keys: ";
      std::cin >> key1 >> key2;

      int choice;
      std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
      std::cin >> choice;
      if (choice == 1)
        std::cout << EncodeAffin(alphabet, text, key1, key2) << "\n";
      else if (choice == 2)
        std::cout << DecodeAffin(alphabet, text, key1, key2) << "\n";
    } else if (choice_cipher == 4) {
      enigma.setRotorPositions({0, 0, 0});

      int choice;
      std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
      std::cin >> choice;
      if (choice == 1)
        std::cout << enigma.encodeMessage(text) << "\n";
      else if (choice == 2)
        std::cout << enigma.decodeMessage(text) << "\n";
    } else if (choice_cipher == 5) {
      int shift;
      std::cout << "Enter your shift value: ";
      std::cin >> shift;

      int choice;
      std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
      std::cin >> choice;
      if (choice == 1)
        std::cout << encodeCaesar(alphabet, text, shift) << "\n";
      else if (choice == 2)
        std::cout << decodeCaesar(alphabet, text, shift) << "\n";
    }
  }
  return 0;
}