#include <iostream>
#include <cstring>

using std::ostream;
using std::istream;
using std::string;

ostream& print_indent(ostream& os, int level, const string& seq)
{
	for (int i = 0; i < level; ++i) os << seq;
	return os;
}

int skip_spaces(istream& is)
{
	auto c = is.get();
	for (; c == ' '; c = is.get());
	is.unget();
	return c;
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
			t_indent(is, os, level + 1, indent);
			// if (skip_spaces(is) != '>')
			//         print_indent(os, level, indent);
			break;
		case '>':
			os << '>';
			if (level > 0) return os;
			break;
		case ',':
			os << ',' << std::endl;
			print_indent(os, level, indent);
			break;
		case ' ':
			if (level == 0) os << ' ';
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
	return t_indent(is, os, 0, indent);
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
