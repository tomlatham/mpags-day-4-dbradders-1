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
  key_ += alphabet_.alphabet;

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
		std::string::size_type row{ i/gridDim_};
		std::string::size_type column{ i%gridDim_};

		auto coords = std::make_pair(row, column);
			      
  // Store the playfair cipher key map

		letterToCoords_.insert( std::make_pair( key_[i], coords ) );
		coordsToLetter_.insert( std::make_pair( coords, key_[i] ) );
  }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
					const CipherMode cipherMode) const
{
  std::string outputText {inputText};

  // Change J -> I
  std::transform (std::begin(outputText), std::end(outputText),
		  std::begin(outputText), [](char c){return (c == 'J') ? 'I' : c; });

  // If repeated chars in a diagraph add an X or Q if XX
  for (std::string::size_type i{0}; i < outputText.size(); i += 2) {

    if (outputText[i] == outputText[i+1])
      {
	if (outputText[i] == 'X')
	  {
	    outputText.insert(i+1, "Q");
	  }
	else{
	  outputText.insert(i+1, "X");
	}
      }
    
  };

  // if the size of input is odd, add a trailing Z
  if ((outputText.size()%2) == 1)
    {
      outputText += 'Z';
    }

  // Loop over the input in Diagraphs
  for (std::string::size_type i{0}; i < outputText.size(); i += 2){
  
  // -Find the coords in the grid for each diagraph
      auto coord1 = letterToCoords_.find(outputText[i])->second;
      auto coord2 = letterToCoords_.find(outputText[i+1])->second;
      auto newcoord1{coord1};
      auto newcoord2{coord2};
	
  // -Apply the rules to these coords to get 'new' coords
      if(coord1.first == coord2.first)
	{
		// Rows are the same, increment or decrement the column numbers (modulo the grid size)
	  if (cipherMode == CipherMode::Encrypt){
	    newcoord1.second = ((coord1.second + 1) % gridDim_);
	    newcoord2.second = ((coord2.second + 1) % gridDim_);	    
	  }
	  else{
	    newcoord1.second = ((coord1.second + gridDim_ - 1) % gridDim_);
	    newcoord2.second = ((coord2.second + gridDim_ - 1) % gridDim_);	    
	  }
	}
      else if (coord1.second == coord2.second)
	{
		// Columns are the same, increment or decrement the row numbers (modulo the grid size)
	  if (cipherMode == CipherMode::Encrypt){
	    newcoord1.first = ((coord1.first + 1) % gridDim_);
	    newcoord2.first = ((coord2.first + 1) % gridDim_);	    
	  }
	  else{
	    newcoord1.first = ((coord1.first + gridDim_ - 1) % gridDim_);
	    newcoord2.first = ((coord2.first + gridDim_ - 1) % gridDim_);	    
	  }
	}
      else
	{
    // Square/rectangle, swap the column indices
    std::swap( newcoord1.second, newcoord2.second );
	}

  // -Find the letter associated with the new coords
      outputText[i]   = coordsToLetter_.find(newcoord1)->second;
      outputText[i+1] = coordsToLetter_.find(newcoord2)->second;
      

    }
  // return the text
  return outputText;
   
}
