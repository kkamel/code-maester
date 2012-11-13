</head>

<body>
  <h1> Associative Sort: Ascending order </h1>
<?php
  // Array to be sorted.
  $unsorted_array = array(200, 1, 300, 60, 21, 22, 45);
  echo "Unsorted array: \n";
  // Print keys and values of unsoretd array.
  foreach ($unsorted_array as $key => $value) {
    echo "<pre>";
    echo "value: $value, key: $key\n";
    echo "</pre>";
  }
  echo "<pre>";
  echo "\n";
  echo "</pre>";
  // Initialize array to hold sorted elements.
  $sorted_array = array();
  // Call associative sort. 
   associative_sort($unsorted_array, $sorted_array);
  echo "Associative sorted array: \n";
  // Print sorted array.
  foreach ($sorted_array as $key => $value) {
    echo "<pre>";
    echo "value: $value, key: $key\n";
    echo "</pre>";
  }
  // Input: $unosorted_array.
  // Output: $sorted_array will hold sorted elements.
  // Algorithm: Selection sort, sorts in reverse order (descending).
  // Complexity => O(n^2) run time.
  function associative_sort(&$aArray, &$sorted_array) {
    $bArray = $aArray;
    foreach ($aArray as $key1 => $value1) {
      //echo $key1,$value1, "\n";
      $min_value = null;
      $min_key = null;
      foreach($bArray as $key2 => $value2) {
        // If value2 is first element or value2 is less than min.
        if (null === $min_value || $value2 < $min_value) {
          // Save the value and its key.
          $min_key = $key2;
          $min_value = $value2;
         
        }
      }
      // Add the smallest element to the sorted array.
      // Done with this element, remove the element from the array.
      $sorted_array[$min_key] = $min_value;
      if (($key = array_search($min_value, $bArray)) !== false) {
        unset($bArray[$key]);
      }
    }
  }

?>
</body>

</html>


      
