#include <iostream>
#include <stack>
#include <cstdint>
#include <utility>
#include <vector>
#include <cerrno>
#include <cstring>

using namespace std;

enum iranyok {
	jobbra = 0, le, balra, fel
};

struct {
	uint32_t sor, oszlop;
	enum iranyok irany;
} PM = {.sor = 0, .oszlop = 0, .irany = jobbra};

pair<int, int> readSize(FILE *f) {
	int lines = 1, maxLength = 0, currentLength = 0, c;
	while ((c = getc(f)) != EOF) {
		if (c == '\r') continue;
		if (c == '\n') {
			lines++;
			if (currentLength > maxLength) {
				maxLength = currentLength;
			}
			currentLength = 0;
		} else {
			currentLength++;
		}
	}
	if (currentLength > maxLength) maxLength = currentLength;
	
	return make_pair(lines, maxLength);
}

void readCode(FILE *f, vector<vector<char>> *arr) {
	int i = 0, j = 0, c, lineLength = arr[0].size();
	while ((c = getc(f)) != EOF) {
		if (c == '\r') continue;
		if (c == '\n') {
			for (int k = j; k < lineLength; k++) {
				(*arr)[i][k] = ' ';
			}
			i++, j = 0;
		} else {
			(*arr)[i][j] = (char) c;
			j++;
		}
	}
}

void movePM(uint32_t lineCount, uint32_t lineLength) {
	switch (PM.irany) {
		case jobbra:
			PM.oszlop++;
			break;
		case balra:
			PM.oszlop--;
			break;
		case fel:
			PM.sor--;
			break;
		case le:
			PM.sor++;
			break;
	}
	
	if (PM.oszlop < 0) {
		PM.oszlop = lineLength - 1;
	} else if (PM.oszlop >= lineLength) {
		PM.oszlop = 0;
	}
	
	if (PM.sor < 0) {
		PM.sor = lineCount - 1;
	} else if (PM.sor >= lineCount) {
		PM.sor = 0;
	}
}

void reverseStack(stack<int32_t> *s) {
	int i = 0, size = s->size();
	int32_t *tmp = new int32_t[size];
	while (!s->empty()) {
		tmp[i++] = s->top();
		s->pop();
	}

	for (i = 0; i < size; i++) s->push(tmp[i]);

	delete[] tmp;

	/* Régi nem működő megoldás (ugyanúgy töltöttem vissza az eredeti stack-et, ahogy volt.
	stack<int32_t> tmp;
	while (!s->empty()) {
		tmp.push(s->top());
		s->pop();
	}
	while (!tmp.empty()) {
		s->push(tmp.top());
		tmp.pop();
	}
	*/
}


// DEBUG
void printCode(vector<vector<char>> code) {
	for(vector<char> vas : code) {
		for(char asd : vas) cout << asd;
		cout << endl;
	}
}

void printStack(stack<int32_t> st) {
	stack<int32_t> s = st;
	while (!s.empty()) {
		cout << s.top() << ' ';
		s.pop();
	}
	cout << endl;
}
// DEBUG vége

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}
	
	FILE *f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "Error while opening file: %s\nMessage: %s\n", argv[1], strerror(errno));
		exit(2);
	}
	
	pair<uint32_t, uint32_t> codeSize = readSize(f);
	
	if (codeSize.second == 0) {
		fprintf(stderr, "Error: there are only empty lines\n");
	}
	
	fseek(f, 0, SEEK_SET);
	
	vector<vector<char>> code(codeSize.first, vector<char>(codeSize.second));
	
	readCode(f, &code);
	
	fclose(f);
	
	int32_t osztaly[25] = {}, p = 1;
	register int32_t r = 0;
	stack<int32_t> s;
	
	char c;
	int inputChar;
	int32_t x, y;
	while (true) {
		c = code[PM.sor][PM.oszlop];
		//cout << c;
		switch (c) {
			case ';':
				exit(0);
				break;
			case '>':
				PM.irany = jobbra;
				break;
			case '<':
				PM.irany = balra;
				break;
			case '^':
				PM.irany = fel;
				break;
			case 'v':
				PM.irany = le;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				s.push(c - '0');
				break;
			case '+':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y + x);
				break;
			case '-':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y - x);
				break;
			case '/':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y / x);
				break;
			case '*':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y * x);
				break;
			case '%':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y % x);
				break;
			case '=':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y == x);
				break;
			case ')':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y > x);
				break;
			case '(':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(y < x);
				break;
			case 'i':
				inputChar = getchar();
				s.push(inputChar);
				break;
			case 'm':
				inputChar = getchar();
				if (inputChar == EOF) exit(0);
				s.push(inputChar);
				break;
			case 'a':
				if (s.empty()) goto error;
				printf("%c", s.top());
				s.pop();
				break;
			case 'n':
				if (s.empty()) goto error;
				cout << s.top();
				s.pop();
				break;
			case '?':
				if (s.empty()) goto error;
				if (!s.top()) {
					movePM(codeSize.first, codeSize.second);
				}
				s.pop();
				break;
			case '&':
				if (s.empty()) goto error;
				r = s.top();
				s.pop();
				break;
			case '@':
				s.push(r);
				break;
			case ':':
				if (s.empty()) goto error;
				s.push(s.top());
				break;
			case '~':
				if (s.empty()) goto error;
				s.pop();
				break;
			case '$':
				if (s.size() < 2) goto error;
				x = s.top();
				s.pop();
				y = s.top();
				s.pop();
				s.push(x);
				s.push(y);
				break;
			case 'l':
				s.push(s.size());
				break;
			case 's':
				s.push(p);
				break;
			case 'p':
				if (s.empty()) goto error;
				osztaly[p] = s.top();
				s.pop();
				break;
			case 'k':
				osztaly[p] = 0;
				break;
			case 'h':
				osztaly[p] *= osztaly[p];
				break;
			case 't':
				p++;
				if (p == 25) p = 1;
				break;
			case 'e':
				p--;
				if (p == 0) p = 24;
				break;
			case 'u':
				s.push(osztaly[p]);
				break;
			case 'r':
				reverseStack(&s);
				break;
			case 'b':
				if (s.empty()) goto error;
				x = s.top();
				s.pop();
				p = (x - 1) % 24 + 1;
				break;
		}
		movePM(codeSize.first, codeSize.second);
	}
	
	error:
		fprintf(stderr, "Error: stack size is %i at %i,%i ('%c')\n", s.size(), PM.sor + 1, PM.oszlop + 1, code[PM.sor][PM.oszlop]);
		exit(3);
	
	return 0;
}
