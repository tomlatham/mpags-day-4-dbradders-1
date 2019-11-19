#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <vector>
#include "CipherMode.hpp"

class PlayfairCipher {
public:
  
  explicit PlayfairCipher(const std::string& key );

  std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

private:

  std::string key_{""};

  void setKey(const std::string& key);

  struct Alphabet{
    std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const std::vector<char>::size_type alphabetSize = alphabet.size();
  };
  

};

#endif

			

