# BagOfWords
In this problem you will write a program that reads one or more documents and uses it to build a large dataset of words called "Bag-of-Words" (BoW for short), disregarding grammar and word order by keeping multiplicity (frequency). BoW is a representatisson of text that describes the occurrence of words within a document where the order of words is not taken into account. This is a text preprocessing technique.
It involves two things:
  1. A vocabulary of known words.
  2. A measure of the presence of known words (frequency).
It is called a “bag” of words, because any information about the order or structure of words in the document is discarded. The model is only concerned with whether known words occur in the document, not where in the document.
Suppose we have following text files (input.txt, document1.txt & document2.txt):
  1. input.txt:
    a. The first row of the file contains Stop Words. Stop Words are lists of words which youdon't want to include in analysis. For example you might want to make a word list excluding common function words like the, of, was, is, it.
      Note: Words are space separated. And stop words are in lower case.
    b. The second row of the file contains number of documents. For example “2” in this case.
    c. Followed by relative paths of documents.
    
  2. Dataset:
    Dataset consists of one or more documents (In our example there are two documents)
    Example:
      a. document1.txt: “John likes to , watch movies. Mary: likes movies too.”
      b. document2.txt: “Mary also’ likes # to& watch football games.”

# Steps:
Step 01:
  a. You will read Stop Words form input.txt file
  b. Read one or more documents whose path is mentioned in input.txt file (For example,document1.txt & document2.txt file).

  Function Prototype:
      void readInput(const char* pathofInputFile)
          pathofInputFile indicates path of input.txt file.

      Note: you must read the input and documents (document1.txt & document2.txt, ...) text file once (you will be awarded no points, if you read text files multiple times). And save the data in classes (it can be templatized).
Step 02:
Process (or Preprocess, to be technically correct) the documents as follows:
  a. Remove all the punctuations marks (.~ ! @ # $ % ^ & * ( ) _ + = “ ; : / ? > , < ). Including ‘\n’ (newline) & extra spaces.
    Note: Remember
      • Output must only contain alphabets and space characters.
      • There must be single space between two words.
    Output:
      • “John likes to watch movies Mary likes movies too”
      • “Mary also likes to watch football games”
   b. Convert all upper case letters to lower case.
     Output:
        • “john likes to watch movies mary likes movies too”
        • “mary also likes to watch football games”
   c. Remove stop words
      Output:
        • “john likes watch movies mary likes movies”
        • “mary likes watch football games”

      Function Prototypes:.
         1. void removePunctuationMarks()
            This function will remove punctuation marks according to Step 02.a
         2. void convertUpperToLowerCase()
            This function will convert upper case letters to lower case letters according to Step 02.b
         3. void removeStopWords()
            This function will remove stop words according to Step 02.c
         4. int getNumberOfDocument()
            This function will return number of documents.
         5. char * getText(int documentNumber)
            This function will return document text as char array (char*) according to document number.
            Note: getNumberOfDocument & getText functions will be used for testing purposes
  Step 03:
    Now generate bag of words.
    Term Document1 Document2
    john 1 0
    likes 2 1
    watch 1 1
    movies 2 0
    mary 1 1
    football 0 1
    games 0 1

    Write bag of words on to the file (BoW.txt)
    Note: unique words must be extracted according to the document’s order i-e order should be
    maintained (first unique word should be “john” then “likes”, so on).

    Function Prototype:
    void generateBagofWords (const char* pathofBoWFile)
    pathofBoWFile indicates path of BoW.txt file.
