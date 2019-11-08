#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>


class PlayfairCipher {
public:
  
  const std::string key;

  explicit PlayfairCipher(const std::string& key );

  std::string setKey(const std::string& key);

  std::string applyCipher() const;

};

#endif

			

