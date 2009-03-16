/* bzflag
 * Copyright (c) 1993 - 2009 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named LICENSE that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* interface header */
#include "WorldEventManager.h"

/* system implementation headers */
#include <string>
#include <set>

/* common implementation headers */
#include "global.h"
#include "bzfsAPI.h"


extern bz_eTeamType convertTeam(TeamColor team);
extern TeamColor convertTeam(bz_eTeamType team);

//-------------------WorldEventManager--------------------
WorldEventManager::WorldEventManager()
{
}

WorldEventManager::~WorldEventManager()
{
  typedef std::set<bz_EventHandler*> EventHandlerSet;
  EventHandlerSet toDelete;

  tmEventTypeList::iterator eventItr = eventList.begin();
  while (eventItr != eventList.end())
  {
    tvEventList::iterator itr = eventItr->second.begin();
    while (itr != eventItr->second.end())
    {
      if ((*itr) && (*itr)->autoDelete())
	toDelete.insert(*itr);
      *itr = NULL;

      itr++;
    }
    eventItr++;
  }

  // Because an event handler can be registerd to handle multiple
  // events, collect all the registered handlers in a set and delete
  // each one exactly once.
  for (EventHandlerSet::iterator die = toDelete.begin(); die != toDelete.end(); ++die) {
    delete *die;
  }
}

void WorldEventManager::addEvent(bz_eEventType eventType, bz_EventHandler* theEvent)
{
  if (!theEvent)
    return;

  if (eventList.find(eventType) == eventList.end()) {
    tvEventList newList;
    eventList[eventType] = newList;
  }

  eventList.find(eventType)->second.push_back(theEvent);
}

void WorldEventManager::removeEvent(bz_eEventType eventType, bz_EventHandler* theEvent)
{
  if (!theEvent)
    return;

  tmEventTypeList::iterator eventTypeItr = eventList.find(eventType);
  if (eventTypeItr == eventList.end())
    return;

  tvEventList::iterator itr = eventTypeItr->second.begin();
  while (itr != eventTypeItr->second.end()) {
    if (*itr == theEvent)
      itr = eventTypeItr->second.erase(itr);
    else
      itr++;
  }
}

tvEventList WorldEventManager::getEventList (bz_eEventType eventType)
{
  tvEventList	eList;

  tmEventTypeList::iterator itr = eventList.find(eventType);
  if (itr == eventList.end())
    return eList;

  eList = itr->second;
  return eList;
}

void WorldEventManager::callEvents(bz_eEventType eventType, bz_EventData *eventData)
{
  if (!eventData)
    return;

  eventData->eventType = eventType;
  tvEventList	eList = getEventList(eventType);

  for (unsigned int i = 0; i < eList.size(); i++)
    eList[i]->process(eventData);
}

int WorldEventManager::getEventCount(bz_eEventType eventType)
{
  return (int)getEventList(eventType).size();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
