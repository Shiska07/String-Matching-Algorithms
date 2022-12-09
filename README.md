Name:Shiska Raut
ID:1001526329

To run the program in omega:
gcc string_matching.c utils.c -lrt
./a.out "text file name" "pattern file name" "mode"


Notes:
1. "text file name": a .txt file containing the text string in the first line of the file
2. "pattern file name: a .txt file containing the patterin string in the first line of the file
3. "mode": "0" - Naive String Matcher
	   "1" - Rabin-Karp Matcher
	   "2" - Knuth-Morris-Pratt Matcher

Sample Output:
$ gcc string_matching.c utils.c -lrt
$ ./a.out sample_data/sample_text1.txt sample_data/sample_pattern.txt 2
Match found at index 999950.
A total of 1 match/es found with Knuth-Morris-Pratt.

Time elapsed: 0.003983 seconds.


	