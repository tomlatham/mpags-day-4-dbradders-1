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
  key_ += std::string alphabet_.alphabet;

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
  for (std::string::size_type i{0}; i < inputText.size(); ++i) {

    if (inputText[i] == inputText[i-1])
      {
	if (inputText[i] == 'X')
	  {
	    inputText.insert(i, 'Q');
	  }
	else{
	  inputText.insert(i, 'X');
	}
      }
    
  };

  // if the size of input is odd, add a trailing Z
  if ((inputText.size()%2) == 1)
    {
      inputText += 'Z';
    }

  // Loop over the input in Diagraphs
  for (std::string::size_type i{0}; i < (2*inputText.size(); i += 2){
  
  // -Find the coords in the grid for each diagraph
      auto coord1 = letterToCoords_.find(inputText[i])->second;
      auto coord2 = letterToCoords_.find(inputText[i+1])->second;
      auto newcoord1;
      auto newcoord2;
	
  // -Apply the rules to these coords to get 'new' coords
      if(coord1.row == coord2.row)
	{
	  if (cipherMode == CipherMode::Encrypt){
	    newcoord1.column = ((coord1.column + 1) % gridDim_);
	    newcoord2.column = ((coord2.column + 1) % gridDim_);	    
	  }
	  else{
	    newcoord1.column = ((coord1.column - 1) % gridDim_);
	    newcoord2.column = ((coord2.column - 1) % gridDim_);	    
	  }
	}
      else if (coord1.column == coord2.column)
	{
	  if (cipherMode == CipherMode::Encrypt){
	    newcoord1.row = ((coord1.row + 1) % gridDim_);
	    newcoord2.row = ((coord2.row + 1) % gridDim_);	    
	  }
	  else{
	    newcoord1.row = ((coord1.row - 1) % gridDim_);
	    newcoord2.row = ((coord2.row - 1) % gridDim_);	    
	  }
	}
      else
	{
	  auto x = newcoord1;
	  newcoord1 = newcoord2;
	  newcoord2 = x;
	}

  // -Find the letter associated with the new coords
      auto input = (coordsToLetter_.find(newcoord1, newcoord2));

    }
  // return the text
  return input;
   
}
