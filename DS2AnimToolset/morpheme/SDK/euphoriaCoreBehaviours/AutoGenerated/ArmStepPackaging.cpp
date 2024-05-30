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
#include "ArmStep.h"
#include "ArmStepPackaging.h"
#include "MyNetwork.h"
#include "BalanceBehaviourInterface.h"
#include "BodyFrame.h"
#include "BodyBalance.h"
#include "BalanceManagement.h"
#include "StaticBalance.h"
#include "ArmPackaging.h"
#include "MyNetworkPackaging.h"

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

//----------------------------------------------------------------------------------------------------------------------
void ArmStep_Con::create(ER::Module* module, ER::Module* NMP_UNUSED(owner))
{
  buildConnections((ArmStep*)module);
}

//----------------------------------------------------------------------------------------------------------------------
ArmStep_Con::~ArmStep_Con()
{
  junc_in_averageStandingPoseEndRelativeToSupport->destroy();
  junc_in_standingPoseEndRelativeToSupport_1->destroy();
  junc_in_standingPoseEndRelativeToSupport_0->destroy();
  junc_in_groundVelocity->destroy();
  junc_in_supportTM->destroy();
  junc_in_evaluateStep->destroy();
  junc_in_recoveryStepTarget->destroy();
  junc_in_allowStep->destroy();
  junc_in_averageEndContactNormal->destroy();
  junc_in_stepParameters->destroy();
  junc_in_enableStep->destroy();
}

//----------------------------------------------------------------------------------------------------------------------
NMP::Memory::Format ArmStep_Con::getMemoryRequirements()
{
  NMP::Memory::Format result(sizeof(ArmStep_Con), 16);

  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  result += ER::Junction::getMemoryRequirements(1);
  return result;
}
//----------------------------------------------------------------------------------------------------------------------
void ArmStep_Con::buildConnections(ArmStep* module)
{
  // Reconstruct the previously-allocated resource to fill in the junctions
  NMP::Memory::Format format = getMemoryRequirements();
  NMP::Memory::Resource resource = {this, format};
  NMP::Memory::Format classFormat(sizeof(ArmStep_Con), 16);
  resource.increment(classFormat);

  ER::Junction* activeJnc = 0;

  // build and connect up all junctions
  junc_in_enableStep = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceBehaviourInterface->out->getStepWithArms()), (float*)&(module->owner->owner->balanceBehaviourInterface->out->getStepWithArmsImportanceRef()) );

  junc_in_stepParameters = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceBehaviourInterface->out->getStepParameters()), (float*)&(module->owner->owner->balanceBehaviourInterface->out->getStepParametersImportanceRef()) );

  junc_in_averageEndContactNormal = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAverageSupportingLimbContactNormal()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAverageSupportingLimbContactNormalImportanceRef()) );

  junc_in_allowStep = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAllowArmStep(module->owner->getChildIndex())), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAllowArmStepImportanceRef(module->owner->getChildIndex())) );

  junc_in_recoveryStepTarget = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getRecoveryArmStepTarget(module->owner->getChildIndex())), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getRecoveryArmStepTargetImportanceRef(module->owner->getChildIndex())) );

  junc_in_evaluateStep = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getEvaluateStep()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getEvaluateStepImportanceRef()) );

  junc_in_supportTM = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getSupportTM()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getSupportTMImportanceRef()) );

  junc_in_groundVelocity = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getGroundVelocity()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getGroundVelocityImportanceRef()) );

  junc_in_standingPoseEndRelativeToSupport_0 = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupport(0)), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupportImportanceRef(0)) );
  junc_in_standingPoseEndRelativeToSupport_1 = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupport(1)), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupportImportanceRef(1)) );

  junc_in_averageStandingPoseEndRelativeToSupport = activeJnc = ER::Junction::init(resource, 1, ER::Junction::directInput);
  activeJnc->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getAverageArmPoseEndRelSupport()), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getAverageArmPoseEndRelSupportImportanceRef()) );

}

//----------------------------------------------------------------------------------------------------------------------
void ArmStep_Con::relocate()
{
  // Reconstruct the previously-allocated resource to fill in the junctions
  NMP::Memory::Format format = getMemoryRequirements();
  NMP::Memory::Resource resource = {this, format};
  NMP::Memory::Format classFormat(sizeof(ArmStep_Con), 16);
  resource.increment(classFormat);

  // Reconnect all junctions
  junc_in_enableStep = ER::Junction::relocate(resource);
  // junc_in_enableStep->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceBehaviourInterface->out->getStepWithArms()), (float*)&(module->owner->owner->balanceBehaviourInterface->out->getStepWithArmsImportanceRef()) );

  junc_in_stepParameters = ER::Junction::relocate(resource);
  // junc_in_stepParameters->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceBehaviourInterface->out->getStepParameters()), (float*)&(module->owner->owner->balanceBehaviourInterface->out->getStepParametersImportanceRef()) );

  junc_in_averageEndContactNormal = ER::Junction::relocate(resource);
  // junc_in_averageEndContactNormal->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAverageSupportingLimbContactNormal()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAverageSupportingLimbContactNormalImportanceRef()) );

  junc_in_allowStep = ER::Junction::relocate(resource);
  // junc_in_allowStep->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAllowArmStep(module->owner->getChildIndex())), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getAllowArmStepImportanceRef(module->owner->getChildIndex())) );

  junc_in_recoveryStepTarget = ER::Junction::relocate(resource);
  // junc_in_recoveryStepTarget->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getRecoveryArmStepTarget(module->owner->getChildIndex())), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getRecoveryArmStepTargetImportanceRef(module->owner->getChildIndex())) );

  junc_in_evaluateStep = ER::Junction::relocate(resource);
  // junc_in_evaluateStep->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getEvaluateStep()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getEvaluateStepImportanceRef()) );

  junc_in_supportTM = ER::Junction::relocate(resource);
  // junc_in_supportTM->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getSupportTM()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getSupportTMImportanceRef()) );

  junc_in_groundVelocity = ER::Junction::relocate(resource);
  // junc_in_groundVelocity->getEdges()[0].reinit( (char*)&(module->owner->owner->bodyFrame->bodyBalance->out->getGroundVelocity()), (float*)&(module->owner->owner->bodyFrame->bodyBalance->out->getGroundVelocityImportanceRef()) );

  junc_in_standingPoseEndRelativeToSupport_0 = ER::Junction::relocate(resource);
  // junc_in_standingPoseEndRelativeToSupport_0->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupport(0)), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupportImportanceRef(0)) );
  junc_in_standingPoseEndRelativeToSupport_1 = ER::Junction::relocate(resource);
  // junc_in_standingPoseEndRelativeToSupport_1->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupport(1)), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getArmPoseEndRelSupportImportanceRef(1)) );

  junc_in_averageStandingPoseEndRelativeToSupport = ER::Junction::relocate(resource);
  // junc_in_averageStandingPoseEndRelativeToSupport->getEdges()[0].reinit( (char*)&(module->owner->owner->balanceManagement->staticBalance->out->getAverageArmPoseEndRelSupport()), (float*)&(module->owner->owner->balanceManagement->staticBalance->out->getAverageArmPoseEndRelSupportImportanceRef()) );

}

//----------------------------------------------------------------------------------------------------------------------
// Combiner api.
void ArmStep_Con::combineInputs(ER::Module* modulePtr)
{
  ArmStep* module = (ArmStep*)modulePtr;
  ArmStepInputs& in = *module->in;

  // Junction assignments.
  in.m_enableStepImportance = junc_in_enableStep->combineDirectInput(&in.enableStep);
  in.m_stepParametersImportance = junc_in_stepParameters->combineDirectInput(&in.stepParameters);
  in.m_averageEndContactNormalImportance = junc_in_averageEndContactNormal->combineDirectInput(&in.averageEndContactNormal);
  in.m_allowStepImportance = junc_in_allowStep->combineDirectInput(&in.allowStep);
  in.m_recoveryStepTargetImportance = junc_in_recoveryStepTarget->combineDirectInput(&in.recoveryStepTarget);
  in.m_evaluateStepImportance = junc_in_evaluateStep->combineDirectInput(&in.evaluateStep);
  in.m_supportTMImportance = junc_in_supportTM->combineDirectInput(&in.supportTM);
  in.m_groundVelocityImportance = junc_in_groundVelocity->combineDirectInput(&in.groundVelocity);
  in.m_standingPoseEndRelativeToSupportImportance[0] = junc_in_standingPoseEndRelativeToSupport_0->combineDirectInput(&in.standingPoseEndRelativeToSupport[0]);
  in.m_standingPoseEndRelativeToSupportImportance[1] = junc_in_standingPoseEndRelativeToSupport_1->combineDirectInput(&in.standingPoseEndRelativeToSupport[1]);
  in.m_averageStandingPoseEndRelativeToSupportImportance = junc_in_averageStandingPoseEndRelativeToSupport->combineDirectInput(&in.averageStandingPoseEndRelativeToSupport);

#if NM_CALL_VALIDATORS
  in.validate();
#endif // NM_CALL_VALIDATORS
}


} // namespace NM_BEHAVIOUR_LIB_NAMESPACE


