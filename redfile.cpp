#include<iostream>
#include<string.h>
#include<podofo/podofo.h>


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

//g++ readfile.cpp -lpodofo -lpthread -lfreetype -lfontconfig -ljpeg -lz -lcrypto
#define YEAR "te"
using namespace std;
int main()
{
	PoDoFo::PdfMemDocument pdf(YEAR".pdf");
	cout<<"pg count ="<<pdf.GetPageCount()<<endl;
	char ch[20];
	string s;
	int tm=0,dno,line_no,len;
	mongocxx::instance inst{};
    	mongocxx::client conn{mongocxx::uri{}};
	auto collection = conn["prac7"]["tablesss"];
	for (int pn = 0; pn < pdf.GetPageCount(); ++pn) {
		dno=0;
		line_no=1;
		tm=0;
		
    		bsoncxx::builder::stream::document *document;
    		PoDoFo::PdfPage* page = pdf.GetPage(pn);
		PoDoFo::PdfContentsTokenizer tok(page);
    		const char* token = nullptr;
		PoDoFo::PdfVariant var;
		PoDoFo::EPdfContentsType type;
		while (tok.ReadNext(type, token, var)) {
		        switch (type) {
		            case PoDoFo::ePdfContentsType_Keyword:
		                break;
		            case PoDoFo::ePdfContentsType_Variant:
				if(var.IsHexString()||var.IsString()){
					s=((var.GetString()).GetString());
					if(s[0]!=' '){
						if(tm!=0)
						{
							tm--;
							if(tm==1){
							int i=52;
							string seatno,name,mname,prn;
							seatno=s.substr(0,10);
							name=s.substr(12,40);
							len=s.length();
							while(!isdigit(s[i])&&i<len){i++;}
							mname=s.substr(52,i-52);
							while(isdigit(s[i])&&i<len){prn+=s[i];i++;}
							prn+=s[i];
							cout<<"\033[1;4;31m"<<"stno :"<<seatno;
							*document<<"seatno"<<seatno;
							cout<<"\033[1;4;31m"<<"name :"<<name;
							*document<<"name"<<name;
							cout<<"\033[1;4;31m"<<"mname :"<<mname;
							*document<<"mname"<<mname;
							cout<<"\033[1;4;31m"<<"prn :"<<prn<<endl;
							*document<<"prn"<<prn;
							}
							else{
							int i=0;
							while(s[i]!=':'){i++;}i++;
							while(s[i]!=':'){i++;}i++;
							stringstream hasnum(s.substr(i,3)); 
							int x = 0; 
							hasnum >> x; 
							*document<<"year"<<YEAR;
							*document<<"grade"<<x;
							collection.insert_one(document->view());
							cout<<"\033[1;4;32m"<<"grade :"<<x<<endl;
							}
						}
						if(s[0]=='.'){
							document=new bsoncxx::builder::stream::document;
							tm=2;
							dno++;
							if(dno==3)
							goto out1;
						}
						line_no++;
					}
				}
		                break;
		            default:
		                break;
		        }
			out1 :{}
		}
	}
}
                
