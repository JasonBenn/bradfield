// COMPUTE input length
// INIT array of bools, one per letter, set all to FALSE (0)
// FOR char in sentence
  // LOWERCASE char
  // IF letter
    // SET that bool in the array to true
// FOR bool in array
  // IF bool is false
    // RETURN false
// RETURN true

// which lines generate branches: in the codestream?
// how often is each branch taken?

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_OF_LETTERS (26)

// 53 + 1 + 16 + 16 bits = 86 bits = 11 bytes
// w ~10kb of memory for branch prediction...
// order of magnitude estimate: you could remember stats for 1k - 10k branches

bool is_pangram(const char *sentence) {
  // Branches: 99% strlen
  size_t sentence_length = ((sentence != NULL) ? strlen(sentence) : 0);
  bool found_letters[NUMBER_OF_LETTERS];

  memset(found_letters, 0, sizeof(found_letters));

  for (size_t i = 0; i < sentence_length /* Branches: 99% of the time, is not last char */; i++) {
    char letter = tolower(sentence[i]);

    // Branches: 70% of the time, is letters not whitespace/tricksy chars like digits
    if (isalpha(letter)) {
      found_letters[letter - 'a'] = true;
    }
  }

  for (size_t i = 0; i < NUMBER_OF_LETTERS /* Branches: 25/26 (96%) is not index of 'Z' bool. Could be unrolled at compile time! But larger code size could cause cache miss. So maybe compilers would unroll if text size increase is small (3-10x?) */; i++) {
    // Branches: true case dominates like... 65% of the time?
    if (!found_letters[i]) {
      return false;
    }
  }

  return true;
}

// valgrind: find when you malloc'd but forgot free
// subtool callgrind: tells you about asm jumps, can give you data on branch prediction performance

int main(int argc, char const *argv[]) {
  const char sentence[] = "the quick brown fox jumps over the lazy dog";
  assert(is_pangram(sentence) == true);
  printf("OK\n");
  return 0;
}
