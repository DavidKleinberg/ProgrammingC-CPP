#ifndef dnasearch

#define dnasearch

	/*
	 * Checks whether the specified file fits the criteria
	 *
	 * @param inputFile file pointer
	 *
	 * @return 0 or 1 depending on validity
	 */
	int validTextFile(FILE* inputFile);

	/*
	 * Creates an array of specified size to fit the DNA String
	 * Eliminates space overhead
	 *
	 * @param inputFile file pointer
	 * @param numNucleotides size of array
	 *
	 * @return 0 or 1 depending on validity
	 */
	char* createDynamicArray(FILE* inputFile, int numNucleotides);

	/**
	 * Outputs a list of offsets where the pattern
	 * occurs in the genome (the input DNA text file)
	 *
	 * @param genome a String of nucleotides
	 * @param pattern a String of nucleotides
	 */
	void findPattern(char* genome, char* pattern);

	/*
	 * Checks whether the pattern is valid
	 *
	 * @param inputPattern a String of nucleotides
	 * @param genome a String of nucleotides
	 *
	 * @return 0 or 1 depending on validity
	 */
	int verifyPattern(char* inputPattern, char* genome);

	/*
	 * Finds the offsets where the pattern matches
	 * This function is split so that it can be tested
	 *
	 * @param genome a String of nucleotides
	 * @param pattern a String of nucleotides
	 * @param startAt the starting index
	 *
	 * @return 0 or 1 depending on match
	 */
	int patternMatch(char* genome, char* pattern, int startAt);

	/*
	 * Checks whether the nucleotide is valid
	 * Eliminates code reusage
	 *
	 * @param nucleotide one character from input
	 *
	 * @return 0 or 1 depending on validity
	 */
	int hasACGT(char nucleotide);

#endif
