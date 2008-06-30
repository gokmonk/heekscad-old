// RemoveOrAddTool.cpp

#include "stdafx.h"

#include "RemoveOrAddTool.h"
#include "../interface/HeeksObj.h"
#include "MarkedList.h"

RemoveOrAddTool::RemoveOrAddTool(HeeksObj *object, HeeksObj *owner, HeeksObj *prev_object) : m_belongs_to_owner(false)
{
	m_object = object;
	m_owner = owner;
	m_prev_object = prev_object;
}

RemoveOrAddTool::~RemoveOrAddTool()
{
	if(m_owner == NULL)return;
	if(!m_belongs_to_owner)delete m_object;
}

static std::string string_for_GetTitle;

const char* AddObjectTool::GetTitle()
{
	string_for_GetTitle.assign("Add ");
	string_for_GetTitle.append(m_object->GetShortStringOrTypeString());
	return string_for_GetTitle.c_str();
}

void RemoveOrAddTool::Add()
{

	if (wxGetApp().m_doing_rollback && (m_owner == NULL))
	{
		m_owner = NULL;
	}

	if (m_owner == NULL)
	{
		wxMessageBox("*Can't Have NULL owner!");
		return;
	}

	m_owner->Add(m_object, m_prev_object);
	m_object->m_owner = m_owner;

	wxGetApp().WasAdded(m_object);
	wxGetApp().WasModified(m_owner);

	m_belongs_to_owner = true;
}

void RemoveOrAddTool::Remove()
{
	if (m_object->m_owner)
	{
		m_owner = m_object->m_owner;
		m_object->m_owner->Remove(m_object);
		wxGetApp().m_marked_list->Remove(m_object);
		wxGetApp().WasRemoved(m_object);
		wxGetApp().WasModified(m_owner);
		m_object->m_owner = NULL;
	}
	m_belongs_to_owner = false;
}

void AddObjectTool::Run()
{
	Add();
}

void AddObjectTool::RollBack()
{
	Remove();
}

RemoveObjectTool::RemoveObjectTool(HeeksObj *object):RemoveOrAddTool(object, NULL, NULL)
{
	m_owner = object->m_owner;
}

void RemoveObjectTool::Run()
{
	Remove();
}

void RemoveObjectTool::RollBack()
{
	Add();
}


ManyRemoveOrAddTool::~ManyRemoveOrAddTool()
{
	if(!m_belongs_to_owner){
		std::list<HeeksObj*>::iterator It;
		for(It = m_objects.begin(); It != m_objects.end(); It++){
			HeeksObj* object = *It;
            delete object;
		}
	}
}

void ManyRemoveOrAddTool::Add()
{
	if (m_owner == NULL)
	{
		wxMessageBox("*Can't have NULL owner!");
		return;
	}

	std::list<HeeksObj*>::iterator It;
	for(It = m_objects.begin(); It != m_objects.end(); It++){
		HeeksObj* object = *It;
		m_owner->Add(object, NULL);
		object->m_owner = m_owner;
	}

	wxGetApp().WereAdded(m_objects);
	wxGetApp().WasModified(m_owner);

	m_belongs_to_owner = true;
}

void ManyRemoveOrAddTool::Remove()
{
	std::list<HeeksObj*>::iterator It;
	for(It = m_objects.begin(); It != m_objects.end(); It++){
		HeeksObj* object = *It;
		m_owner->Remove(object);
		wxGetApp().m_marked_list->Remove(object);
	}

	wxGetApp().WereRemoved(m_objects);
	wxGetApp().WasModified(m_owner);
	for(It = m_objects.begin(); It != m_objects.end(); It++){
		HeeksObj* object = *It;
		object->m_owner = NULL;
	}

	m_belongs_to_owner = false;
}

const char* AddObjectsTool::GetTitle()
{
	return "Add Objects";
}

void AddObjectsTool::Run()
{
	Add();
}

void AddObjectsTool::RollBack()
{
	Remove();
}

const char* RemoveObjectsTool::GetTitle()
{
	return "Remove Objects";
}

void RemoveObjectsTool::Run()
{
	Remove();
}

void RemoveObjectsTool::RollBack()
{
	Add();
}