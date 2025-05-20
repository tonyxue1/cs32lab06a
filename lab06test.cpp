#include "WordCount.h"
#include "tddFuncs.h"

int main() {
    WordCount wc;

    wc.incrWordCount("Hello");
    wc.incrWordCount("HELLO");
    wc.incrWordCount("world!");
    wc.incrWordCount("world");

    ASSERT_EQUALS(2, wc.getWordCount("hello")); // should normalize to lowercase
    ASSERT_EQUALS(2, wc.getWordCount("WORLD")); // punctuation removed, case normalized
    ASSERT_EQUALS(4, wc.getTotalWords());
    ASSERT_EQUALS(2, wc.getNumUniqueWords());

    return 0;
}

