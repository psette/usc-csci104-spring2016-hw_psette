#include "Map.h"
#include <cmath>
#include <utility>
#include <algorithm>
class HashTable : public Map{
	public:
		//Initialize Hashtable, set private variabls and fill the array of sizes
		HashTable(){
			_num_words = 0;	_load_factor = 0;	_size_index = 0;
			vals = new std::pair<std::string,int>[11];
			for(int i = 0; i < 11; i++) 	vals[i].second = 0;
			_size[0] = 11; _size[1] = 23; _size[2] = 41; _size[3] = 83; _size[4] = 163; _size[5] = 331; _size[6] = 641;
			_size[8] = 2579; _size[9] = 5147; _size[10] = 10243; _size[11] = 20483; _size[12] =  40961; _size[7] = 1283;
		}
		//Delete dynamically allocated array
		~HashTable(){	delete [] vals;	}
		//add function which calls add_helper with the word and the count of 1
		void add(const std::string& word){	add_helper(word ,1);	}
		//Report all writes to the ostream, iterates from 0 to size and writes if the count > 0
		void reportAll(std::ostream& output){
			if(_num_words == 0)	return;
			for(int i = 0; i < _size[_size_index]; i++)
				if(vals[i].second != 0)	output<<vals[i].first<<" "<<vals[i].second<<std::endl;
		}
	private:
		//Resizes the array of pairs, adds all the pairs in the previous arrays
		void resize(const int& ref){
			std::pair<std::string,int> * old_vals = vals;
			vals = new std::pair<std::string,int>[_size[ref]];
			_num_words = 0;
			_load_factor = 0;
			for(int i = 0; i < _size[ref]; i++)	vals[i].second = 0;
			for(int i = 0; i < _size[ref - 1]; i++)
				if(old_vals[i].second != 0) add_helper(old_vals[i].first , old_vals[i].second);
			delete [] old_vals;
		}
		/*add_helper function: converts word to lower, checks if you must resize
		checks if there is not a word at the hashed value, insert the word and increment count
		otherwise, if there is a word and it is the same word, increment count
		otherwise, quadratic probe
		*/
		void add_helper(const std::string& word, const int & count){
			std::string lower_word = word;
			std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
			if(_load_factor >= 0.5)	resize(++_size_index);
			int hashed = hash(lower_word);
			if(vals[hashed].second == 0){
				vals[hashed].first = lower_word;
				vals[hashed].second = count;
				++_num_words;
			} 	else if( vals[hashed].first == lower_word){
				vals[hashed].second += count;
			}	else	{
				for(int i = 1; ;i++){
					int index = (hashed + i * i) % _size[_size_index];
					if(vals[index].first == lower_word){
						vals[index].second += count;
						break;
					} else if(vals[index].second == 0) {
						_num_words++;
						vals[index].first = lower_word;
						vals[index].second = count;
						break;
					}
				}
			}
			_load_factor = double(_num_words)/_size[_size_index];
		}
		/*hash function: takes in a word and splits into groups of 8, calls hash helper to fill array w
		then does some arithmetic and returns that value % tablesize
		*/
		int hash(const std::string word){
			int w[14];
			for(int i = 0; i < 14; ++i)	w[i] = -1;
			if( word.length() > 8 ) {
				int end = word.length();
				int begin = end - 8;
				while(end > 0){
					if(begin < 0) begin = 0;
					hash_helper(word.substr(begin,end-begin),w); 
					end = begin;
					begin = end - 8; 
				}
			} else hash_helper(word, w);
			for(int i = 0; i < 14; i++) if(w[i] == -1) w[i] = 0;
			long long part1 = (long long)(34394 * w[0]) + (long long)(36706 * w[1]) + (long long)(38074 * w[2]);
			long long part2 = (long long)(16351 * w[3]) + (long long)(2623 * w[4]) + (long long)( 10174 * w[5]);
			long long part3 = (long long)(22339 * w[6]) + (long long)(27779 * w[7]) + (long long)(36642 * w[8]) + (long long)(24019 * w[12]);
			long long part4 = (long long)(19250 * w[9]) + (long long)(36216 * w[10]) + (long long)(33514 * w[11]) + (long long)(5552 * w[13]);
			return (part1 + part2 + part3 + part4) % _size[_size_index];
		}
		/*hash_helper adds nulls to word if it's under 8 character

		*/
		void hash_helper(std::string word, int arr[14]){
			while(word.length() < 8) word = '\0' + word;
			long long a1 = word[0], a2 = word[1], a3 = word[2], a4 = word[3];
			long long a5 = word[4], a6 = word[5], a7 = word[6], a8 = word[7];
			long long part1 = (long long)(pow(128,7) * a1) + (long long)(pow(128,6) * a2);
			long long part2 = (long long)(pow(128,5) * a3) + (long long)(pow(128,4) * a4);
			long long part3 = (long long)(pow(128,3) * a5) + (long long)(pow(128,2) * a6);
			long long part4 = (long long)(pow(128,1) * a7) + (long long)(a8);
			long long total = part1 + part2 + part3 + part4;
			int place = 0, i = 0;
			while(arr[place] == -1){
				if(place == 13)	break;
				if(arr[place+1] != -1) break;
				++place;
			}
			while(total > 0){
				arr[place - i++] = total % 40961;
				total /= 40961;
			}
		}
		std::pair<std::string,int> * vals;
		int _size_index, _num_words, _size[13];
		double _load_factor;
};