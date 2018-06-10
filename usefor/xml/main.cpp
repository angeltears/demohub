#include <string>
#include <iostream>
#include <cassert>
#include "tinyxml2.h"
using namespace tinyxml2;
using std::cout;
using std::endl;
using std::string;
int main()
{
    XMLDocument* doc = new XMLDocument();  
    doc->LoadFile("config.xml");
    //获取根节点，即persons节点
    XMLElement* root = doc->RootElement();  
    XMLElement* person = root->FirstChildElement("Listen");
    while (person)  
    {  
         //获取person的name属性
         const XMLElement * nameAttr = person->FirstChildElement();
         assert(nameAttr != NULL);
         while(nameAttr)
         {     
            cout<<nameAttr->Name()<<":"<<nameAttr->GetText()<<endl; 
            nameAttr = nameAttr->NextSiblingElement();    
         }
         person =  person->NextSiblingElement();
    }  
    delete doc;
}


