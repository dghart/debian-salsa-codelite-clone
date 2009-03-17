//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : xmlutils.cpp              
//                                                                          
// -------------------------------------------------------------------------
// A                                                                        
//              _____           _      _     _ _                            
//             /  __ \         | |    | |   (_) |                           
//             | /  \/ ___   __| | ___| |    _| |_ ___                      
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )                     
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/                     
//              \____/\___/ \__,_|\___\_____/_|\__\___|                     
//                                                                          
//                                                  F i l e                 
//                                                                          
//    This program is free software; you can redistribute it and/or modify  
//    it under the terms of the GNU General Public License as published by  
//    the Free Software Foundation; either version 2 of the License, or     
//    (at your option) any later version.                                   
//                                                                          
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
 #include "xmlutils.h"

wxXmlNode *XmlUtils::FindNodeByName(const wxXmlNode *parent, const wxString &tagName, const wxString &name)
{
	if(!parent){
		return NULL;
	}

	wxXmlNode *child = parent->GetChildren();
	while( child ){
		if( child->GetName() == tagName){
			if( child->GetPropVal(wxT("Name"), wxEmptyString) == name){
				return child;
			}
		}
		child = child->GetNext();
	}
	return NULL;
}

wxXmlNode *XmlUtils::FindFirstByTagName(const wxXmlNode *parent, const wxString &tagName)
{
	if( !parent ){
		return NULL;
	}

	wxXmlNode *child = parent->GetChildren();
	while( child ){
		if( child->GetName() == tagName){
			return child;
		}
		child = child->GetNext();
	}
	return NULL;
}

wxXmlNode *XmlUtils::FindLastByTagName(const wxXmlNode *parent, const wxString &tagName)
{
	wxXmlNode *last_node = NULL;
	wxXmlNode *child = parent->GetChildren();
	while( child ){
		if( child->GetName() == tagName){
			last_node = child;
		}
		child = child->GetNext();
	}
	return last_node;
}

void XmlUtils::UpdateProperty(wxXmlNode *node, const wxString &name, const wxString &value)
{
	wxXmlProperty *prop = node->GetProperties();
	while (prop){
		if( prop->GetName() == name ){
			prop->SetValue(value);
			return;
		}
		prop = prop->GetNext();
	}

	// No such property, create new one and add it
	node->AddProperty(name, value);
}

wxString XmlUtils::ReadString(wxXmlNode *node, const wxString &propName, const wxString &defaultValue)
{
	return node->GetPropVal(propName, defaultValue);
}

long XmlUtils::ReadLong(wxXmlNode *node, const wxString &propName, long defaultValue)
{
	wxString val = node->GetPropVal(propName, wxEmptyString);
	if( val.IsEmpty() ){
		return defaultValue;
	}

	if(val.StartsWith(wxT("\""))){
		val = val.AfterFirst(wxT('"'));
	}
	if(val.EndsWith(wxT("\""))){
		val = val.BeforeLast(wxT('"'));
	}
	long retVal = defaultValue;
	val.ToLong(&retVal);
	return retVal;
}

bool XmlUtils::ReadBool(wxXmlNode *node, const wxString &propName, bool defaultValue)
{
	wxString val = node->GetPropVal(propName, wxEmptyString);
	if( val.IsEmpty() ){
		return defaultValue;
	}

	if(val.IsEmpty()){
		return defaultValue;
	}

	bool retVal = defaultValue;
	if(val.CmpNoCase(wxT("yes")) == 0){
		retVal = true;
	} else {
		retVal = false;
	}
	return retVal;
}

void XmlUtils::SetNodeContent(wxXmlNode *node, const wxString &text)
{
	wxXmlNode *n = node->GetChildren();
	wxXmlNode *contentNode = NULL;
    while (n)
    {
		if (n->GetType() == wxXML_TEXT_NODE || n->GetType() == wxXML_CDATA_SECTION_NODE){
			contentNode = n;
			break;
		}
        n = n->GetNext();
    }

	if(contentNode) {
		// remove old node
		node->RemoveChild(contentNode);
		delete contentNode;
	}
	
	contentNode = new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, text);
	node->AddChild( contentNode );
}

void XmlUtils::RemoveChildren(wxXmlNode *node)
{
	wxXmlNode *child = node->GetChildren();
	while(child){
		wxXmlNode *nextChild = child->GetNext();
		node->RemoveChild(child);
		delete child;
		child = nextChild;
	}
}
