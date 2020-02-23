# Vocab-Dictionary
A console application implemented using C, it allows the user to translate a single vocabulary into one of the two supported languages (Spanish, German) in a constant
time.

It based on the concept of Trie data structure and three main functions load, check , unload.

How “load” works?
The load function reads the English file character by character and store it in the Trie according to the index of this character in the English Alphabets,                              a,A = 0
b,B = 1
c,C = 2
………
when the cursor hit the null terminator ‘\n’  in the end of  each single word, the corresponding line from the other language’s file should be loaded in the last node of the Trie’s path represents this particular word.

 
How “check” works?
Basically check function accepts a word to search for it in the Trie, once the string is provided to it, it starts to iterate over it and convert each character to its English index and then go to the node pointed to by this character’s index pointer, till it reaching the last node in the path, checks if the is_word variable is true, then returns the content of meaning.
