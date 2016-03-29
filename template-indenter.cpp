#include <iostream>
#include <cstring>
#include <regex>

using std::ostream;
using std::istream;
using std::string;

string colour_start_seq {"2"};
string colour_end_seq {"22"};

ostream& start_colour(ostream& os)
{
	return os << "[" << colour_start_seq << "m";
}

ostream& end_colour(ostream& os)
{
	return os << "[" << colour_end_seq << "m";
}

ostream& print_indent(ostream& os, int level, const string& seq)
{
	for (int i = 0; i < level; ++i) os << seq;
	return os;
}

void skip_spaces(istream& is)
{
	while (is.good() && is.get() == ' ');
	is.unget();
}

/* t_indent: indent template. */
ostream& t_indent(istream& is, ostream& os, int level, const string& indent)
{
	print_indent(os, level, indent);
	auto c = is.get();
	for (; is.good() && c != '\n'; c = is.get()) {
		switch (c) {
		case '<':
			os << '<' << std::endl;
			start_colour(os);
			t_indent(is, os, level + 1, indent);
			if (level == 0) end_colour(os);
			skip_spaces(is);
			break;
		case '>':
			os << '>';
			if (level > 0) return os;
			break;
		case ',':
			os << ',' << std::endl;
			if (level > 0) start_colour(os);
			print_indent(os, level, indent);
			skip_spaces(is);
			break;
		default:
			os << (char)c;
			break;
		}
	}
	return os;
}

ostream& t_indent(istream& is, ostream& os, const string& indent)
{
	while (is) {
		int ch = is.get();
		if (ch == '\n' || ch == EOF) {
			return os;
		} else if (ch == ' ' || ch == '\t') {
			os << (char)ch;
			continue;
		} else {
			is.unget();
		}
		string word;
		is >> word;
		os << word;
		if (std::regex_match(word,
				     std::regex{".*(error|note):.*"})) {
			return t_indent(is, os, 0, indent);
		}
	}
	return os;
}

ostream& t_indent_all(istream& is, ostream& os, string indent)
{
	while (is.good()) {
		t_indent(is, os, indent) << std::endl;
	}
	return os;
}

int main()
{
	using namespace std;

	t_indent_all(cin, cout, "    ");
	if (cin.bad() || cout.bad()) {
		cerr << strerror(errno) << endl;
		return 2;
	} else {
		return 0;
	}
}
