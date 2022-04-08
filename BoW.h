#pragma once
#include<iostream>
#include<fstream>
using namespace std;

template <typename SW>
class BagOfWords {
	SW** stop_words;
	SW*** Content;
	char** files;
	char* text;
	int* files_words;
	unsigned int no_of_files;
	unsigned int no_of_stop_words;
	unsigned int length_of_stop_words;
public:
	BagOfWords() {
		stop_words = nullptr;
		Content = nullptr;
		files = nullptr;
		text = nullptr;
		no_of_files = no_of_stop_words = length_of_stop_words = 0;
	}
	void readInput(const char* pathofInputFile) {
		std::ifstream input(pathofInputFile, ios::in);
		input.seekg(12, ios::beg);

		no_of_stop_words = 0;
		length_of_stop_words = 0;
		int temp_max = 0;
		while (1) {
			char temp_char = input.get();
			if (temp_char == 32) {
				no_of_stop_words++;
				length_of_stop_words = temp_max > length_of_stop_words ? temp_max : length_of_stop_words;
				temp_max = 0;
			}
			else if (temp_char == '\n') {
				no_of_stop_words++;
				length_of_stop_words = temp_max > length_of_stop_words ? temp_max : length_of_stop_words;
				temp_max = 0;
				break;
			}
			else
				temp_max++;
		}
		
		input.seekg(12, ios::beg);

			stop_words = new SW * [no_of_stop_words];
			for (int i = 0; i < no_of_stop_words; i++) {
				stop_words[i] = new SW[length_of_stop_words];
				int a = NULL;
				for (int j = 0; j < length_of_stop_words; j++)
					*(*(stop_words+i)+j) = a;
			}
			for (int i = 0,j=0; i < no_of_stop_words; ) {
				char temp = input.get();
				if (temp == ' ' || temp == '\n') {
					i++;
					j = 0;
				}
				else if((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z')){
					stop_words[i][j] = (temp);
					j++;
				}
			}

		input >> no_of_files;
		files = new char*[no_of_files];
		for (int i = 0; i < no_of_files; i++) {
			files[i] = new char [45];
			for (int j = 0; j < 45; j++) {
				files[i][j] = NULL;
			}
		}
		files_words = new int[no_of_files];
		for (int i = 0; i < no_of_files; i++) {
			files_words[i] = 0;
			input >> files[i];
		}


		for (int i = 0; i < no_of_files;files_words[i-1]++) {
			ifstream sub_input(files[i], ios::in);
			while (!sub_input.eof()) {
				char temp_char = sub_input.get();
				if (temp_char == 32) {
					files_words[i]++;
				}
			}
			sub_input.close();
			i++;
		}


			Content = new SW**[no_of_files];
			for (int i = 0; i < no_of_files; i++) {
				Content[i] = new SW*[files_words[i]];
				for (int j = 0; j < files_words[i]; j++) {
					Content[i][j] = new SW[45];
					int a = NULL;
					for (int k = 0; k < 45; k++)
						Content[i][j][k] = a;
				}
				ifstream sub_input(files[i], ios::in);
				for (int j = 0; j < files_words[i]; j++) {
					
					SW temp = sub_input.get();
					int k = 0;
					while(!sub_input.eof()&&(temp!=32&&temp!='\n')){
						Content[i][j][k] = temp;
						k++;
						temp = sub_input.get();
					}
				}
				sub_input.close();
			}

		input.close();
	}
	void removePunctuationMarks() {
		for (int i = 0; i < no_of_files; i++) {
			for (int j = 0; j < files_words[i]; j++) {
				if (Content[i][j] != NULL) {
					for (int k = 0; k < 45 && Content[i][j][k] != NULL; k++) {
						if ((Content[i][j][k] < 'A' || Content[i][j][k] > 'z') || (Content[i][j][k] > 'Z' && Content[i][j][k] < 'a')) {
							Content[i][j][k] = NULL;
						}
					}
				}
			}
		}
	}
	void convertUpperToLowerCase() {
		for (int i = 0; i < no_of_files; i++) {
			for (int j = 0; j < files_words[i]; j++) {
				if (Content[i][j] != NULL) {
					for (int k = 0; k < 45 && Content[i][j][k] != NULL; k++) {
						if ((Content[i][j][k] >= 'A' && Content[i][j][k] <= 'Z')) {
							Content[i][j][k] += 32;
						}
					}
				}
			}
		}
	}
	void removeStopWords() {
		for (int i = 0; i < no_of_files; i++) {
			for (int j = 0; j < files_words[i]; j++) {
				if (Content[i][j] != NULL) {
					bool temp = true;
					for (int k = 0; k < no_of_stop_words; k++) {
						if (temp&&(Content[i][j][0] == stop_words[k][0])) {
							for (int l = 1;temp && (Content[i][j][l] == stop_words[k][l]); l++) {
								if ((stop_words[k][l + 1] < 'A'|| stop_words[k][l + 1] > 'z') || (stop_words[k][l + 1] < 'a' && stop_words[k][l + 1] > 'Z')) {
									if ((Content[i][j][l + 1] < 'A' || Content[i][j][l + 1]>'z') || (Content[i][j][l + 1] < 'a' && Content[i][j][l + 1]>'Z')) {
										delete[] Content[i][j];
										Content[i][j] = NULL;
										temp = false;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	int getNumberOfDocument() {
		return no_of_files;
	}
	char* getText(int documentNumber) {
		int no_of_chars = 0;
			for (int j = 0; j < files_words[documentNumber-1]; j++) {
				if (Content[documentNumber-1][j] != NULL) {
					for (int k = 0; k < 45 && Content[documentNumber-1][j][k] != NULL; k++) {
						no_of_chars++;
					}
					no_of_chars++;
				}
			}
			if (text)
				delete[] text;
			text = new char[no_of_chars];
			for (int i = 0; i < no_of_chars; i++) {
				text[i] = 0;
			}
			no_of_chars = 0;
			for (int i = 0; i < files_words[documentNumber - 1]; i++) {
				if (Content[documentNumber - 1][i] != NULL) {
					for (int j = 0; j < 45 && Content[documentNumber - 1][i][j] != NULL; j++) {
						text[no_of_chars] = Content[documentNumber - 1][i][j];
						no_of_chars++;
					}
					text[no_of_chars] = ' ';
					no_of_chars++;
				}
			}
			return text;
	}
	void generateBagofWords(const char* pathofBoWFile) {

		int total_words = 0;
		for (int i = 0; i < no_of_files; i++)
			total_words += files_words[i];
		char** words = new char* [total_words];
		for (int i = 0; i <total_words; i++) {
			words[i] = new char[45];
		}

			for (int j = 0; j < total_words; j++) {
				for (int k = 0; k < 45; k++) {
					words[j][k] = NULL;
				}
			}

		int** no_words = new int* [no_of_files];
		for (int i = 0; i < no_of_files; i++) {
			no_words[i] = new int [total_words];
		}

		for (int i = 0; i < no_of_files; i++) {
			for (int j = 0; j < total_words; j++) {
				no_words[i][j] = 0;
			}
		}

		int index_of_words = 0;
		for (int i = 0; i < no_of_files; i++){
			for (int j = 0; j < files_words[i]; j++) {
				if (Content[i][j] != nullptr) {
					bool temp = true;
					for (int k = 0; k <= index_of_words&&temp; k++) {
						if (Content[i][j][0] == words[k][0]) {
							for (int l = 1; l < 45 && (words[k][l] == Content[i][j][l]); l++) {
								if (words[k][l] == NULL) {
									no_words[i][k]++;
									temp = false;
									break;
								}
							}
						}
					}
					if (temp) {
						for (int k = 0; Content[i][j][k] != NULL; k++) {
							words[index_of_words][k] = Content[i][j][k];
						}
						no_words[i][index_of_words] = 1;
						index_of_words++;
					}
				}
			}
		}

		ofstream output(pathofBoWFile, ios::out);
		for (int i = 0; i < index_of_words; i++) {
			output << words[i]<<" ";
			for (int j = 0; j < no_of_files; j++) {
				output << no_words[j][i] << " ";
			}
			output << "\n";
		}
		output.close();
	}

	~BagOfWords() {
			for (int i = 0; i < no_of_stop_words; i++)
				delete stop_words[i];
			delete[] stop_words;

			for (int i = 0; i < no_of_files; i++) {
				for (int j = 0; j < files_words[i]; j++)
					if (Content[i][j] != NULL) {
						delete[] Content[i][j];
					}
				delete[] Content[i];
			}
			delete[] Content;
		

		if (files)
			delete[] files;
		if (files_words)
			delete[] files_words;

		if (text)
			delete[] text;
	}
};