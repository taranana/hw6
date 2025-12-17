#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      unsigned long long w[5] = {0,0,0,0,0};

      int len = k.size();
      int index = 4;
      int i = len - 1;

      while (i >= 0 && index >= 0) {
        unsigned long long value = 0;
        unsigned long long power = 1;


        for(int x= 0 ; x < 6 && i >= 0; x ++ ) {
          value += letterDigitToNumber(k[i]) * power;
          power *= 36;
          i--;
        }

        w[index] = value;
        index--;
      }

      HASH_INDEX_T hash = 0;
      for( int j = 0; j < 5; j++) {
        hash += (rValues[j] * w[j]);
      }
      return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char c) const //im used to using c for chars so i switched letter to c
    {
        // Add code here or delete this helper function if you do not want it
      if (c >= 'A' && c <= 'Z') {
        c = c - 'A' + 'a';
      }

      if( c >= 'a' && c <= 'z') {
        return c - 'a';
      }

      if( c >= '0' && c <= '9') {
        return c - '0'+26;
      }

      return 0; //return 0 if c is not a valid char to use in hassh
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
