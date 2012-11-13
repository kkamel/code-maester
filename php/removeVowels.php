<!DOCTYPE html>

<html>
<head> 

</head>

<body>
	<h1> Removing vowels LIKE A BOSS! </h1>
	<?php
	
 $input_sentence = "Of Monsters and Men. They sip their 
                    coffee and eat their buns.!"; 
  // Initial sentence.
  echo "<pre>";
  echo "Initial sentence: $input_sentence\n";
  echo "</pre>";
  removeVowels ($input_sentence);
  // Sentence after stripping the vowels.
  echo "<pre>";
  echo "Stripped of vowels: $input_sentence\n";
  echo "</pre>";

	function removeVowels (&$sentence) {
		// Explodes the passed sentence into an array of tokens. 
    $tokens = explode (" ", $sentence);
    $sentence = "";
		// For each token in the sentence... 
		foreach ($tokens as &$token) {					 
			// Splits each word into an array of letters. 
			$characters = str_split($token);		 
			
      foreach ($characters as &$char) {
        // Convert all characters to lowercase for consistency.
        $letter = strtolower($char);
				// Checks if the letter is a vowel and replaces with _. 
        if ($letter== 'a' ||$letter == 'e' || $letter == 'o' 
            || $letter == 'u' ||$letter == 'i') {	 
					$char="_";
				}
      }
      // Implode letters back into words.
      $word = implode($characters);
      // Concat words back into sentence.
      $sentence .= $word;
      $sentence .= " ";
    }
	}
	
	?>
	
</body>

</html>
