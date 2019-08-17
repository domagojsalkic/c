#include <iostream>
#include <map>
#include <string>
#include <algorithm>

typedef std::map<std::string, int>::const_iterator Iter;


int main() {
	std::string s;
	Iter it;
	std::map<std::string, int> h;
	while (true) {
		std::cin >> s;
		if (std::cin.fail())
			break;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		it = h.find(s);
		if (it != h.end())
			h[s] += 1;
		else
			h.insert(make_pair(s, 1));

	}
	if(h.size() > 0)
	for (it = h.begin(); it != h.end(); ++it) {
		std::cout << it->first << " : " << it->second << std::endl;
	} 
}