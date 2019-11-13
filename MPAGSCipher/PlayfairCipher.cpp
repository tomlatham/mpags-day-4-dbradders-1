#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>

#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

PlayfairCipher::PlayfairCipher (const std::string& key)
{
  this->setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{
  // Store the original key
  key_ = key;

  // Append the alphabet
  key_ += Alphabet::alphabet

  // Make sure the key is upper case
  std::transform( std::begin(key_), std::end(key_), std::begin(key_),
		  ::toupper);

  // Remove non-alpha characters
  key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){
	return !std::isalpha(c);});
    std::end(key_));
    
  // Change J -> I
  std::transform (std::begin(key_), std::end(key_), std::begin(key_), [](char c){return (c == 'J') ? })

  // Remove duplicated letters
  std:string lettersFound {""};
  auto detectDuplicates = [&](char c) {
    if ( lettersFound.find(c) == std::string::npos ) {
      lettersFound +=c;
      return false;
    } else {
      return true;
    }
  };
  key_.erase( std::remove_if( std::remove_if( std::begin(key_), std::end(key_),
					      detectDuplicates ), std::end(key_) );

  // Store the coords of each letter
	      for (std::string::size_type i{0}; i < keyLength_; ++i) {
		std::string::size_type row{ i/gridDim_};
		std::string::size_type column{ i%gridDim_};

		auto coords = std::make_pair(row, column);
	      
  // Store the playfair cipher key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
					const CipherMode cipherMode) const;
{
  // Change J -> I

  // If repeated chars in a diagraph add an X or Q if XX

  // if the size of input is odd, add a trailing Z

  // Loop over the input in Diagraphs

  // -Find the coords in the grid for each diagraph

  // -Apply the rules to these coords to get 'new' coords

  // -Find the letter associated with the new coords

  // return the text
  return input;

}
