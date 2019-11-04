#include<stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void writeTest(void)
{
/* Write Test start*/
    //Define document pointer
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
     
    //Define node pointer
    xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"root");

    //Set the root element of the document
    xmlDocSetRootElement(doc,root_node);

    xmlNewTextChild(root_node,NULL,BAD_CAST"newnode1",BAD_CAST"newnode1 content");
    xmlNewTextChild(root_node,NULL,BAD_CAST"newnode2",BAD_CAST"newnode2 content");

    xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"node2");

    xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");

    xmlAddChild(root_node,node);
    xmlAddChild(node,content);

    xmlNewProp(node,BAD_CAST"attribute",BAD_CAST"yes");

    node = xmlNewNode(NULL,BAD_CAST"son");
    xmlAddChild(root_node,node);
    xmlNodePtr grandson = xmlNewNode(NULL,BAD_CAST"grandson");
    xmlAddChild(node,grandson);
    xmlAddChild(grandson,xmlNewText(BAD_CAST"THis is a grandson node"));

    int nRel = xmlSaveFormatFile("libxml2-demo.xml", doc, 1);
    if(nRel != -1)
        printf("create xml %d byte!!\n",nRel);

    xmlFreeDoc(doc);
	
/* Write Test end*/	
	
}

static void parseTest(void)
{
	xmlKeepBlanksDefault (0); 
	xmlDocPtr doc = xmlParseFile("libxml2-demo.xml");
	if(doc == NULL)
	{
		printf("parse xml failed. \n");
		return;
	}
	
	xmlNodePtr curElement = xmlDocGetRootElement(doc);
	if(curElement == NULL)
	{
		printf("This xml file is empty. \n");
		return;
	}
	
	curElement = curElement->xmlChildrenNode;
	
	while(curElement != NULL) 
	{
		printf("curElement name:%s \n", curElement->name);
		
		xmlNodePtr curNode = curElement->xmlChildrenNode;
		while(curNode != NULL)
		{
			printf("	curNode name:%s, value:%s\n", curNode->name, xmlNodeGetContent(curNode));
			curNode = curNode->next;			
		}
		
		curElement = curElement->next;
	}
	
}

int main(int argc, char **argv)
{
	
	writeTest();

	parseTest();
	
    return 0;
}