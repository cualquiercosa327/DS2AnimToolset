#include "BlendNode.h"
#include "Node.h"
#include "NodeUtils.h"
#include "extern.h"
#include "RCore.h"
#include "morpheme/Nodes/mrNodePassThrough.h"
#include "morpheme/Nodes/mrNodeFeatherBlend2.h"
#include "morpheme/Nodes/mrNodeFeatherBlend2SyncEvents.h"
#include "morpheme/Nodes/mrNodeBlend2.h"
#include "morpheme/Nodes/mrNodeBlend2SyncEvents.h"
#include "morpheme/Nodes/mrNodeSubtractiveBlend.h"
#include "morpheme/Nodes/mrNodeSubtractiveBlendSyncEvents.h"
#include "assetProcessor/include/assetProcessor/BlendNodeBuilderUtils.h"

namespace MD
{
	namespace Node
	{
		void writeTimeStretchModeFlags(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			int timeStretchMode = AP::kNodeTimeStretchNone;

			MR::AttribDataUInt* startSyncEventIndex = static_cast<MR::AttribDataUInt*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_START_SYNC_EVENT_INDEX));
			MR::AttribDataUInt* durationEventMatchingOpAttrib = static_cast<MR::AttribDataUInt*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_DURATION_EVENT_MATCHING_OP));
			MR::AttribDataBool* loop = static_cast<MR::AttribDataBool*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_LOOP));

			MR::QueueAttrTaskFn syncEventTrackFn = nodeDef->getTaskQueueingFn(MR::ATTRIB_SEMANTIC_SYNC_EVENT_TRACK);

			if (syncEventTrackFn == MR::nodeBlend2SyncEventsQueueSyncEventTrack)
				timeStretchMode = AP::kNodeTimeStretchMatchEvents;

			attribDataBlock->writeInt(timeStretchMode, "TimeStretchMode");

			if (loop)
				attribDataBlock->writeBool(loop->m_value, "Loop");

			NodeUtils::writeSyncEventFlagsFromAttribData(attribDataBlock, durationEventMatchingOpAttrib);

			if (startSyncEventIndex)
				attribDataBlock->writeInt(startSyncEventIndex->m_value, "StartEventIndex");
		}

		void writeFeatherBlendModeFlags(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			AP::NodeBlendModes blendMode = AP::kNodeBlendInvalid;

			MR::QueueAttrTaskFn taskQueueFn = nodeDef->getTaskQueueingFn(MR::ATTRIB_SEMANTIC_TRANSFORM_BUFFER);
			const char* fnName = MR::Manager::getInstance().getTaskQueuingFnName(taskQueueFn);

			if (taskQueueFn == MR::nodeFeatherBlend2QueueFeatherBlend2TransformBuffsAddAttAddPos)
				blendMode == AP::kAddQuatAddPos;
			else if (taskQueueFn == MR::nodeFeatherBlend2QueueFeatherBlend2TransformBuffsAddAttInterpPos)
				blendMode == AP::kAddQuatInterpPos;
			else if (taskQueueFn == MR::nodeFeatherBlend2QueueFeatherBlend2TransformBuffsInterpAttAddPos)
				blendMode == AP::kInterpQuatAddPos;
			else if (taskQueueFn == MR::nodeFeatherBlend2QueueFeatherBlend2TransformBuffsInterpAttInterpPos)
				blendMode == AP::kInterpQuatInterpPos;
			else
				g_appLog->panicMessage("Unexpected ATTRIB_SEMANTIC_TRANSFORM_BUFFER queueing fn %s\n", fnName);

			bool additiveBlendAtt = false;
			bool additiveBlendPos = false;

			switch (blendMode)
			{
			case AP::kInterpQuatInterpPos:
				additiveBlendAtt = false;
				additiveBlendPos = false;
				break;
			case AP::kInterpQuatAddPos:
				additiveBlendAtt = false;
				additiveBlendPos = true;
				break;
			case AP::kAddQuatInterpPos:
				additiveBlendAtt = true;
				additiveBlendPos = false;
				break;
			case AP::kAddQuatAddPos:
				additiveBlendAtt = true;
				additiveBlendPos = true;
				break;
			default:
				break;
			}

			attribDataBlock->writeBool(additiveBlendAtt, "AdditiveBlendAttitude");
			attribDataBlock->writeBool(additiveBlendPos, "AdditiveBlendPosition");
		}

		void writeBlend2BlendModeFlags(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			AP::NodeBlendModes blendMode = AP::kNodeBlendInvalid;

			MR::QueueAttrTaskFn taskQueueFn = nodeDef->getTaskQueueingFn(MR::ATTRIB_SEMANTIC_TRANSFORM_BUFFER);
			const char* fnName = MR::Manager::getInstance().getTaskQueuingFnName(taskQueueFn);

			if (taskQueueFn == MR::nodeBlend2QueueBlend2TransformBuffsAddAttAddPos)
				blendMode = AP::kAddQuatAddPos;
			else if (taskQueueFn == MR::nodeBlend2QueueBlend2TransformBuffsAddAttInterpPos)
				blendMode = AP::kAddQuatInterpPos;
			else if (taskQueueFn == MR::nodeBlend2QueueBlend2TransformBuffsInterpAttAddPos)
				blendMode = AP::kInterpQuatAddPos;
			else if (taskQueueFn == MR::nodeBlend2QueueBlend2TransformBuffsInterpAttInterpPos)
				blendMode = AP::kInterpQuatInterpPos;
			else
				g_appLog->panicMessage("Unexpected ATTRIB_SEMANTIC_TRANSFORM_BUFFER queueing fn %s\n", fnName);

			attribDataBlock->writeInt(blendMode, "BlendMode");
		}

		void writeEventBlendMode(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			AP::NodeSampledEventBlendModes eventBlendMode = AP::kSampledEventBlendModeInvalid;

			MR::QueueAttrTaskFn taskQueueFn = nodeDef->getTaskQueueingFn(MR::ATTRIB_SEMANTIC_SAMPLED_EVENTS_BUFFER);
			const char* fnName = MR::Manager::getInstance().getTaskQueuingFnName(taskQueueFn);

			if ((taskQueueFn == MR::nodeBlend2SyncEventsQueueSampledEventsBuffers) || (taskQueueFn == MR::nodeBlend2QueueSampledEventsBuffers))
				eventBlendMode = AP::kMergeSampledEvents;
			else if ((taskQueueFn == MR::nodeBlend2SyncEventsQueueAddSampledEventsBuffers) || (taskQueueFn == MR::nodeBlend2QueueAddSampledEventsBuffers))
				eventBlendMode = AP::kAddSampledEvents;

			attribDataBlock->writeInt(eventBlendMode, "EventsBlendMode");
		}

		void writeSlerpTrajPos(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			bool slerpTrajPos = false;

			MR::QueueAttrTaskFn taskQueueFn = nodeDef->getTaskQueueingFn(MR::ATTRIB_SEMANTIC_TRAJECTORY_DELTA_TRANSFORM_BUFFER);

			switch (nodeDef->getNodeTypeID())
			{
			case NODE_TYPE_FEATHER_BLEND_2:
				if ((taskQueueFn == MR::nodeFeatherBlend2QueueTrajectoryDeltaAndTransformsAddAttAddPosSlerpTraj) ||
					(taskQueueFn == MR::nodeFeatherBlend2QueueTrajectoryDeltaAndTransformsAddAttInterpPosSlerpTraj) ||
					(taskQueueFn == MR::nodeFeatherBlend2QueueTrajectoryDeltaAndTransformsInterpAttAddPosSlerpTraj) || 
					(taskQueueFn == MR::nodeFeatherBlend2QueueTrajectoryDeltaAndTransformsInterpAttInterpPosSlerpTraj))
					slerpTrajPos = true;
				break;
			case NODE_TYPE_BLEND_2:
				if ((taskQueueFn == MR::nodeBlend2QueueTrajectoryDeltaAndTransformsAddAttAddPosSlerpTraj) || 
					(taskQueueFn == MR::nodeBlend2QueueTrajectoryDeltaAndTransformsAddAttInterpPosSlerpTraj) ||
					(taskQueueFn == MR::nodeBlend2QueueTrajectoryDeltaAndTransformsInterpAttAddPosSlerpTraj) ||
					(taskQueueFn == MR::nodeBlend2QueueTrajectoryDeltaAndTransformsInterpAttInterpPosSlerpTraj))
					slerpTrajPos = true;
				break;
			case NODE_TYPE_SUBTRACTIVE_BLEND:
				if ((taskQueueFn == MR::nodeSubtractiveBlendQueueTrajectoryDeltaAndTransformsSubtractAttSubtractPosSlerpTraj))
					slerpTrajPos = true;
				break;
			case NODE_TYPE_BLEND_N:
				if ((taskQueueFn == MR::nodeBlend2QueueTrajectoryDeltaAndTransformsInterpAttInterpPosSlerpTraj))
					slerpTrajPos = true;
				break;
			default:
				g_appLog->panicMessage("Invalid node type %d (expecting a blend node)");
				break;
			}

			attribDataBlock->writeBool(slerpTrajPos, "SphericallyInterpolateTrajectoryPosition");
		}

		void writePassThroughMode(MR::NodeDef* nodeDef, ME::DataBlockExportXML* attribDataBlock)
		{
			if (nodeDef->getNodeFlags() & MR::NodeDef::NODE_FLAG_IS_FILTER)
			{
				uint16_t passThroughChildIndex = nodeDef->getPassThroughChildIndex();

				switch (passThroughChildIndex)
				{
				case 0:
					attribDataBlock->writeInt(AP::kNodePassThroughSource0, "PassThroughMode");
					break;
				case 1:
					attribDataBlock->writeInt(AP::kNodePassThroughSource1, "PassThroughMode");
					break;
				}

				return;
			}

			attribDataBlock->writeInt(AP::kNodePassThroughNone, "PassThroughMode");
		}

		bool isBlendNodeWrapWeights(MR::NodeDef* nodeDef)
		{
			int numSourceNodes = nodeDef->getNumChildNodes();

			MR::AttribDataFloatArray* weights = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_CHILD_NODE_WEIGHTS));

			if (weights->m_numValues == numSourceNodes)
				return false;

			return true;
		}

		ME::NodeExportXML* exportBlend2Node(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_BLEND_2);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(0), "Source0NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(1), "Source1NodeID");
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Weight", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataFloatArray* weights = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_CHILD_NODE_WEIGHTS));

			assert(weights->m_numValues == 2);

			nodeDataBlock->writeFloat(weights->m_values[0], "BlendWeight_0");
			nodeDataBlock->writeFloat(weights->m_values[1], "BlendWeight_1");

			writePassThroughMode(nodeDef, nodeDataBlock);
			writeEventBlendMode(nodeDef, nodeDataBlock);
			writeSlerpTrajPos(nodeDef, nodeDataBlock);
			writeBlend2BlendModeFlags(nodeDef, nodeDataBlock);
			writeTimeStretchModeFlags(nodeDef, nodeDataBlock);

			MR::AttribDataBlendFlags* blendFlags = static_cast<MR::AttribDataBlendFlags*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_BLEND_FLAGS));
			nodeDataBlock->writeBool(blendFlags->m_alwaysCombineSampledEvents, "AlwaysCombineSampledEvents");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportBlend2x2Node(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_BLEND_2X2);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(0), "Source0NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(1), "Source1NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(2), "Source2NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(3), "Source3NodeID");
			NodeUtils::writeInputCPConnection(nodeDataBlock, "WeightX", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "WeightY", nodeDef->getInputCPConnection(1), true);

			MR::AttribDataFloatArray* weights = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_CHILD_NODE_WEIGHTS));

			assert(weights->m_numValues == 4);

			nodeDataBlock->writeFloat(weights->m_values[0], "BlendWeightX_0");
			nodeDataBlock->writeFloat(weights->m_values[1], "BlendWeightX_1");
			nodeDataBlock->writeFloat(weights->m_values[2], "BlendWeightY_0");
			nodeDataBlock->writeFloat(weights->m_values[3], "BlendWeightY_1");

			writePassThroughMode(nodeDef, nodeDataBlock);
			writeEventBlendMode(nodeDef, nodeDataBlock);
			writeSlerpTrajPos(nodeDef, nodeDataBlock);
			writeBlend2BlendModeFlags(nodeDef, nodeDataBlock);
			writeTimeStretchModeFlags(nodeDef, nodeDataBlock);

			MR::AttribDataBlendFlags* blendFlags = static_cast<MR::AttribDataBlendFlags*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_BLEND_FLAGS));
			nodeDataBlock->writeBool(blendFlags->m_alwaysCombineSampledEvents, "AlwaysCombineSampledEvents");

			MR::AttribDataBool* loop = static_cast<MR::AttribDataBool*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_LOOP));
			nodeDataBlock->writeBool(loop->m_value, "Loop");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportBlendNNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_BLEND_N);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			const int sourceNodeCount = nodeDef->getNumChildNodes();

			nodeDataBlock->writeInt(sourceNodeCount, "SourceNodeCount");

			CHAR paramName[256];
			for (int i = 0; i < sourceNodeCount; i++)
			{
				sprintf_s(paramName, "Source%dNodeID", i);

				nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(i), paramName);
			}

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Weight", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataFloatArray* weights = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_CHILD_NODE_WEIGHTS));
			for (int i = 0; i < sourceNodeCount; i++)
			{
				sprintf_s(paramName, "SourceWeight_%d", i);

				nodeDataBlock->writeFloat(weights->m_values[i], paramName);
			}

			bool wrapWeights = isBlendNodeWrapWeights(nodeDef);
			nodeDataBlock->writeBool(wrapWeights, "WrapWeights");

			if (wrapWeights)
				nodeDataBlock->writeFloat(weights->m_values[sourceNodeCount], "WrapWeight");

			writeTimeStretchModeFlags(nodeDef, nodeDataBlock);
			writeSlerpTrajPos(nodeDef, nodeDataBlock);

			MR::AttribDataBlendFlags* blendFlags = static_cast<MR::AttribDataBlendFlags*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_BLEND_FLAGS));
			nodeDataBlock->writeBool(blendFlags->m_alwaysCombineSampledEvents, "AlwaysCombineSampledEvents");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportFeatherBlendNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_FEATHER_BLEND_2);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			const int numAnimSets = netDef->getNumAnimSets();

			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(0), "Source0NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(1), "Source1NodeID");
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Weight", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataFloatArray* childWeights = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_CHILD_NODE_WEIGHTS));

			nodeDataBlock->writeFloat(childWeights->m_values[0], "BlendWeight_0");
			nodeDataBlock->writeFloat(childWeights->m_values[1], "BlendWeight_1");

			writePassThroughMode(nodeDef, nodeDataBlock);
			writeTimeStretchModeFlags(nodeDef, nodeDataBlock);
			writeFeatherBlendModeFlags(nodeDef, nodeDataBlock);
			writeEventBlendMode(nodeDef, nodeDataBlock);
			writeSlerpTrajPos(nodeDef, nodeDataBlock);

			MR::AttribDataBlendFlags* blendFlags = static_cast<MR::AttribDataBlendFlags*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_BLEND_FLAGS));
			nodeDataBlock->writeBool(blendFlags->m_alwaysCombineSampledEvents, "AlwaysCombineSampledEvents");

			nodeDataBlock->writeInt(numAnimSets, "NumAnimSets");

			char paramNumAlphas[256];
			char paramAlpha[256];
			for (short setIndex = 0; setIndex < numAnimSets; setIndex++)
			{
				MR::AttribDataFeatherBlend2ChannelAlphas* channelAlphas = static_cast<MR::AttribDataFeatherBlend2ChannelAlphas*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_BONE_WEIGHTS, setIndex));

				int numAlphaValues = channelAlphas->m_numChannelAlphas;

				sprintf_s(paramNumAlphas, "ChannelAlphasSet%dCount", setIndex);
				nodeDataBlock->writeInt(numAlphaValues, paramNumAlphas);

				for (int j = 0; j < numAlphaValues; j++)
				{
					sprintf_s(paramAlpha, "ChannelAlphasSet%d_Value%d", setIndex, j);
					nodeDataBlock->writeFloat(channelAlphas->m_channelAlphas[j], paramAlpha);
				}
			}

			return nodeExportXML;
		}

		ME::NodeExportXML* exportSubtractiveBlendNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_SUBTRACTIVE_BLEND);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			const int numAnimSets = netDef->getNumAnimSets();

			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(0), "Source0NodeID");
			nodeDataBlock->writeNetworkNodeId(nodeDef->getChildNodeID(1), "Source1NodeID");

			writeTimeStretchModeFlags(nodeDef, nodeDataBlock);
			writeSlerpTrajPos(nodeDef, nodeDataBlock);
			writePassThroughMode(nodeDef, nodeDataBlock);
			writeEventBlendMode(nodeDef, nodeDataBlock);

			return nodeExportXML;
		}
	}
}