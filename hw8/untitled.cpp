		void add(const std::string& word){
			add_multiple(word,1);
		}
		void probe(int hashed, std::string word, int count){
			for(int i = 1;	; i++){
				int index = (hashed + i * i)%_size[_size_index];
					if(vals[index].first == word || vals[index].second == 0) {
						add_helper(vals[index],word,count);
						break;
					}
				}
			}
		void add_helper(std::pair<std::string,int> pair, const std::string& word, const int& count){
			if(pair.second == 0){
				pair.first = word;
				++_num_words;
			}
			pair.second += count;
		}
		void add_multiple(const std::string& word, int count){
			std::string lower_word = word;
			std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
			if(_load_factor >= 0.5)	resize(++_size_index);
			int hashed = hash(word);
			if(vals[hashed].second == 0 || vals[hashed].first == word)	add_helper(vals[hashed], word, count);
			else	probe(hashed,word, count);
			_load_factor = double(_num_words)/_size[_size_index];
		}
		void add_multiple(const std::string& word, int count){
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
			_load_factor =double(_num_words)/_size[_size_index];
		}