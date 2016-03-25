#include <vector>
template <class T, class Comparator>
void mergesort(std::vector<T>& input, int low, int high, Comparator comp) {
	if (low >= high - 1)	return;
	int mid = (low + high) / 2;
	mergesort(input, low, mid, comp);
	mergesort(input, mid, high,comp);
	int l1 = low, h1 = mid, l2 = mid, h2 = high;
	std::vector<T> temp;
	while (l1 < h1 && l2 < h2) temp.push_back(input[ comp(input[l1],input[l2]) ? l1++ : l2++]);
	while (l1 < h1)	temp.push_back(input[l1++]);
	while (l2 < h2)	temp.push_back(input[l2++]);
	for (int i=0; i<temp.size(); i++) input[i + low] = temp[i];
}
template <class T, class Comparator>
void mergesort(std::vector<T>& input, Comparator comp){
	mergesort(input, 0, input.size(), comp);
}