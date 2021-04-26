
/***************************************
Author:lixingbo
data:2021 04 26

buglist
1.若[]list 含有多个object,或缺省值如[null,null],已处理
2.其他错误在生成文件头已指示
  
若需要用此APP生成结构体及基于repadjson的解析cpp文件
在生成的文件里面稍作修改亦可达到想要的目标文件。
****************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
using namespace std;



class generate
{
public:	
	int group_map();
	int demapkey(string key);
	string& trim(string &str, string::size_type pos);
	void SplitString(const string& s, vector<string>& v, const string& c);
	int start(string filename);
	map<string,vector<string> > crte;
	ofstream ofs;
	string jsonfile;
	string stroot;
};

int generate::start(string filename)
{
	jsonfile = filename;
	if(jsonfile.find("_") == -1)
	{
		cout << "filename should is mod + \"_\" + structroot\n";
		cout << "example:\"smsf_UeSmsContextData\"\n";
		return 0;
	}
	stroot = jsonfile.substr(jsonfile.find("_")+1);
	string strname = filename;
	//strname.insert(0, "./data/");
	strname.append("_struct.h");
	ofs.open(strname.c_str());
	
	ofs << "/*"<< endl;
	ofs << "Thank you use this simple tool"<< endl;
	ofs << "Portal: https://github.com/Still-her/autojson"<< endl;
	ofs << "This document may need to be modified as follows:"<< endl;
	ofs << "Missing structure field:"<< endl;
	ofs << "struct stplmnId{"<< endl;
	ofs << "string mcc;"<< endl;
	ofs << "string mnc;"<< endl;
	ofs << "};"<< endl;
	ofs << "Correct:"<< endl;
	ofs << "struct stplmnId{"<< endl;
	ofs << "string mcc;"<< endl;
	ofs << "string mnc;"<< endl;
	ofs << "string nid;"<< endl;
	ofs << "};"<< endl;
	ofs << "struct stR -> struct what you need"<< endl;
	ofs << "There are unexpected bugs"<< endl;
	ofs << "Hey, just play"<< endl;
	ofs << "*/"<< endl;
	
	ofs << "#ifndef "<< filename <<"_DEFINE_H_"<< endl;
	ofs << "#define "<< filename <<"_DEFINE_H_"<< endl;
	ofs << "#include <string>"<< endl;
	ofs << "#include <vector>"<< endl;
	ofs << "using namespace std;"<< endl;
	ofs << "namespace " << filename << "{" << endl;
	group_map();
	demapkey("R");
	ofs << "}"<< endl;
	ofs << "#endif"<< endl;
	ofs.close();
}


int generate::demapkey(string key)
{
	map<string,vector<string> >::iterator mit = crte.find(key);

	if(mit != crte.end())
	{
		
		vector<string> vtmp;
		vtmp = mit->second;

		for(vector<string>::iterator vit = vtmp.begin(); vit != vtmp.end(); vit++)
		{
			string buf = *vit;
			int nide = buf.find(":");
			string key = buf.substr(1,nide-2);
			
			map<string,vector<string> >::iterator mitmp = crte.find(key);
			if(mitmp != crte.end())
			{
				demapkey(key);
			}
		}
			
		if(mit->first == "}")
			ofs << "struct st" << stroot << "{\n";
		else
			ofs << "struct st" << mit->first << "{\n";
		for(vector<string>::iterator vit = vtmp.begin(); vit != vtmp.end(); vit++)
		{
			string buf = *vit;
			
			int nide = buf.find(":");
			if(-1 != nide)
			{
				string key = buf.substr(1,nide-2);
				char ctmp = buf[nide+1];
				switch(ctmp)
				{
					case 0:
					{
						ofs << "\tst" << key << " " << key << ";" << endl;
						
						break;
					}
					case 34:
					{
						ofs << "\tstring " << key << ";" << endl;
						
						break;
					}
					case 't':
					case 'f':
					{
						ofs << "\tbool " << key << ";" << endl;
						
						break;
					}
					case 0x30:
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34:
					case 0x35:
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
					{
						ofs << "\tint " << key << ";" << endl;
						
						break;
					}
					case 91:
					{
						switch(buf[nide+2])
						{
							case ']':
							{
								ofs << "\tvector<st" << key << "> " << key << ";" << endl;
								break;
							}
							case 0x30:
							case 0x31:
							case 0x32:
							case 0x33:
							case 0x34:
							case 0x35:
							case 0x36:
							case 0x37:
							case 0x38:
							case 0x39:
							{
								ofs << "\tvector<int> " << key << ";" << endl;
								break;
							}
							case 'N':
							case '"':
							{
								ofs << "\tvector<string> " << key << ";" << endl;
								break;
							}
							case 't':
							case 'f':
							{
								ofs << "\tvector<bool> " << key << ";" << endl;
								break;
							}
						}
						
					}
				}
			}
		}
		ofs << "};" << endl << endl;
		crte.erase(mit);
	}

	else{

		cout << "no find" << endl;
	}
	
}

int generate::group_map()
{
	//cout << "--------------1--------------------" << endl;
	//const char* file_name = "json1.data";
	std::ifstream in(jsonfile.c_str());
	if (!in.is_open()) {
		fprintf(stderr, "fail to read json file: %s\n", jsonfile.c_str());
		return -1;
	}

	string s;

	string buf;		
	while( in >> s ) 
	{    
		buf.append(s);
	}
	buf.insert(0,"\"R\":");
	in.close();

	int nide = 0;
	
	//while(nide != buf.length()-1 )
	for(int i = 0; i <10000 ; i++)
	{
		vector<string> vtmp;
		nide = buf.find_first_of("{}",nide);
		char tmp = buf[nide];
		int  pos = nide;
		nide = buf.find_first_of("{}",nide+1);
		
		if(tmp == '{' && buf[nide] == '}')
		{
			SplitString(buf.substr(pos+1,nide-pos-1),vtmp,",");
			
			int ri = buf.rfind("\"",pos);
			int li = buf.rfind("\"",ri-1);
	
			crte.insert(make_pair(buf.substr(li+1,ri-li-1),vtmp));
			
			//cout << "generate::group_map " << buf.substr(li+1,ri-li-1) << endl;

			buf.erase(pos, nide-pos+1);

			//cout << "generate::group_map " << buf << endl;

		}
	}
}

string& generate::trim(string &str, string::size_type pos = 0)
{
    static const string delim = " \r\n\t"; //删除空格或者tab字符
    pos = str.find_first_of(delim, pos);
    if (pos == string::npos)
        return str;
    return trim(str.erase(pos, 1));
}

void generate::SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

         //cout << "generate::SplitString: " << s.substr(pos1, pos2-pos1) << endl;

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
	{
		v.push_back(s.substr(pos1));
	}
        
}

class c2json
{
public:	
	
	int start(string filename);
	//s.open("test.cpp");
	int call(string &buf,int pos );
	int init();
	ofstream ofs;
	string jsonfile;
	string stroot;
	int arrcut = 0;
	vector<string> vkey;
	vector<string> okey;
};


int c2json::call(string &buf,int pos)
{

	string val;
	val = "";
	val.append("root->");
	for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
	{
		val.append(*vit);
		val.append(".");
	}

	//cout << buf << endl;
	int mn = buf.find_first_not_of("}]",0);


	int flg = mn;
	//cout << "call start:" << mn << endl;
	if(flg == -1)
		flg = buf.length();
	for(int i = 0; i < flg; ++i)
	{
		switch(buf[i])
		{
			case '}' :
			ofs << "writer.EndObject();" << endl;

			
			break;

			case ']' :
			if(!vkey.empty())
			{

				//cout << vkey.at(0) << endl;
				//cout << endl<< endl;
				vkey.pop_back();
			}
			val = "";
			val.append("root->");
			for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
			{
				val.append(*vit);
				val.append(".");
			}

			ofs << "}" << endl;
			ofs << "writer.EndArray();" << endl;
			break;
			default :
			break;
		}

	}

	if(mn == -1){
		
		buf = "    ";
		return 0;
		//sleep(1);
	};

	if(buf[mn] == ',')
		goto key;

	//buf = buf.substr(buf.find_first_of('{'),buf.length()-buf.find_first_of('{'));
	switch(buf[buf.find_first_of('{')])
	{
		case '{':
		{
			ofs << "writer.StartObject();" << endl;

key:

			int li,ri;
			li = buf.find_first_of("\"", 0);
			ri = buf.find_first_of("\"",li+1);
			okey.push_back(buf.substr(li+1,ri-li-1));
			ofs << "writer.Key(\"" << buf.substr(li+1,ri-li-1) << "\");" << endl;
			if( ':' != buf[ri+1])
			{
				cout << buf[ri+1] << endl;
				return 0;
			}
			switch(buf[ri+2])
			{
				case 0x30:
				case 0x31:
				case 0x32:
				case 0x33:
				case 0x34:
				case 0x35:
				case 0x36:
				case 0x37:
				case 0x38:
				case 0x39:
				ofs << "writer.Int(" << val << buf.substr(li+1,ri-li-1) << ");" << endl;
					goto write;
				case 't':  //true
				case 'f':  //false
				ofs << "writer.Bool(" << val << buf.substr(li+1,ri-li-1) << ");" << endl;
					goto write;
				case 'N':  //NULL
				case '\"': //NULL

				ofs << "writer.String(" << val << buf.substr(li+1,ri-li-1) << ".c_str());" << endl;
					goto write;
write:
				{
					int nide = buf.find_first_of(",}",ri+2);
					if(buf[nide] == '}')
					{
						ofs << "writer.EndObject();" << endl;
						okey.pop_back();
						buf = buf.substr(nide+1,buf.length()-nide-1);

						call(buf, 0);

						//cout << buf << endl;

					}
					else{
						buf = buf.substr(nide+1, buf.length()-nide-1);

						
						goto key;
					}
					break;
				}
				case '[':
				{
					string tmp = buf.substr(li+1,ri-li-1);
					
					vkey.push_back(tmp);
					val = "";
					val.append("root->");
					for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
					{
						val.append(*vit);
						val.append(".");
					}

					ofs << "writer.StartArray();" << endl;

					ofs << "for(int i_" << vkey.size() << " = 0; i_" << vkey.size() << " < " << val \ 
					<< "size(); ++i_" << vkey.size() <<" )" << endl;
					ofs << "{" << endl;
					if(!vkey.empty())
					vkey.pop_back();
					tmp.append(".at(i_");
					char tmpin[10];
					sprintf(tmpin, "%d",vkey.size()+1);
					tmp.append(tmpin);
					tmp.append(")");
					vkey.push_back(tmp);

					int nide = buf.find_first_of("{]",ri+2);
					if(buf[nide] == '{')
					{
						buf = buf.substr(nide, buf.length()-nide);
						call(buf, 0);

						//cout << "447 "  << buf << endl;

					}
					else if(buf[nide] == ']')
					{
						if(!vkey.empty())
						vkey.pop_back();
						val = "";
						val.append("root->");
						for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
						{
							val.append(*vit);
							val.append(".");
						}
						switch(buf[ri+3])
						{
							case 0x30:
							case 0x31:
							case 0x32:
							case 0x33:
							case 0x34:
							case 0x35:
							case 0x36:
							case 0x37:
							case 0x38:
							case 0x39:
							ofs << "writer.Int(" << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<"));" <<endl;
							goto sta;
							case 't':  //true
							case 'f':  //false
							ofs << "writer.Bool(" << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<"));" <<endl;
							goto sta;
							
							case 'N':  //NULL
							case '\"': //NULL
							case 'n':
							ofs << "writer.String(" << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<").c_str());" <<endl;
							goto sta;
sta:					
							ofs << "}" << endl;
							ofs << "writer.EndArray();" << endl;

							buf = buf.substr(nide+1, buf.length()-nide-1);
							call(buf, 0);

						}
						if(buf[nide+1] == ',')
						{
							buf = buf.substr(nide+1, buf.length()-nide-1);
							goto key;
						}
						
					}
					else{
						cout << "kong " << endl;
					}
					break;
				}
				case '{':
				{

					buf = buf.substr(ri+2, buf.length()-ri-2);

					call(buf, 0);

				}
				default :
				{

					break;
				}
			}
			break;
		}
	}
	return 0;
}

int c2json::init()
{
	std::ifstream in(jsonfile.c_str());
	if (!in.is_open()) {
		fprintf(stderr, "fail to read json file: %s\n", jsonfile.c_str());
		return -1;
	}
	string s;
	string buf;		
	while( in >> s ) 
	{    
		buf.append(s);
	}
	buf.insert(0,"\"R\":");
	in.close();
	//cout << buf << endl;
	buf = buf.substr(5,buf.length()-5);
	call(buf, 0);
	return 0;
}
int c2json::start(string filename)
{
	jsonfile = filename;
	if(jsonfile.find("_") == -1)
	{
		cout << "filename should is mod + \"_\" + structroot\n";
		cout << "example:\"smsf_UeSmsContextData\"\n";
		return 0;
	}
	stroot = jsonfile.substr(jsonfile.find("_")+1);
	string strname = filename;
	//strname.insert(0, "./data/");
	strname.append("_c2json.cpp");
	ofs.open(strname.c_str());
	
	ofs << "/*"<< endl;
	ofs << "Thank you use this simple tool"<< endl;
	ofs << "Portal: https://github.com/Still-her/autojson"<< endl;
	ofs << "This document may need to be modified as follows:"<< endl;
	ofs << "For example: root.arr1[m].arr2[n] missing object in the for loop"<< endl;
	ofs << "Correct: root.obj1.arr1[m].obj2.arr2[n]"<< endl;
	ofs << "There are unexpected bugs"<< endl;
	ofs << "Hey, just play"<< endl;
	ofs << "*/"<< endl;
	
	ofs << "#include <iostream>"<< endl;
	ofs << "#include <stdio.h>"<< endl;
	ofs << "#include <fstream>"<< endl;
	ofs << "#include \"rapidjson/document.h\""<< endl;
	ofs << "#include \"rapidjson/writer.h\""<< endl;
	ofs << "#include \"rapidjson/prettywriter.h\""<< endl;
	ofs << "#include \"rapidjson/stringbuffer.h\""<< endl;
	ofs << "#include \""<< filename << "_struct.h\""<< endl;
	ofs << "using namespace " << filename << ";" << endl;
	ofs << "string c2json(st" << stroot << " *root)"<< endl << "{" << endl;;
	ofs << "rapidjson::StringBuffer strBuf;"<< endl;
	ofs << "rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);"<< endl;
	init();
	ofs << "string data = strBuf.GetString();"<< endl;
	ofs << "return data;"<< endl;
	ofs << "}"<< endl;
	ofs.close();
}


class json2c
{
public:	
	
	int start(string filename);
	//s.open("test.cpp");
	int call(string &buf,int pos );
	int init();
	ofstream ofs;
	string jsonfile;
	string stroot;
	int arrcut = 0;
	vector<string> vkey;
};


int json2c::call(string &buf,int pos)
{

	string val;
	val = "";
	val.append("root->");
	for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
	{
		val.append(*vit);
		val.append(".");
	}

	//cout << "json2c::call:" << buf << endl;
	int mn = buf.find_first_not_of("}]",0);


	int flg = mn;
	//cout << "call start:" << mn << endl;
	if(flg == -1)
		flg = buf.length() - 1 ;
	for(int i = 0; i < flg; ++i)
	{
		//cout << "mnmnmn:::" << buf << endl;
		switch(buf[i])
		{

			case '}' :
			ofs << "}" << endl;
			if(!vkey.empty())
			{
				//cout << vkey.at(0) << endl;
				//cout << endl<< endl;
				vkey.pop_back();
			}
			//ofs << "writer.EndObject();" << endl;
			break;

			case ']' :
			arrcut--;
			if(!vkey.empty())
			{

				//cout << vkey.at(0) << endl;
				//cout << endl<< endl;
				//vkey.pop_back();
			}
			val = "";
			val.append("root->");
			for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
			{
				val.append(*vit);
				val.append(".");
			}

			ofs << "}" << endl;
			//ofs << "writer.EndArray();" << endl;
			break;
			default :
			break;
		}

	}

	if(mn == -1){
		
		buf = "stop";
		
		return 0;
		
	};

	if(buf[mn] == ',')
		goto key;

	//cout << "call"<< buf << endl;
	//buf = buf.substr(buf.find_first_of('{'),buf.length()-buf.find_first_of('{'));
	switch(buf[buf.find_first_of('{')])
	{
		case '{':
		{

key:
			

			//cout << "key:::" << buf << endl;
			char tmpin[10];
			sprintf(tmpin, "%d",vkey.size());
			int li,ri;
			li = buf.find_first_of("\"", 0);
			ri = buf.find_first_of("\"",li+1);

			//cout << buf.substr(li+1,ri-li-1) << endl;
			switch(buf[ri+2])
			{
				
				case 'N':  //NULL
				case '\"': //NULL
				{
					val = "";
					val.append("root->");
					for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
					{
						val.append(*vit);
						val.append(".");
					}
					
					ofs << "if(obj_" << tmpin << ".HasMember(\"" << buf.substr(li+1,ri-li-1) << "\") && \\" << endl;
					ofs << "obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].IsString())" << endl;
					ofs << "{" << endl;
					ofs << val << buf.substr(li+1,ri-li-1) << " = obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetString();"<< endl;
					ofs << "}" << endl;

					if( ':' != buf[ri+1])
					{
						//cout << buf[ri+1] << endl;
						return 0;
					}
					goto write;
				}
				case 0x30:
				case 0x31:
				case 0x32:
				case 0x33:
				case 0x34:
				case 0x35:
				case 0x36:
				case 0x37:
				case 0x38:
				case 0x39:
				{
					ofs << "if(obj_" << tmpin << ".HasMember(\"" << buf.substr(li+1,ri-li-1) << "\") && \\" << endl;
					ofs << "obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].IsInt())" << endl;
					ofs << "{" << endl;
					ofs << val << buf.substr(li+1,ri-li-1) << " = obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetInt();"<< endl;
					ofs << "}" << endl;

					if( ':' != buf[ri+1])
					{
						//cout << buf[ri+1] << endl;
						return 0;
					}
					goto write;
				}
				case 't':  //true
				case 'f':  //false
				{
					ofs << "if(obj_" << tmpin << ".HasMember(\"" << buf.substr(li+1,ri-li-1) << "\") && \\" << endl;
					ofs << "obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].IsBool())" << endl;
					ofs << "{" << endl;
					ofs << val << buf.substr(li+1,ri-li-1) << " = obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetBool();"<< endl;
					ofs << "}" << endl;

					if( ':' != buf[ri+1])
					{
						//cout << buf[ri+1] << endl;
						return 0;
					}
					goto write;
				}


write:

				{
					int nide = buf.find_first_of(",}",ri+2);
					if(buf[nide] == '}')
					{
						if(!vkey.empty())
						{

							//cout << vkey.at(0) << endl;
							//cout << endl<< endl;
							vkey.pop_back();
						}
						ofs << "}" << endl;

						buf = buf.substr(nide+1,buf.length()-nide-1);


						//cout << "---------------------" << buf << endl;
						call(buf, 0);

						//cout << buf << endl;

					}
					else{
						buf = buf.substr(nide+1, buf.length()-nide-1);

						
						goto key;
					}
					break;
				}
				case '[':
				{
					arrcut++;
					val = "";
					val.append("root->");
					for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
					{
						val.append(*vit);
						val.append(".");
					}
					ofs << "if(obj_" << tmpin << ".HasMember(\"" << buf.substr(li+1,ri-li-1) << "\") && \\" << endl;
					ofs << "obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].IsArray())" << endl;
					ofs << "{" << endl;
					ofs << "const rapidjson::Value& arr_" << arrcut <<" = obj_" << tmpin << "[\"";
					ofs << buf.substr(li+1,ri-li-1) << "\"];"<< endl;
					ofs << "int len = arr_" << arrcut << ".Size();"<< endl;
					ofs << val << buf.substr(li+1,ri-li-1) << ".resize(len);" << endl;
					ofs << "for(int i_" << arrcut << "= 0; i_" << arrcut << " << len; ++i_"<< arrcut << ")" << endl;
					ofs << "{" << endl;
					

					//ofs << "}" << endl;

			
					string tmp = buf.substr(li+1,ri-li-1);
					vkey.push_back(tmp);
					val = "";
					val.append("root->");
					for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
					{
						val.append(*vit);
						val.append(".");
					}

					if(!vkey.empty())
					vkey.pop_back();
					tmp.append(".at(i_");
					char tmpin[10];
					sprintf(tmpin, "%d",arrcut);
					tmp.append(tmpin);
					tmp.append(")");
					vkey.push_back(tmp);

					int nide = buf.find_first_of("{]",ri+2);
					if(buf[nide] == '{')
					{
						ofs << "const rapidjson::Value& obj_" << atoi(tmpin) << " = arr_" << arrcut <<"[i_" << arrcut << "];" << endl;
						buf = buf.substr(nide, buf.length()-nide);
						call(buf, 0);

						//cout << "447 "  << buf << endl;

					}
					else if(buf[nide] == ']')
					{
						arrcut--;
						if(!vkey.empty())
						vkey.pop_back();
						val = "";
						val.append("root->");
						for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
						{
							val.append(*vit);
							val.append(".");
						}
						switch(buf[ri+3])
						{
							ofs  << "//Add assignment operation by yourself" << endl;
							case 0x30:
							case 0x31:
							case 0x32:
							case 0x33:
							case 0x34:
							case 0x35:
							case 0x36:
							case 0x37:
							case 0x38:
							case 0x39:
							ofs  << "//Add assignment operation by yourself" << endl;
							ofs << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<"));" <<endl;
							goto sta;
							case 't':  //true
							case 'f':  //false
							ofs  << "//Add assignment operation by yourself" << endl;
							ofs  << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<"));" <<endl;
							goto sta;
							
							case 'N':  //NULL
							case '\"': //NULL
							case 'n': //NULL
							ofs  << "//Add assignment operation by yourself" << endl;
							ofs  << val << buf.substr(li+1,ri-li-1) << ".at(i_" << tmpin <<").c_str());" <<endl;
							goto sta;
	sta:					
							ofs << "}" << endl;
							ofs << "}" << endl;
							//ofs << "writer.EndArray();" << endl;

							buf = buf.substr(nide+1, buf.length()-nide-1);

							//cout << "dwfqwefreqf" << buf << endl << endl << endl;
							call(buf, 0);

						}
						if(buf[nide+1] == ',')
						{
							buf = buf.substr(nide+1, buf.length()-nide-1);
							goto key;
						}
						
					}
					else{
						cout << "kong " << endl;
					}
					break;
				}
				case '{':
				{
					

					if(buf[ri+3] == '}')
					{
						if(buf[ri+4] == ',')
						{
							buf = buf.substr(ri+5, buf.length()-ri-5);
							goto key;
						}
						else
						{
							buf = buf.substr(ri+4, buf.length()-ri-4);
							call(buf, 0);
						}
					}

					if(buf == "stop")
					{
						cout << "stop" << endl;
						return 0;
					}


					ofs << "if(obj_" << tmpin << ".HasMember(\"" << buf.substr(li+1,ri-li-1) << "\") && \\" << endl;
					ofs << "obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].IsObject())" << endl;
					ofs << "{" << endl;
					ofs << "const rapidjson::Value& ";
					ofs << "obj_" << atoi(tmpin) + 1 << " = obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"];" << endl;
					vkey.push_back(buf.substr(li+1,ri-li-1));
					//ofs << val << buf.substr(li+1,ri-li-1) << " = obj_" << tmpin << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetString();"<< endl;
					//ofs << "}" << endl;

					buf = buf.substr(ri+2, buf.length()-ri-2);

					call(buf, 0);

				}
				default :
				{

					break;
				}
			}
		}
		break;
	}
	return 0;
}

int json2c::init()
{
	std::ifstream in(jsonfile.c_str());
	if (!in.is_open()) {
		fprintf(stderr, "fail to read json file: %s\n", jsonfile.c_str());
		return -1;
	}
	string s;
	string buf;		
	while( in >> s ) 
	{    
		buf.append(s);
	}
	buf.insert(0,"\"R\":");
	in.close();
	//cout << buf << endl;
	buf = buf.substr(5,buf.length()-5);
	call(buf, 0);	
	return 0;
}

int json2c::start(string filename)
{
	jsonfile = filename;
	if(jsonfile.find("_") == -1)
	{
		cout << "filename should is mod + \"_\" + structroot\n";
		cout << "example:\"smsf_UeSmsContextData\"\n";
		return 0;
	}
	stroot = jsonfile.substr(jsonfile.find("_")+1);
	string strname = filename;
	//strname.insert(0, "./data/");
	strname.append("_json2c.cpp");
	ofs.open(strname.c_str());
	ofs << "/*"<< endl;
	ofs << "Thank you use this simple tool"<< endl;
	ofs << "Portal: https://github.com/Still-her/autojson"<< endl;
	ofs << "This document may need to be modified as follows:"<< endl;
	ofs << "For example: const rapidjson::Value& obj_x = arr_1[i_1];"<< endl;
	ofs << "x=? According to the next line obj_x to define "<< endl;
	ofs << "There are unexpected bugs"<< endl;
	ofs << "Hey, just play"<< endl;
	ofs << "*/"<< endl;
	ofs << "#include <iostream>"<< endl;
	ofs << "#include <stdio.h>"<< endl;
	ofs << "#include <fstream>"<< endl;
	ofs << "#include \"rapidjson/document.h\""<< endl;
	ofs << "#include \"rapidjson/writer.h\""<< endl;
	ofs << "#include \"rapidjson/prettywriter.h\""<< endl;
	ofs << "#include \"rapidjson/stringbuffer.h\""<< endl;
	ofs << "#include \""<< filename << "_struct.h\""<< endl;
	ofs << "using namespace " << filename << ";" << endl;
	ofs << "int json2c(string str, st" << stroot <<" *root)"<< endl << "{" << endl;
	ofs << "rapidjson::Document obj_0;"<< endl;
	ofs << "if (obj_0.Parse(str.c_str()).HasParseError())"<< endl << "{" << endl;
	ofs << "return 1;" << endl << "}" << endl;
	init();
	ofs << "return 0;" << endl;
	ofs << "}" << endl;
	ofs.close();
}

int main(int argc, char *argv[])
{
	string filename;
	if(argv[1] != NULL){
		filename = argv[1];
		cout << "filename:" << filename << endl;
	}
	else{
	cout << "input json filename" << endl;
	return 0;}
	//.h
	generate te1;
	te1.start(filename);
	//写.cpp -1

	c2json te2;
	te2.start(filename);

	json2c te3;
	te3.start(filename);
}
