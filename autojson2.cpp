
/***************************************
Author:lixingbo
data:2020 07 23


  
若需要用此APP生成结构体及基于repadjson的解析cpp文件
必须遵循以上要求

当json格式与上冲突时,可以修改json模板数据格式，满足以上要求
然后再生成的文件里面稍作修改亦可达到想要的目标文件。


****************************************/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
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
	ofs << "#ifndef "<< filename <<"_DEFINE_H_"<< endl;
	ofs << "#define "<< filename <<"_DEFINE_H_"<< endl;
	ofs << "#include <string>"<< endl;
	ofs << "#include <vector>"<< endl;
	ofs << "using namespace std;"<< endl;
	ofs << "namespace " << filename << "{" << endl;
	group_map();
	demapkey("}");
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

			cout << "generate::group_map " << buf << endl;

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
};


int c2json::call(string &buf,int pos)
{
	#if 0
	string val("root");
	for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
	{
		val.append(".");
		val.append(*vit);
	}
	#endif

	//cout << buf << endl;
	int mn = buf.find_first_not_of("}]",0);
	cout << "call start:" << mn << endl;
	for(int i = 0; i < mn; ++i)
	{
		switch(buf[i])
		{
			case '}' :
			ofs << "writer.EndObject();" << endl;
			break;

			case ']' :
			ofs << "}" << endl;
			ofs << "writer.EndArray();" << endl;
			break;
			default :
			break;
		}

	}

	if(buf[mn] == ',')
		goto key;

	//buf = buf.substr(buf.find_first_of('{'),buf.length()-buf.find_first_of('{'));
	switch(buf[buf.find_first_of('{')])
	{
		#if 0
		//case '[':
		case '???':
		{
			if(buf[pos+1] == '{')
			{
				int nide = val.find_last_of(".at");
				int lide = val.find_last_of(")",nide);
				string tmp = val;
				string dstr= tmp.erase(nide-2,lide-nide);
				ofs << "writer.StartArray();" << endl;
				ofs << "for(int i_" << arrcut << " = 0; i_" << arrcut << " < " << dstr << ".size(); ++i_" << arrcut <<" )" << endl;
				ofs << "{" << endl;
				ofs << "writer.StartObject();" << endl;
			}
			break;
		}
		#endif
		case '{':
		{
			ofs << "writer.StartObject();" << endl;

key:
			cout << "key :"  << buf << endl;
			cout  << endl;
			cout  << endl;
			cout  << endl;
			int li,ri;
			li = buf.find_first_of("\"",pos);
			ri = buf.find_first_of("\"",li+1);
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
				case 't':  //true
				case 'f':  //false
				case 'N':  //NULL
				case '\"': //NULL
				{

					ofs << "writer.String(" << buf.substr(li+1,ri-li-1) << ".c_str());" << endl;
					int nide = buf.find_first_of(",}",ri+2);
					if(buf[nide] == '}')
					{
						ofs << "writer.EndObject();" << endl;

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
					ofs << "writer.StartArray();" << endl;
					ofs << "for(int i_1 = 0; i_1 < root.backupAmfInfo.size(); ++i_1 ){" << endl;

					int nide = buf.find_first_of("{]",ri+2);
					if(buf[nide] == '{')
					{
						buf = buf.substr(nide, buf.length()-nide);
						call(buf, 0);

						//cout << "447 "  << buf << endl;

					}
					else if(buf[nide] == ']')
					{
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
							case 't':  //true
							case 'f':  //false
							case 'N':  //NULL
							case '\"': //NULL

							ofs << "writer.String" << endl;
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

					//cout << buf << endl;

					//cout << buf << endl;
					call(buf, 0);

					//cout << "call : " << buf << endl;
				}
				default :
				{

					//cout << "json err" << endl;
					break;
				}
			}
			break;
		}
	}
	#if 0
	int li,ri;
	
	li = buf.find_first_of("\"",pos);
	ri = buf.find_first_of("\"",li+1);
	if(li != -1)
	{
		ofs << "writer.Key(\"" << buf.substr(li+1,ri-li-1) << "\");" << endl;;
		int mo = buf.find_first_of(":",ri+1);
		if(mo == -1)
		{
			return 0;
		}
		int control = 0;
		switch(buf[mo+1])
		{
			case '"':
			{
				control = 1;
				ofs << "writer.String(" << val << "." << buf.substr(li+1,ri-li-1) << ".c_str());" << endl;
				break;
			}
			case 't':
			case 'f':
			{
				control = 1;
				ofs << "writer.Bool(" << val << "." << buf.substr(li+1,ri-li-1) << ");" << endl;
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
				control = 1;
				ofs << "writer.Int(" << val << "." << buf.substr(li+1,ri-li-1) << ");" << endl;
				break;
			}
			case '[':
			{
				if(buf[mo+2] == '{')
				{
					arrcut++;
					char tmp_[64];
					sprintf(tmp_,"%s.at(i_%d)",buf.substr(li+1,ri-li-1).c_str(),arrcut);
					//string tmp(buf.substr(li+1,ri-li-1));
					//tmp.append(tmp_);
					vkey.push_back(tmp_);
					call(buf, mo+1);
				}
				else
				{
					arrcut++;
					string tmp(buf.substr(li+1,ri-li-1));
					control = 1;
					ofs << "writer.StartArray();" << endl;
					ofs << "for(int i_" << arrcut << " = 0; i_" << arrcut << " < " << val << "." << tmp << ".size(); ++i_" << arrcut <<" )" << endl;
					ofs << "{" << endl << "}" << endl;
					ofs << "writer.EndArray();" << endl;
					arrcut--;
				}
				break;
			}
			case '{':
			{
				vkey.push_back(buf.substr(li+1,ri-li-1));
				call(buf, mo+1);
				break;
			}
		}
		
		if(control == 1)
		{
			int di = buf.find_first_of(",",mo+1);
			if(di != -1)
			{
				switch(buf[di-1])
				{
					case '}':
					{
						string stmp = buf.substr(mo+1,di-mo-1);
						int it = 0 ;
						int cou = 0;
						while(it != -1)
						{
							it = stmp.find_first_of("}",it+1);
							cou ++;
						}
						for(int i = 0; i < cou-1; i++)
						{
							ofs << "writer.EndObject();" << endl;
							vkey.pop_back();
						}
						break;
					}
					case ']':
					{
						if(buf[di-2] == '}')
						{

							string stmp = buf.substr(mo+1,di-mo-1);
							int it = 0 ;
							int cou = 0;
							while(it != -1)
							{
								it = stmp.find("}]",it+1);
								cou ++;
							}
							for(int i = 0; i < (cou-1); i++)
							{
								ofs << "writer.EndObject();" << endl;
								ofs << "}" << endl;
								ofs << "writer.EndArray();" << endl;
								vkey.pop_back();
								arrcut--;
							}
							
						}
						break;
					}
				}
				call(buf, di+1);
			}
		}
	}
	#endif
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
	in.close();
	//cout << buf << endl;
	call(buf, 0);
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
	ofs << "#include <iostream>"<< endl;
	ofs << "#include <stdio.h>"<< endl;
	ofs << "#include <fstream>"<< endl;
	ofs << "#include \"rapidjson/document.h\""<< endl;
	ofs << "#include \"rapidjson/writer.h\""<< endl;
	ofs << "#include \"rapidjson/prettywriter.h\""<< endl;
	ofs << "#include \"rapidjson/stringbuffer.h\""<< endl;
	ofs << "#include \""<< filename << "_struct.h\""<< endl;
	ofs << "using namespace " << filename << ";" << endl;
	ofs << "string c2json(st" << stroot << " root)"<< endl << "{" << endl;;
	ofs << "rapidjson::StringBuffer strBuf;"<< endl;
	ofs << "rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);"<< endl;
	init();
	//ofs << "writer.EndObject();"<< endl;
	ofs << "string data = strBuf.GetString();"<< endl;
	ofs << "return data;"<< endl;
	ofs << "}"<< endl;
	ofs.close();
}




class json2c
{
public:	
	
	int start(string filename);

	int call(string buf,int pos);
	int init();

	string jsonfile;
	ofstream ofs;
	vector<string> vkey;
	
	typedef struct aktm
	{
		int op;
		string val;
	}staktm;
	vector<staktm> vecktm;
	struct obj
	{
		int num = 0;
		string objval;
	}stobj;
	
	struct arr
	{
		int num = 0;
		string arrval;
	}starr;
	string stroot;
};


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
	strname.insert(0, "./data/");
	strname.append("_json2c.cpp");
	ofs.open(strname.c_str());
	
	ofs << "#include <iostream>"<< endl;
	ofs << "#include <stdio.h>"<< endl;
	ofs << "#include <fstream>"<< endl;
	ofs << "#include \"rapidjson/document.h\""<< endl;
	ofs << "#include \"rapidjson/writer.h\""<< endl;
	ofs << "#include \"rapidjson/prettywriter.h\""<< endl;
	ofs << "#include \"rapidjson/stringbuffer.h\""<< endl;
	ofs << "#include \""<< filename << "_struct.h\""<< endl;
	ofs << "using namespace " << filename << ";" << endl;
	ofs << "int json2c(string str, st" << stroot <<" &root)"<< endl << "{" << endl;;
	ofs << "rapidjson::Document obj_0;"<< endl;
	ofs << "if (obj_0.Parse(str.c_str()).HasParseError())"<< endl << "{" << endl;
	ofs << "return 1;" << endl << "}" << endl;
	init();
	ofs << "return 0;" << endl;
	ofs << "}" << endl;
	ofs.close();
}



int json2c::call(string buf,int pos)
{
	char num[4];
	sprintf(num,"%d",stobj.num);
	stobj.objval = "obj_";
	stobj.objval.append(num);
	string val("root");
	for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
	{
		val.append(".");
		val.append(*vit);
	}
	
	int li = buf.find_first_of("\"",pos);
	int ri = buf.find_first_of("\"",li+1);
	ofs << "if(" << stobj.objval << ".HasMember(\"" << buf.substr(li+1,ri-li-1)<< "\") && " ;
	ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1);

	int mo = buf.find_first_of(":",ri+1);
	if(mo == -1)
	{
		return 0;
	}
	int control = 0;
	switch(buf[mo+1])
	{
		case '"':
		{
			control = 1;
			ofs << "\"].IsString())"<<endl << "{" << endl;
			if(vecktm.size() > 0)
			{
				ofs << "" << (vecktm.end()-1)->val << ".";

				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			else
			{
				ofs << "" << val << ".";
				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetString();\n}\n";
			break;
		}
		case 't':
		case 'f':
		{
			control = 1;
			ofs << "\"].IsBool())"<<endl << "{" << endl;
			if(vecktm.size() > 0)
			{
				ofs << "" << (vecktm.end()-1)->val << ".";

				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			else
			{
				ofs << "" << val << ".";
				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetBool();\n}\n";
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
			control = 1;
			ofs << "\"].IsInt())"<<endl << "{" << endl;
			if(vecktm.size() > 0)
			{
				ofs << "" << (vecktm.end()-1)->val << ".";

				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			else
			{
				ofs << "" << val << ".";
				ofs << buf.substr(li+1,ri-li-1) << " = ";
			}
			ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1) << "\"].GetInt();\n}\n";
			break;
		}
		case '[':
		{
			if(buf[mo+2] == '{')
			{
				staktm tmp;
				tmp.op = 1;
				tmp.val = "tmp";
				tmp.val.append(buf.substr(li+1,ri-li-1));
				vecktm.push_back(tmp);
				
				char num[4];
				starr.num ++;
				sprintf(num,"%d",starr.num);
				string tmpa = starr.arrval;
				starr.arrval = "arr_";
				starr.arrval.append(num);

				char bl[64];
				sprintf(bl, "for(int i_%d = 0; i_%d < len; i_%d++)",vecktm.size(),vecktm.size(),vecktm.size());
				
				
				ofs << "\"].IsArray())"<<endl << "{" << endl;
				ofs << "const rapidjson::Value& " << starr.arrval << " = ";
				ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1) << "\"];" << endl;
				ofs << "int len = " << starr.arrval<< ".Size();" << endl << bl <<" \n{\n";
				
				char num1[4];
				stobj.num ++;
				sprintf(num1,"%d",stobj.num);
				string tmpo = stobj.objval;
				stobj.objval = "obj_";
				stobj.objval.append(num1);
				
				ofs << "st" << buf.substr(li+1,ri-li-1) << " tmp"   << buf.substr(li+1,ri-li-1) << ";\n" ;
				ofs << "const rapidjson::Value& "<< stobj.objval << " = " << starr.arrval <<"[i_"<<vecktm.size() <<"];" << endl;
				ofs << "if(" << stobj.objval << ".IsObject())" << endl << "{" << endl;
				vkey.push_back(buf.substr(li+1,ri-li-1));
				call(buf, mo+1);
			}
			else
			{
				control = 1;
				ofs << "\"].IsArray())"<<endl << "{" << endl;
				char num[4];
				starr.num ++;
				sprintf(num,"%d",starr.num);
				string tmpa = starr.arrval;
				starr.arrval = "arr_";
				starr.arrval.append(num);
				char bl[64];
				sprintf(bl, "for(int i_%d = 0; i_%d < len; i_%d++)",vecktm.size(),vecktm.size(),vecktm.size());
				ofs << "const rapidjson::Value& " << starr.arrval << " = ";
				ofs << stobj.objval << "[\"" << buf.substr(li+1,ri-li-1) << "\"];" << endl;
				ofs << "int len = " << starr.arrval<< ".Size();" << endl << bl <<" \n{\n" <<endl;
				ofs << "}" << endl << "}" <<endl;
				starr.num --;
			}
			break;
		}
		case '{':
		{
			char num[4];
			stobj.num ++;
			sprintf(num,"%d",stobj.num);
			string tmpo = stobj.objval;
			stobj.objval = "obj_";
			stobj.objval.append(num);
			
			ofs << "\"].IsObject())"<<endl << "{" << endl;
			ofs << "const rapidjson::Value& " << stobj.objval << " = " <<  tmpo;
			ofs << "[\"" << buf.substr(li+1,ri-li-1) << "\"];" << endl;
			
			if(vecktm.size() > 0)
			{
				(vecktm.end()-1)->val.append(".");
				(vecktm.end()-1)->val.append(buf.substr(li+1,ri-li-1));
			}
			vkey.push_back(buf.substr(li+1,ri-li-1));
			call( buf,mo+1);
			break;
		}
	}
	
	if(control == 1)
	{
		int di = buf.find_first_of(",",mo+1);
		if(di != -1)
		{
			switch(buf[di-1])
			{
				case '}':
				{
					string stmp = buf.substr(mo+1,di-mo-1);
					int it = 0 ;
					int cou = 0;
					while(it != -1)
					{
						it = stmp.find_first_of("}",it+1);
						cou ++;
					}
					for(int i = 0; i < cou-1; i++)
					{
						vkey.pop_back();
						
						stobj.num --;
						
					
						
						ofs << "}" <<endl;
					}
					if(vecktm.size() > 0)
					{
						(vecktm.end()-1)->val.erase((vecktm.end()-1)->val.find("."));
					}
					
					break;
				}
				case ']':
				{
					if(buf[di-2] == '}')
					{
						string stmp = buf.substr(mo+1,di-mo-1);
						int it = 0 ;
						int cou = 0;
						while(it != -1)
						{
							it = stmp.find("}]",it+1);
							cou ++;
						}
						for(int i = 0; i < (cou-1); i++)
						{
							string val("root");
							for(vector<string>::iterator vit = vkey.begin(); vit != vkey.end(); vit++)
							{
								val.append(".");
								val.append(*vit);
							}
							vkey.pop_back();
							stobj.num --;
							starr.num --;
							string tmp;
							
							if(vecktm.size()>=2)
							{
								tmp = (vecktm.end()-2)->val;
								tmp.append(".");
								string tmp_ = (vecktm.end()-1)->val;
								tmp_ = tmp_.substr(3,tmp_.length()-3);
								tmp.append(tmp_);
							}
							else
							{
								tmp = val;
							}
							ofs << "}" << endl ;
							ofs << "" << tmp << ".push_back(";
							ofs << (vecktm.end()-1)->val << ");" << endl;
							ofs << "}" << endl ;
							ofs << "}" << endl ;
							vecktm.pop_back();
						}
					}
					else{
						starr.num --;
					}
					break;
				}
			}
			call(buf, di+1);
		}
	}
}


int	json2c::init()
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
	in.close();
	//cout << buf << endl;
	
	call(buf, 0);	
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
	//te1.start(filename);
	//写.cpp -1

	c2json te2;
	te2.start(filename);

	json2c te3;
	//te3.start(filename);
}
