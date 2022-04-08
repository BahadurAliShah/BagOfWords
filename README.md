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
