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
  key_ += std::string Alphabet.alphabet;

  // Make sure the key is upper case
  // Using std::transform algorithm
  std::transform( std::begin(key_), std::end(key_), std::begin(key_),
		  ::toupper);

  // Remove non-alpha characters
  // Used lambda, removing elements from beginning to end of key_
  // if the element (declared explicitly as c) is not alphabetic
  key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){
	return !std::isalpha(c);}),
    std::end(key_));
    
  // Change J -> I
  std::transform (std::begin(key_), std::end(key_), std::begin(key_), [](char c){return (c == 'J') ? 'I' : c; });

  // Remove duplicated letters
  // Create and store lambda function detectDuplicates that captures
  // by reference each letter. If c is not found in the string lettersFound
  // then return is false and c is added to the string lettersFound
  std::string lettersFound {""};
  auto detectDuplicates = [&](char c) {
    if ( lettersFound.find(c) == std::string::npos ) {
      lettersFound += c;
      return false;
    } else {
      return true;
    }
  };
  // Remove if duplicate in similar manner as before
  key_.erase( std::remove_if( std::begin(key_), std::end(key_),
					      detectDuplicates ),
			      std::end(key_) );

  // Store the coords of each letter
  for (std::string::size_type i{0}; i < key_.size(); ++i) {
		const int gridDim_{5};
		std::string::size_type row{ i/gridDim_};
		std::string::size_type column{ i%gridDim_};

		auto coords = std::make_pair(row, column);
			      
  // Store the playfair cipher key map

		letterToCoords_.insert(coords);
		coordsToLetter_.insert(key_[i]);
  }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
					const CipherMode cipherMode) const;
{
  // Change J -> I
  std::transform (std::begin(inputText), std::end(inputText),
		  std::begin(inputText), [](char c){return (c == 'J') ? 'I' : c; });

  // If repeated chars in a diagraph add an X or Q if XX
  

  // if the size of input is odd, add a trailing Z

  // Loop over the input in Diagraphs

  // -Find the coords in the grid for each diagraph

  // -Apply the rules to these coords to get 'new' coords

  // -Find the letter associated with the new coords

  // return the text
  return input;

}
