#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXM 16
#define MAXN 50010
#define MAXQ 210
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define mii map<int, int>
#define umii unordered_map<int, int>
#define allof(x) x.begin(), x.end()
#define DEBUG 1
// #define NOT_DMOJ 0
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

inline int GCD (int a, int b) { return b == 0 ? a : GCD(b, a % b); }
inline int LCM (int a, int b) { return a * b / GCD(a, b); }
inline ll PowMod (ll a, ll b, ll mod) { ll val = 1; while (b) { if (b & 1) val = (val * a) % mod; a = (a * a) % mod; b >>= 1; } return val; }

template <class T> struct is_iterator {
    template <class U, typename enable_if<!is_convertible<U, const char*>::value, int>::type = 0>
    constexpr static auto has_indirection(int) -> decltype(*declval<U>(), bool()) { return true; }
    template <class> constexpr static bool has_indirection(long) { return false; }
    constexpr static bool value = has_indirection<T>(0);
};

using uint = unsigned int;
// Buffer size should be 2^12 or 2^13 for optimal performance with files.
const uint BUFFER_SIZE = 1 << 8;
// Maximum possible length of string representing primitive type
// assuming we won't encounter huge double values.
const uint MAX_LENGTH = 1 << 7;

namespace Detail {
    struct Width { uint value; };
    struct Fill { char value; };
    struct Base { uint value; };
    struct Precision { uint value; };
    struct Delimiter { const char* value; };
}  // namespace Detail

Detail::Width setWidth(uint value = 0) { return {value}; }
Detail::Fill setFill(char value = ' ') { return {value}; }
Detail::Base setBase(uint value = 10) { assert(2 <= value && value <= 36); return {value}; }
Detail::Precision setPrecision(uint value = 9) { assert(value < MAX_LENGTH); return {value}; }
Detail::Delimiter setDelimiter(const char* value = " ") { return {value}; }

/******************************* input classes ********************************/
class InputDevice {
protected:
    const char* head;
    const char* tail;

    InputDevice(const char* head, const char* tail) : head(head), tail(tail), base(setBase().value) {}

    virtual void fillInput() = 0;

    inline char nextChar() {
        if (__builtin_expect(head >= tail, false)) fillInput();
        return *head++;
    }

    template <class I> int readUnsignedIntGeneral(I& arg, char c) {
        I value = 0;
        int length = 0;
        for (;; ++length, c = nextChar()) {
            if (isDigit(c)) c -= '0';
            else if (isUpper(c)) c -= 'A' - 10;
            else if (isLower(c)) c -= 'a' - 10;
            else c = base;
            if (c >= base) break;
            value = base * value + c;
        }
        arg = value;
        return --head, length;
    }

    template <class I> inline int readUnsignedInt(I& arg, char c) {
        if (__builtin_expect(base > 10, false)) return readUnsignedIntGeneral(arg, c);
        I value = 0;
        int length = 0;
        for (; static_cast<unsigned char>(c - '0') < base; ++length, c = nextChar())
            value = base * value + c - '0';
        arg = value;
        return --head, length;
    }

    template <class I> inline bool readSignedInt(I& arg, char c) {
        bool negative = c == '-';
        if (negative) c = nextChar();
        typename make_unsigned<I>::type unsignedArg;
        if (readUnsignedInt(unsignedArg, c) == 0) return false;
        arg = negative ? ~static_cast<I>(unsignedArg - 1) : static_cast<I>(unsignedArg);
        return true;
    }

    template <class F> bool readFloatingPoint(F& arg, char c) {
        bool negative = c == '-';
        if (negative) c = nextChar();
        unsigned long long integerPart;
        if (readUnsignedInt(integerPart, c) == 0) return false;
        arg = static_cast<F>(integerPart);
        if (nextChar() == '.') {
            unsigned long long fractionalPart = 0;
            int fractionalLength = readUnsignedInt(fractionalPart, nextChar());
            if (fractionalLength > 0) {
                unsigned long long basePower = 1;
                for (; fractionalLength; --fractionalLength) basePower *= base;
                arg += static_cast<F>(fractionalPart) / basePower;
            }
        } else --head;
        if (negative) arg = -arg;
        return true;
    }

public:
    uint base;

    InputDevice(InputDevice const&) = delete;
    InputDevice& operator = (InputDevice const&) = delete;

    static inline bool isSpace(char c) { return static_cast<unsigned char>(c - '\t') < 5 || c == ' '; }
    static inline bool isDigit(char c) { return static_cast<unsigned char>(c - '0') < 10; }
    static inline bool isUpper(char c) { return static_cast<unsigned char>(c - 'A') < 26; }
    static inline bool isLower(char c) { return static_cast<unsigned char>(c - 'a') < 26; }
    static inline bool isOneOf(char c, const char* str) { return strchr(str, c) != nullptr; }

    void putBack() { --head; }  // can be called only once directly after successfully reading a character

    inline bool readChar(char& arg) {
        if (__builtin_expect(head >= tail, false)) {
            fillInput();
            if (__builtin_expect(head >= tail, false)) return arg = '\0', false;
        }
        return arg = *head++, true;
    }

    template <class UnaryPredicate>
    inline char skipCharacters(UnaryPredicate isSkipped) {
        char c;
        do { c = nextChar(); } while (isSkipped(c));
        return c;
    }
    inline char skipCharacters() { return skipCharacters(isSpace); }

    template <class UnaryPredicate>
    inline int readString(char* arg, int limit, UnaryPredicate isTerminator) {
        skipCharacters(isTerminator);
        // put back first non-skipped character, reserve space for null character
        int charsRead = 0;
        for (--head, --limit; head < tail; fillInput()) {
            ptrdiff_t chunkSize = find_if(head, min(tail, head + limit - charsRead), isTerminator) - head;
            arg = copy_n(head, chunkSize, arg);
            head += chunkSize;
            charsRead += chunkSize;
            if (chunkSize == 0 || head < tail) break;
        }
        return *arg = '\0', charsRead;
    }

    inline int readString(char* arg, int limit, const char* terminators) {
        if (!*terminators) return readString(arg, limit, InputDevice::isSpace);
        return readString(arg, limit, [terminators](char c) { return InputDevice::isOneOf(c, terminators); });
    }

    inline bool read(Detail::Base newBase) { base = newBase.value; return true; }
    inline bool read() { return true; }
    inline bool read(char& arg) { return readChar(arg); }
    template <class I> inline typename enable_if<is_integral<I>::value && is_unsigned<I>::value,
            bool>::type read(I& arg) { return readUnsignedInt(arg, skipCharacters()) > 0; }
    template <class I> inline typename enable_if<is_integral<I>::value && is_signed<I>::value,
            bool>::type read(I& arg) { return readSignedInt(arg, skipCharacters()); }
    template <class F> inline typename enable_if<is_floating_point<F>::value,
            bool>::type read(F& arg) { return readFloatingPoint(arg, skipCharacters()); }
    inline bool read(const char& arg) { skipCharacters([arg](char c) { return arg != c; }); return true; }
    inline bool read(const char* arg) {
        if (*arg) skipCharacters([arg](char c) { return InputDevice::isOneOf(c, arg); });
        else skipCharacters();
        return putBack(), true;
    }
    inline bool read(bool (*isSkipped)(char)) { skipCharacters(isSkipped); putBack(); return true; }
    template <class I, class Terminator, class... Ts> inline typename enable_if<is_integral<I>::value,
            bool>::type read(char* arg, I limit, Terminator terminator, Ts&&... args) {
        readString(arg, static_cast<int>(limit), terminator);
        return read(forward<Ts>(args)...);
    }
    template <class I> inline typename enable_if<is_integral<I>::value,
            bool>::type read(char* arg, I limit) { return read(arg, limit, ""); }
    template <class... Ts>
    inline bool read(char* first, char* last, Ts&&... args) {
        return read(first, static_cast<int>(last - first), forward<Ts>(args)...);
    }
    template <int N, class... Ts>
    inline bool read(char (&arg)[N], Ts&&... args) { return read(static_cast<char*>(arg), N, forward<Ts>(args)...); }
    template <class Terminator, class... Ts>
    inline bool read(string& arg, Terminator terminator, Ts&&... args) {
        for (int length = 16, last = 0;; last += length, length <<= 1) {
            arg.resize(last + length);
            int charsRead = readString(&arg[last], length + 1, terminator);
            if (charsRead < length) {
                arg.resize(last + charsRead);
                return read(forward<Ts>(args)...);
            }
        }
    }
    inline bool read(string& arg) { return read(arg, ""); }
    template <class T1, class T2>
    inline bool read(pair<T1, T2>& arg) { return read(arg.first, arg.second); }
    template <class T>
    inline bool read(complex<T>& arg) {
        T real, imag;
        if (!read(real, imag)) return false;
        arg.real(real), arg.imag(imag);
        return true;
    }
    template <class T>
    inline bool read(vector<T>& arg) {
        uint n;
        if (!read(n)) return false;
        arg.resize(n);
        return read(arg.begin(), arg.end());
    }
    template <class Iterator, class... Ts> inline typename enable_if<is_iterator<Iterator>::value,
            bool>::type read(Iterator first, Iterator last, Ts&&... args) {
        for (; first != last; ++first) if (!read(*first)) return false;
        return read(forward<Ts>(args)...);
    }
    template <class Iterator, class I, class... Ts>
    inline typename enable_if<is_iterator<Iterator>::value && is_integral<I>::value,
            bool>::type read(Iterator first, I count, Ts&&... args) { return read(first, first + count, forward<Ts>(args)...); }
    template <class T>
    inline auto read(T& arg) -> decltype(arg.read(*this)) { return arg.read(*this); }
    template <class T0, class T1, class... Ts>
    inline typename enable_if<!is_iterator<T0>::value && !is_convertible<T0, char*>::value,
            bool>::type read(T0&& arg0, T1&& arg1, Ts&&... args) {
        return read(forward<T0>(arg0)) && read(forward<T1>(arg1), forward<Ts>(args)...);
    }
};

class InputFile : public InputDevice {
    FILE* file;
    bool lineBuffered;
    bool owner;
    char buffer[BUFFER_SIZE];

    void fillInput() override {
        head = buffer;
        *buffer = '\0';
        if (__builtin_expect(!lineBuffered, true)) {
            tail = head + fread(buffer, 1, BUFFER_SIZE, file);
        } else {
            tail = head;
            if (fgets(buffer, BUFFER_SIZE, file)) while (*tail) ++tail;
        }
    }

public:
    InputFile(FILE* file = stdin, bool lineBuffered = true, bool takeOwnership = false)
            : InputDevice(buffer, buffer) , file(file), lineBuffered(lineBuffered), owner(takeOwnership) {}
    InputFile(const char* fileName) : InputFile(fopen(fileName, "r"), false, true) {}
    ~InputFile() { if (owner) fclose(file); }
};

// Picks up data appended to the string but doesn't handle reallocation.
class InputString : public InputDevice {
    void fillInput() override { while (*tail) ++tail; }

public:
    InputString(const string& s) : InputDevice(s.data(), s.data() + s.size()) {}
    InputString(const char* s) : InputDevice(s, s + strlen(s)) {}
};

/******************************* output classes *******************************/
class OutputDevice {
protected:
    char buffer[BUFFER_SIZE + MAX_LENGTH];
    char* output;
    char* end;
    bool separate;

    OutputDevice() : output(buffer), end(buffer + BUFFER_SIZE + MAX_LENGTH), separate(false)
            , width(setWidth().value), fill(setFill().value), base(setBase().value), precision(setPrecision().value)
            , delimiter(setDelimiter().value) { computeBasePower(); }

    virtual void writeToDevice(uint count) = 0;

    inline void flushMaybe() {
        if (__builtin_expect(output >= buffer + BUFFER_SIZE, false)) {
            writeToDevice(BUFFER_SIZE);
            output = copy(buffer + BUFFER_SIZE, output, buffer);
        }
    }

    void computeBasePower() {
        basePower = 1;
        for (uint i = 0; i < precision; ++i) basePower *= base;
    }

    template <class I> inline char* writeUnsignedInt(I arg, char* last) {
        if (__builtin_expect(arg == 0, false)) *--last = '0';
        if (__builtin_expect(base == 10, true)) {
            for (; arg; arg /= 10) *--last = '0' + arg % 10;
        } else for (; arg; arg /= base) {
                I digit = arg % base;
                *--last = digit < 10 ? '0' + digit : 'A' - 10 + digit;
            }
        return last;
    }

    template <class I> inline char* writeSignedInt(I arg, char* last) {
        auto unsignedArg = static_cast<typename make_unsigned<I>::type>(arg);
        if (arg < 0) {
            last = writeUnsignedInt(~unsignedArg + 1, last);
            *--last = '-';
            return last;
        }
        return writeUnsignedInt(unsignedArg, last);
    }

    template <class F> char* writeFloatingPoint(F arg, char* last) {
        bool negative = signbit(arg);
        if (negative) arg = -arg;
        if (isnan(arg)) for (int i = 0; i < 3; ++i) *--last = i["NaN"];
        else if (isinf(arg)) for (int i = 0; i < 3; ++i) *--last = i["fnI"];
        else {
            auto integerPart = static_cast<unsigned long long>(arg);
            auto fractionalPart = static_cast<unsigned long long>((arg - integerPart) * basePower + F(0.5));
            if (fractionalPart >= basePower) ++integerPart, fractionalPart = 0;
            char* point = last - precision;
            if (precision > 0) {
                ::fill(point, writeUnsignedInt(fractionalPart, last), '0');
                *--point = '.';
            }
            last = writeUnsignedInt(integerPart, point);
        }
        if (negative) *--last = '-';
        return last;
    }

    inline int writeT(char* first) {
        int delimiterLenght = separate ? writeDelimiter() : 0;
        separate = true;
        uint charsWritten = static_cast<uint>(end - first);
        if (__builtin_expect(charsWritten < width, false))
            charsWritten += writeFill(width - charsWritten);
        output = copy(first, end, output);
        flushMaybe();
        return delimiterLenght + static_cast<int>(charsWritten);
    }

    inline int writeFill(uint count) {
        int charsWritten = static_cast<int>(count);
        if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
            if (count == 1) *output++ = fill;
            else output = fill_n(output, count, fill);
        } else for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
                if (chunkSize > count) chunkSize = count;
                output = fill_n(output, chunkSize, fill);
                flushMaybe();
                if ((count -= chunkSize) == 0) break;
            }
        return charsWritten;
    }

public:
    uint width;
    char fill;
    uint base;
    uint precision;
    unsigned long long basePower;
    string delimiter;

    OutputDevice(OutputDevice const&) = delete;
    OutputDevice& operator = (OutputDevice const&) = delete;
    virtual ~OutputDevice() {};

    inline int writeChar(char arg) { separate = false; *output++ = arg; flushMaybe(); return 1; }

    inline int writeString(const char* arg, size_t length, bool checkWidth = true) {
        separate = false;
        uint count = static_cast<uint>(length);
        int charsWritten = static_cast<int>(count) + (checkWidth && count < width ? writeFill(width - count) : 0);
        if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
            if (count == 1) *output++ = *arg;
            else output = copy_n(arg, count, output);
        } else for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
                if (chunkSize > count) chunkSize = count;
                output = copy_n(arg, chunkSize, output);
                flushMaybe();
                if ((count -= chunkSize) == 0) break;
                arg += chunkSize;
            }
        return charsWritten;
    }

    inline int writeDelimiter() { return writeString(delimiter.c_str(), delimiter.size(), false); }

    inline void flush() {
        writeToDevice(static_cast<uint>(output - buffer));
        output = buffer;
    }

    // property setters
    inline int write(Detail::Width newWidth) { width = newWidth.value; return 0; }
    inline int write(Detail::Fill newFill) { fill = newFill.value; return 0; }
    inline int write(Detail::Base newBase) { base = newBase.value; computeBasePower(); return 0; }
    inline int write(Detail::Precision newPrecision) {
        precision = newPrecision.value; computeBasePower(); return 0;
    }
    inline int write(Detail::Delimiter newDelimiter) { delimiter = newDelimiter.value; return 0; }
    // primitive types
    inline int write() { return 0; }
    inline int write(char arg) { return writeChar(arg); }
    template <class I> inline typename enable_if<is_integral<I>::value && is_unsigned<I>::value,
            int>::type write(I arg) { return writeT(writeUnsignedInt(arg, end)); }
    template <class I> inline typename enable_if<is_integral<I>::value && is_signed<I>::value,
            int>::type write(I arg) { return writeT(writeSignedInt(arg, end)); }
    template <class F> inline typename enable_if<is_floating_point<F>::value,
            int>::type write(F arg) { return writeT(writeFloatingPoint(arg, end)); }
    // complex types
    inline int write(const char* arg) { return writeString(arg, strlen(arg)); }
    template <int N>
    inline int write(char (&arg)[N]) { return writeString(arg, strlen(arg)); }
    inline int write(const string& arg) { return writeString(arg.c_str(), arg.size()); }
    template <class T1, class T2>
    inline int write(const pair<T1, T2>& arg) {
        int charsWritten = write(arg.first);
        charsWritten += writeDelimiter();
        return charsWritten + write(arg.second);
    }
    template <class T>
    inline int write(const complex<T>& arg) { return write(real(arg), imag(arg)); }
    // ranges
    template <class Iterator, class... Ts> inline typename enable_if<is_iterator<Iterator>::value,
            int>::type write(Iterator first, Iterator last, Ts&&... args) {
        int charsWritten = 0;
        for (; first != last; charsWritten += ++first == last ? 0 : writeDelimiter()) charsWritten += write(*first);
        return charsWritten + write(forward<Ts>(args)...);
    }
    template <class Iterator, class I, class... Ts>
    inline typename enable_if<is_iterator<Iterator>::value && is_integral<I>::value,
            int>::type write(Iterator first, I count, Ts&&... args) { return write(first, first + count, forward<Ts>(args)...); }
    // generic forwarding
    template <class T>
    inline auto write(const T& arg) -> decltype(arg.write(*this)) { return arg.write(*this); }
    template <class T0, class T1, class... Ts> inline typename enable_if<!is_iterator<T0>::value,
            int>::type write(T0&& arg0, T1&& arg1, Ts&&... args) {
        int charsWritten = write(forward<T0>(arg0));
        return charsWritten + write(forward<T1>(arg1), forward<Ts>(args)...);
    }
};

class OutputFile : public OutputDevice {
    FILE* file;
    bool owner;

    void writeToDevice(uint count) override {
        fwrite(buffer, 1, count, file);
        fflush(file);
    }

public:
    OutputFile(FILE* file = stdout, bool takeOwnership = false) : file(file), owner(takeOwnership) {}
    OutputFile(const char* fileName) : OutputFile(fopen(fileName, "w"), true) {}
    ~OutputFile() override { flush(); if (owner) fclose(file); }
};

class OutputString : public OutputDevice {
    string& str;

    void writeToDevice(uint count) override { str.append(buffer, count); }

public:
    OutputString(string& str) : OutputDevice(), str(str) {}
    ~OutputString() override { flush(); }
};

unique_ptr<InputDevice> input;
unique_ptr<OutputDevice> output;

template <class... Ts> inline bool read(Ts&&... args) { return input->read(forward<Ts>(args)...); }
template <class... Ts> inline int write(Ts&&... args) { return output->write(forward<Ts>(args)...); }
template <class... Ts> inline int writeln(Ts&&... args) { return write(forward<Ts>(args)..., '\n'); }
void flush() { output->flush(); }

/*******************************************************************************
 * Read returns true if all the arguments were successfully read. Parameters:
 * - setBase(uint): base for integer and floating point numbers
 * Single variable of one of the following types:
 * - char, standard integer and floating point types
 * - pair, complex
 * - vector (size and then the elements)
 * Characters skip:
 * - char: skip until the given character is encountered and read it
 * - const char*: skip all the characters from the string
 * - predicate: skip all the characters satisfying the predicate
 * Strings: read until character limit is reached or termination character is found
 *   (one of the characters in a given string or defined by predicate, isspace by default)
 * - char (&)[N], terminator
 * - char*, int limit, terminator
 * - string&, terminator
 * Ranges:
 * - Iterator first, Iterator last
 * - Iterator first, int count
 *******************************************************************************
 * Write returns number of characters written. Parameters:
 * - setWidth(uint): minimum width of a single element to write (except character)
 * - setFill(char): character prepended to an element until set width is reached
 * - setBase(uint): base for integer and floating point numbers
 * - setPrecision(uint): number of digits after the decimal point
 * - setDelimiter(const char*): delimiter automatically inserted between elements
 *   that are not strings or characters
 * Single variable of one of the following types:
 * - char, standard integer and floating point types
 * - string, const char*
 * - pair, complex
 * Ranges:
 * - Iterator first, Iterator last
 * - Iterator first, int count
 ******************************************************************************/


struct Disjoint {
private:
	int N;
	vi lead, rank;

public:
	Disjoint(int N) : N(N), lead(N + 1), rank(N + 1) { }

	inline void make_Set () {
		for (int i=1; i<=N; i++) {
			lead[i] = i;
			rank[i] = 1;
		}
	}
	
	inline int Find (int x) {
		while (x ^ lead[x]) {
			lead[x] = lead[lead[x]];
			x = lead[x];
		}
		return x;
	}

	inline bool Merge (int x, int y) {
		return Find(x) ^ Find(y);
	}

	inline void Union (int x, int y) {
		int c = Find(x);
		int d = Find(y);
		if (Merge(x, y)) {
			if (rank[c] > rank[d]) {
				rank[c] += rank[d];
				lead[d] = c;
			}
			else {
				rank[d] += rank[c];
				lead[c] = d;
			}
		}
	}

	inline int Cnt (int x) {
		return rank[x];
	}
};

Disjoint ds(MAXN);

int N, M, Q, a, b, w, s, e, ind, idx;
int depth[MAXN], par[MAXN], nodes[MAXN];
ll dist[MAXN];
ll cost[MAXQ][MAXN];
int anc[MAXM][MAXN];
bool vis[MAXN], flag[MAXN], processed[MAXN];
vector<pii> adj[MAXN];
vector<pair<int, pii> > edgelist;

inline void DFS (int node, int prev, ll weight) {
	depth[node] = prev >= 0 ? depth[prev] + 1 : 0;
	par[node] = prev;
	dist[node] = weight;
	for (auto i : adj[node]) {
		if (i.f == prev) continue;
		DFS(i.f, node, weight + i.s);
	}
}

inline void Build_Sparse_Table () {
	memcpy(anc[0], par, sizeof(par));
	for (int i=1; i<MAXM; i++) {
		for (int j=0; j<N; j++) {
			anc[i][j] = anc[i - 1][j] >= 0 ? anc[i - 1][anc[i - 1][j]] : -1;
		}
	}
}

inline int LCA (int x, int y) {
	if (depth[x] < depth[y]) swap(x, y);
	int diff = depth[x] - depth[y];
	for (int i=0; i<MAXM; i++) {
		if (diff & (1 << i)) x = anc[i][x];
	}
	if (x == y) return x;
	for (int i=MAXM - 1; i>=0; i--) {
		if (anc[i][x] ^ anc[i][y]) {
			x = anc[i][x];
			y = anc[i][y];
		}
	}
	return par[x];
}

inline void Dijkstra (int src) {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
	int idx = nodes[src];
	cost[idx][src] = 0LL;
	pq.push(mp(0, src));
	while (!pq.empty()) {
		pii curr = pq.top(); pq.pop();
		if (curr.f > cost[idx][curr.s]) continue;
		for (auto i : adj[curr.s]) {
			if (cost[idx][i.f] > cost[idx][curr.s] + i.s) {
				cost[idx][i.f] = cost[idx][curr.s] + i.s;
				pq.push(mp(cost[idx][i.f], i.f));
			}
		}
	}
}

inline void SPFA (int src) {
	queue<int> q;
	int idx = nodes[src];
	cost[idx][src] = 0LL;
	vis[src] = 1;
	q.push(src);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		vis[curr] = 0;
		for (auto i : adj[curr]) {
			if (cost[idx][i.f] > cost[idx][curr] + i.s) {
				cost[idx][i.f] = cost[idx][curr] + i.s;
				if (!vis[i.f]) {
					vis[i.f] = 1;
					q.push(i.f);
				}
			}
		}
	}
}

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	input.reset(new InputFile(stdin, 0));
	output.reset(new OutputFile());
	read(N, M);
	for (int i=1; i<=M; i++) {
		read(a, b, w);
		edgelist.pb(mp(--a, mp(--b, w)));
	}
	ds.make_Set();
	for (size_t i=0; i<edgelist.size(); i++) {
		pair<int, pii> &next = edgelist[i];
		if (ds.Merge(next.f, next.s.f)) {
			ds.Union(next.f, next.s.f);
			processed[i] = 1;
			adj[next.f].pb(mp(next.s.f, next.s.s));
			adj[next.s.f].pb(mp(next.f, next.s.s));
		}
	}
	DFS(0, -1, 0LL);
	Build_Sparse_Table();
	memset(cost, 0x3f, sizeof(cost));
	for (size_t i=0; i<edgelist.size(); i++) {
		pair<int, pii> &next = edgelist[i];
		if (processed[i]) continue;
		adj[next.f].pb(mp(next.s.f, next.s.s));
		adj[next.s.f].pb(mp(next.f, next.s.s));
	}
	for (size_t i=0; i<edgelist.size(); i++) {
		pair<int, pii> &next = edgelist[i];
		if (processed[i]) continue;
		if (!nodes[next.f]) nodes[next.f] = ind++;
		if (!flag[next.f]) {
			flag[next.f] = 1;
			SPFA(next.f);
		}
	}
	read(Q);
	while (Q--) {
		read(s, e);
		ll ans = dist[--s] + dist[--e] - (dist[LCA(s, e)] << 1);
		for (int i=0; i<ind; i++) ans = min(ans, cost[i][s] + cost[i][e]);
		writeln(ans);
	}
	return 0;
}

/*
5 4
1 2 1
1 3 1
2 4 1
2 5 1
3
1 2
4 3
4 5

Ans:
1
3
2

8 13
1 2 4
2 3 6
3 4 1
4 5 12
5 6 3
6 7 8
7 8 7
1 4 1
1 8 3
2 6 9
2 7 1
4 6 3
6 8 2
8
1 5
1 7
2 3
2 8
3 7
3 4
6 8
7 8

Ans:
7
5
6
7
7
1
2
7
*/

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */