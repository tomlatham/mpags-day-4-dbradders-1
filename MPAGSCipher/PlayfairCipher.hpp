#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <map>
#include <string>
#include <vector>
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
public:
  
  /**
   * Create a new PlayfairCipher with the given key
   *
   * \param key the key to use in the cipher
   */
  explicit PlayfairCipher(const std::string& key );

  /**
   * Apply the cipher to the provided text
   *
   * \param inputText the text to encrypt or decrypt
   * \param cipherMode whether to encrypt or decrypt the input text
   * \return the result of applying the cipher to the input text
   */
  std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

private:

  /// The cipher key
  std::string key_{""};

  /**
   * Set the key to be used for the encryption/decryption
   *
   * \param key the key to use in the cipher
   */
  void setKey(const std::string& key);

  /// Define the nested alphabet type
  struct Alphabet{
    /// The alphabet itself
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    /// The alphabet size
    const std::vector<char>::size_type alphabetSize = alphabet.size();
  };

  /// Our alphabet instance
  Alphabet alphabet_;

  /// The grid dimension
  const int gridDim_{5};

  // Lookup tables generated from the key

  /// Type definition for the coordinates in the 5x5 table
  using Coords = std::pair<int,int>;
  /// Type definition for the map from letter to coordinates in the 5x5 table
  using Char2Coords = std::map<char, Coords>;
  /// Type definition for the map from coordinates in the 5x5 table to letter
  using Coords2Char = std::map<Coords, char>;
  /// Lookup table to go from the character to the coordinates
  Char2Coords letterToCoords_;
  /// Lookup table to go from the coordinates to the character
  Coords2Char coordsToLetter_;
  

};

#endif

			

