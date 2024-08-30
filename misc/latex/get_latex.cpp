/*
    From https://github.com/tdas0/lib/blob/master/latex/getlatex.cpp
*/

#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"

int HASH_LEN = 2;
int LINE_HASH_LEN = 2;

string NO_HASH = "nohash";
string NO_PRINT = "noprint";

string path = "../../library/";
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-" + to_string(HASH_LEN);

string hash_cmd_full = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6";

string hash_line_cmd = "sed -n 1','1' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-" + to_string(LINE_HASH_LEN);

bool print_all = false;

string exec(string cmd) {
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) throw runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	result.pop_back();
	return result;
}

string get_hash_arquivo(string s) {
	ifstream fin(s.c_str());
	ofstream tmp("tmp.cpp", ios::out);
	string line;
	while (getline(fin, line)) tmp << line << '\n';
	fin.close();
	tmp.close();
	string hash = exec(hash_cmd);
	return hash;
}
string get_hash_arquivo_full(string s) {
	ifstream fin(s.c_str());
	ofstream tmp("tmp.cpp", ios::out);
	string line;
	while (getline(fin, line)) tmp << line << '\n';
	fin.close();
	tmp.close();
	string hash = exec(hash_cmd_full);
	return hash;
}

bool find_in_file(string s, string t) {
	ifstream fin(s.c_str());
	bool found = false;
	string line;
	while (getline(fin, line)) {
		for (int i = int(t.size()) - 1; i < line.size(); i++) {
			if (line.substr(i - t.size() + 1, t.size()) == t) {
				found = true;
				break;
			}
		}
	}
	return found;
}

bool find_string_on_string(string s,string pat){
	for(int i=0;i+pat.size() <= s.size();i++)
		if(s.substr(i,pat.size())==pat)
			return 1;
	return 0;
}

bool is_comment(string line) {
	while (line.size() and (line[0] == ' ' or line[0] == '\t'))
		line = line.substr(1);
	bool comment = line.size() == 0;
	if (line.size() >= 2 and line.substr(0, 2) == "//") comment = true;
	if (line.size() >= 2 and line.substr(0, 2) == "/*") comment = true;
	if( 1 ){
		for(int i=0;i+1<line.size();i++){
			if(line.substr(i,2) == "/*")break;
			if(line[i] == '*' && line[i+1]=='/')comment = true;
		}
	}
	return comment;
}

vector<string> split(string line, char c) {
	vector<string> ret;
	string cur;
	line.push_back(c);
	for (char at : line) {
		if (at == c) {
			if (cur.size()) ret.push_back(cur);
			cur.clear();
			continue;
		}
		cur += at;
	}
	return ret;
}

set<string> get_flags(string file) {
	ifstream fin(file.c_str());
	string line;
	getline(fin, line);
	fin.close();
	while (line.size() and line[0] != '[') line = line.substr(1);
	if (!line.size() or line.back() != ']') return {};
	vector<string> flags = split(line.substr(1, line.size() - 2), ',');
	return set<string>(flags.begin(), flags.end());
}

void remove_flags(string& line) {
	int has_flags = 0;
	for (char c : line) {
		if (has_flags == 0 and c == '[') has_flags++;
		if (has_flags == 1 and c == ']') has_flags++;
	}
	if (has_flags != 2) return;
	int idx = -1;
	for (int i = 0; i < line.size(); i++) if (line[i] == '[') {
		idx = i;
		break;
	}
	while (line.size() > idx) line.pop_back();
	while (line.size() and line.back() == ' ') line.pop_back();
}

void printa_arquivo_codigo(string file, bool extra = false,string Hash = "") {
	cout << "\\begin{lstlisting}\n";
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	bool started_code = false;
	ofstream pref("pref.cpp", ios::out);
	pref.close();
	int depth = 0;
	int abriuComment=0;
	cout << "Hash: "<<Hash<<endl;
	while (getline(fin, line)) {
		// if(find_string_on_string(line, "#pragma once"))continue;
		// if (count++ < 2 and !extra) continue;
		// cerr << line << endl;
		for (char c : line) {
			if (c == '{') depth++;
			if (c == '}') depth--;
		}
		for(int i=0;i<(int)line.size()-1;i++){
			if(line[i]=='/' && line[i+1]=='*')abriuComment++;
			else if(line[i+1]=='/' && line[i]=='*')abriuComment--;
		}
		
		bool comment = is_comment(line) || (abriuComment>0);
		// cerr <<"OI NAIM"<<": "<<line<<" = "<<abriuComment<<endl;;
		bool bef = started_code;
		if (!comment) started_code = true;

		// if(!started_code && find_string_on_string(line,"www."))continue;
		// if(!started_code && find_string_on_string(line,"github."))continue;
		// if(!started_code && find_string_on_string(line,"https"))continue;
		
		

		if (!extra and started_code) {
			ofstream pref("pref.cpp", ios::app);
			pref << line << '\n';
			pref.close();
			ofstream tmp("tmp.cpp", ios::out);
			tmp << line;
			tmp.close();
			if (comment) {
				if (depth != 0) {
					for (int i = 0; i < HASH_LEN + LINE_HASH_LEN + 2; i++)
						cout << " ";
				}
			} else {
				string hash_line = exec(hash_line_cmd);
				string hash_pref = get_hash_arquivo("pref.cpp");
				cout << hash_pref << " " << hash_line << " ";
			}
		}
		cout << line << endl;
	}
	fin.close();
	cout << "\\end{lstlisting}\n\n";
}

void printa_arquivo(string file, bool extra = false) {
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and !extra) continue;
		cout << line << endl;
	}
	fin.close();
}
string normalize_name(string s){
	string t="";
	int upper=1;
	for(auto& c:s){
		if(c=='_' || c=='-'){
			upper=1;continue;;
		}
		if(upper && c>='a' && c<='z'){
			t+=c-'a'+'A';
		}else t+=c;
		upper=0;
	}
	return t;
}

string get_name(string file) {
	string s = "defaultName";
	for(int i=0;i<file.size();i++){
		if(file[i]=='/' && i+1<file.size())s=file.substr(i+1);
	}
	return normalize_name(s);
}

void printa_cuidado(string s) {
	for (char c : s) {
		if (c == '^') cout << '\\';
		cout << c;
		if (c == '^') cout << "{}";
	}
}

bool printa_listing(string sub, string file, bool extra = false) {
	set<string> flags = get_flags(file);

	if (!print_all and flags.count(NO_PRINT)) return false;

	// if (!extra and !flags.count(NO_HASH)) {
	// 	if (!find_in_file(file, get_hash_arquivo(file)))
	// 		cerr << RED << "WARNING" << RESET << ": hash nao encontrado para: "
	// 		<< file.substr(10) << '\n';
	// }

	cout << "\\subsection{";
	if (!extra) printa_cuidado(get_name(file));
	else printa_cuidado(sub);
	cout << "}\n";

	printa_arquivo_codigo(file, extra, (get_hash_arquivo_full(file)));
	return true;
}

void dfs(vector<pair<string, string>>& files, string s, bool extra = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) dfs(files, s + "/" + string(entry->d_name), extra);
		else {
			if (!extra) files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
			else printa_listing(entry->d_name, s + "/" + entry->d_name, extra);
		}
	}
}

void printa_section(string s) {
	cout << "\n\n";

	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% " << s << "\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	cout << "\\section{" << s << "}\n\n";
}

string lower(string s) {
	for (char& c : s) if (c >= 'A' and c <= 'Z') c ^= 32;
	return s;
}

int main(int argc, char** argv) {

	if (argc > 1) {
		string arg1(argv[1]);
		if (arg1 == "--printall") {
			print_all = true;
			cerr << "Printing all files..." << endl << endl;
		}
	}
	cerr<<"vamos la"<<endl;cerr.flush();
	
	printa_arquivo("header.tex", true);
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		// cerr << entry->d_name <<" "<<entry->d_type << endl;cerr.flush();
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		string dir(entry->d_name);
		// cerr << "foi"<<endl;cerr.flush();
		if (dir == "Extra") continue;
		printa_section(dir);
		// cerr << "OI"<<endl;cerr.flush();
		vector<pair<string, string>> files;
		dfs(files, path + dir);
		// cerr << "aqui"<<endl;cerr.flush();
		sort(files.begin(), files.end(), [&](auto f1, auto f2) {
			return lower(get_name(f1.second)) < lower(get_name(f2.second));
		});
		// cerr<<"?????"<<endl;
		cerr << "=== " << dir << " ===" << endl;
		for (auto [f, path] : files) {
			bool printed = printa_listing(f.substr(0, f.size() - 4), path);
			if (printed) cerr << get_name(path) << endl;
		}
		cerr << endl;
	}

	cout << "\\pagebreak" << endl;
	// printa_section("Extra");
	vector<pair<string, string>> files;
	dfs(files, path + "Extra", true);

	cout << "\\end{document}\n";
	return 0;
}