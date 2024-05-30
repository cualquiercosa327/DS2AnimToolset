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
#include "Arm.h"
#include "ArmReachReaction.h"
#include "ArmReachReactionPackaging.h"
#include "MyNetwork.h"
#include "ArmReachForBodyPart.h"
#include "BodyFrame.h"
#include "ReachForBody.h"
#include "ReachForBodyBehaviourInterface.h"
#include "ArmPackaging.h"
#include "MyNetworkPackaging.h"

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

//----------------------------------------------------------------------------------------------------------------------
void ArmReachReaction_Con::create(ER::Module* module, ER::Module* NMP_UNUSED(owner))
{
  buildConnections((ArmReachReaction*)module);
}

//----------------------------------------------------------------------------------------------------------------------
ArmReachReaction_Con::~ArmReachReaction_Con()
{
  junc_in_armHitPoseEndRelRoot->destroy();
  junc_in_avgReachingHandPos->destroy();
  junc_in_supportAmount->destroy();
  junc_in_currentReachTargets_1->destroy();
  junc_in_currentReachTargets_0->destroy();
}

//----------------------------------------------------------------------------------------------------------------------
NMP::Memory::Format ArmReachReaction_Con::getMemoryRequirements()
{
  NMP::Memory::Format result(sizeof(ArmReachReaction_Con), 16);

  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  return result;
}
//----------------------------------------------------------------------------------------------------------------------
void ArmReachReaction_Con::buildConnections(ArmReachReaction* module)
{
  // Reconstruct the previously-allocated resource to fill in the junctions
  NMP::Memory::Format format = getMemoryRequirements();
  NMP::Memory::Resource resource = {this, format};
  NMP::Memory::Format classFormat(sizeof(ArmReachReaction_Con), 16);
  resource.increment(classFormat);

  ER::Junction* activeJnc = 0;

  // build and connect up all junctions
  junc_in_currentReachTargets_0 = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->arms[0]->reachForBodyPart->feedOut->getCurrentReachTarget()), (float*)&(module->owner->owner->arms[0]->reachForBodyPart->feedOut->getCurrentReachTargetImportanceRef()) );
  junc_in_currentReachTargets_1 = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->arms[1]->reachForBodyPart->feedOut->getCurrentReachTarget()), (float*)&(module->owner->owner->arms[1]->reachForBodyPart->feedOut->getCurrentReachTargetImportanceRef()) );

  junc_in_supportAmount = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->feedOut->getSupportAmount()), (float*)&(module->owner->owner->bodyFrame->feedOut->getSupportAmountImportanceRef()) );

  junc_in_avgReachingHandPos = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->reachForBody->out->getErrorWeightedAverageEffectorPosition()), (float*)&(module->owner->owner->bodyFrame->reachForBody->out->getErrorWeightedAverageEffectorPositionImportanceRef()) );

  junc_in_armHitPoseEndRelRoot = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->reachForBodyBehaviourInterface->out->getArmHitPoseEndRelRoot(module->owner->getChildIndex())), (float*)&(module->owner->owner->reachForBodyBehaviourInterface->out->getArmHitPoseEndRelRootImportanceRef(module->owner->getChildIndex())) );

}

//----------------------------------------------------------------------------------------------------------------------
void ArmReachReaction_Con::relocate()
{
  // Reconstruct the previously-allocated resource to fill in the junctions
  NMP::Memory::Format format = getMemoryRequirements();
  NMP::Memory::Resource resource = {this, format};
  NMP::Memory::Format classFormat(sizeof(ArmReachReaction_Con), 16);
  resource.increment(classFormat);

  // Reconnect all junctions
  junc_in_currentReachTargets_0 = ER::Junction::relocate(resource);
  // junc_in_currentReachTargets_0->getEdges()[0].reinit( (char*)&(module->owner->owner->arms[0]->reachForBodyPart->feedOut->getCurrentReachTarget()), (float*)&(module->owner->owner->arms[0]->reachForBodyPart->feedOut->getCurrentReachTargetImportanceRef()) );
  junc_in_currentReachTargets_1 = ER::Junction::relocate(resource);
  // junc_in_currentReachTargets_1->getEdges()[0].reinit( (char*)&(module->owner->owner->arms[1]->reachForBodyPart->feedOut->getCurrentReachTarget()), (float*)&(module->owner->owner->arms[1]->reachForBodyPart->feedOut->getCurrentReachTargetImportanceRef()) );

  junc_in_supportAmount = ER::Junction::relocate(resource);
  // junc_in_supportAmount->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->feedOut->getSupportAmount()), (float*)&(module->owner->owner->bodyFrame->feedOut->getSupportAmountImportanceRef()) );

  junc_in_avgReachingHandPos = ER::Junction::relocate(resource);
  // junc_in_avgReachingHandPos->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->reachForBody->out->getErrorWeightedAverageEffectorPosition()), (float*)&(module->owner->owner->bodyFrame->reachForBody->out->getErrorWeightedAverageEffectorPositionImportanceRef()) );

  junc_in_armHitPoseEndRelRoot = ER::Junction::relocate(resource);
  // junc_in_armHitPoseEndRelRoot->getEdges()[0].reinit( (char*)&(module->owner->owner->reachForBodyBehaviourInterface->out->getArmHitPoseEndRelRoot(module->owner->getChildIndex())), (float*)&(module->owner->owner->reachForBodyBehaviourInterface->out->getArmHitPoseEndRelRootImportanceRef(module->owner->getChildIndex())) );

}

//----------------------------------------------------------------------------------------------------------------------
// Combiner api.
void ArmReachReaction_Con::combineInputs(ER::Module* modulePtr)
{
  ArmReachReaction* module = (ArmReachReaction*)modulePtr;
  ArmReachReactionInputs& in = *module->in;

  // Junction assignments.
  in.m_currentReachTargetsImportance[0] = junc_in_currentReachTargets_0->combineDirectInput(&in.currentReachTargets[0]);
  in.m_currentReachTargetsImportance[1] = junc_in_currentReachTargets_1->combineDirectInput(&in.currentReachTargets[1]);
  in.m_supportAmountImportance = junc_in_supportAmount->combineDirectInput(&in.supportAmount);
  in.m_avgReachingHandPosImportance = junc_in_avgReachingHandPos->combineDirectInput(&in.avgReachingHandPos);
  in.m_armHitPoseEndRelRootImportance = junc_in_armHitPoseEndRelRoot->combineDirectInput(&in.armHitPoseEndRelRoot);

#if NM_CALL_VALIDATORS
  in.validate();
#endif // NM_CALL_VALIDATORS
}


} // namespace NM_BEHAVIOUR_LIB_NAMESPACE


