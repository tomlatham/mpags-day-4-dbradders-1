#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

PlayfairCipher::PlayfairCipher (const std::string& key)
{

}

void PlayfairCipher::setKey(const std::string& key)
{

}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
					const CipherMode cipherMode) const;
