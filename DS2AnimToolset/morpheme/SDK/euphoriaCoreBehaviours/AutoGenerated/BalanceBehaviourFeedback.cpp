/*
 * Copyright (c) 2013 NaturalMotion Ltd. All rights reserved.
 *
 * Not to be copied, adapted, modified, used, distributed, sold,
 * licensed or commercially exploited in any manner without the
 * written consent of NaturalMotion.
 *
 * All non public elements of this software are the confidential
 * information of NaturalMotion and may not be disclosed to any
 * person nor used for any purpose not expressly approved by
 * NaturalMotion in writing.
 *
 */

//----------------------------------------------------------------------------------------------------------------------
//                                  This file is auto-generated
//----------------------------------------------------------------------------------------------------------------------

// module def dependencies
#include "MyNetwork.h"
#include "BalanceBehaviourFeedback.h"
#include "BalanceBehaviourFeedbackPackaging.h"
#include "MyNetworkPackaging.h"

// misc
#include "euphoria/erEuphoriaLogger.h"
#include "euphoria/erDebugDraw.h"
#include "physics/mrPhysicsSerialisationBuffer.h"



namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

//----------------------------------------------------------------------------------------------------------------------
BalanceBehaviourFeedback::BalanceBehaviourFeedback(ER::ModuleDataAllocator* mdAllocator, ER::ModuleCon* connectionSet) : ER::Module(mdAllocator, connectionSet)
{
  feedOut = (BalanceBehaviourFeedbackFeedbackOutputs*)mdAllocator->alloc(ER::ModuleDataAllocator::FeedbackOutputs, sizeof(BalanceBehaviourFeedbackFeedbackOutputs), __alignof(BalanceBehaviourFeedbackFeedbackOutputs));

  m_apiBase = (BalanceBehaviourFeedbackAPIBase*)NMPMemoryAllocAligned(sizeof(BalanceBehaviourFeedbackAPIBase), 16);
}

//----------------------------------------------------------------------------------------------------------------------
BalanceBehaviourFeedback::~BalanceBehaviourFeedback()
{
  owner = 0;

  NMP::Memory::memFree(m_apiBase);
}

//----------------------------------------------------------------------------------------------------------------------
void BalanceBehaviourFeedback::create(ER::Module* parent, int childIndex)
{
  ER::Module::create(parent, childIndex);
  owner = (MyNetwork*)parent;
  if (getConnections())
    getConnections()->create(this, (ER::Module*)owner);


  new(m_apiBase) BalanceBehaviourFeedbackAPIBase( owner->m_apiBase);
}

//----------------------------------------------------------------------------------------------------------------------
void BalanceBehaviourFeedback::clearAllData()
{
  feedOut->clear();
}

//----------------------------------------------------------------------------------------------------------------------
bool BalanceBehaviourFeedback::storeState(MR::PhysicsSerialisationBuffer& savedState)
{
  savedState.addValue(*feedOut);
  storeStateChildren(savedState);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool BalanceBehaviourFeedback::restoreState(MR::PhysicsSerialisationBuffer& savedState)
{
  *feedOut = savedState.getValue<BalanceBehaviourFeedbackFeedbackOutputs>();
  restoreStateChildren(savedState);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
const char* BalanceBehaviourFeedback::getChildName(int32_t) const
{
  NMP_ASSERT_FAIL();
  return 0;
}


} // namespace NM_BEHAVIOUR_LIB_NAMESPACE


