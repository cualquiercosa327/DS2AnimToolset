#include "OperatorNode.h"
#include "Node.h"
#include "extern.h"
#include "RCore.h"
#include "morpheme/mrAttribData.h"
#include "morpheme/Nodes/mrNodeOperatorSmoothFloat.h"
#include "morpheme/Nodes/mrNodeOperatorRateOfChange.h"

namespace MD
{
	namespace Node
	{
		bool isSmoothFloatScalar(MR::NodeDef* nodeDef)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_SMOOTH_FLOAT);
			
			MR::OutputCPTask outputCPTask = nodeDef->getOutputCPTask(0);

			if (outputCPTask == MR::nodeOperatorSmoothFloatCriticallyDampFloat)
				return true;
			else if (outputCPTask == MR::nodeOperatorSmoothFloatCriticallyDampVector)
				return false;
			else
				g_appLog->panicMessage("Invalid outputCPTaskFunction %s (nodeId=%d)\n", MR::Manager::getInstance().getOutputCPTaskName(outputCPTask), MR::Manager::getInstance().getOutputCPTaskName(outputCPTask), nodeDef->getNodeID());

			return false;
		}

		bool isRateOfChangeScalar(MR::NodeDef* nodeDef)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_SMOOTH_FLOAT);

			MR::OutputCPTask outputCPTask = nodeDef->getOutputCPTask(0);

			if (outputCPTask == MR::nodeOperatorRateOfChangeFloat)
				return true;
			else if (outputCPTask == MR::nodeOperatorRateOfChangeVector)
				return false;
			else
				g_appLog->panicMessage("Invalid outputCPTaskFunction %s (nodeId=%d)\n", MR::Manager::getInstance().getOutputCPTaskName(outputCPTask), MR::Manager::getInstance().getOutputCPTaskName(outputCPTask), nodeDef->getNodeID());

			return false;
		}

		ME::NodeExportXML* exportOperatorFunctionNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_FUNCTION);
			
			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataFunctionOperation* functionOpCode = static_cast<MR::AttribDataFunctionOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));
		
			nodeDataBlock->writeInt(functionOpCode->m_operation, "OperationCode");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorArithmeticNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_ARITHMETIC);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			MR::AttribDataArithmeticOperation* functionOpCode = static_cast<MR::AttribDataArithmeticOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeInt(functionOpCode->m_operation, "OperationCode");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorArithmeticVector3Node(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_ARITHMETIC_VECTOR3);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			MR::AttribDataArithmeticOperation* functionOpCode = static_cast<MR::AttribDataArithmeticOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeInt(functionOpCode->m_operation, "OperationCode");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorFloatsToVector3Node(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_FLOATS_TO_VECTOR3);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "FloatX", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "FloatY", nodeDef->getInputCPConnection(1), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "FloatZ", nodeDef->getInputCPConnection(2), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3ToFloatsNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_TO_FLOATS);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3Dot(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_DOT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3Distance(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_DISTANCE);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3CrossProduct(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_CROSSPRODUCT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3Angle(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_ANGLE);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input0", nodeDef->getInputCPConnection(0), true);
			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input1", nodeDef->getInputCPConnection(1), true);

			MR::AttribDataVector3* angleAttrib = static_cast<MR::AttribDataVector3*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			int axisID = NodeUtils::getAxisIndex(angleAttrib->m_value);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorVector3Normalise(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_NORMALISE);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorRayCast(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_VECTOR3_NORMALISE);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			MR::AttribDataRayCastDef* rayCastAttrib = static_cast<MR::AttribDataRayCastDef*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeFloat(rayCastAttrib->m_rayStart.x, "RayStartX");
			nodeDataBlock->writeFloat(rayCastAttrib->m_rayStart.y, "RayStartY");
			nodeDataBlock->writeFloat(rayCastAttrib->m_rayStart.z, "RayStartZ");

			nodeDataBlock->writeFloat(rayCastAttrib->m_rayDelta.x, "RayDeltaX");
			nodeDataBlock->writeFloat(rayCastAttrib->m_rayDelta.y, "RayDeltaY");
			nodeDataBlock->writeFloat(rayCastAttrib->m_rayDelta.z, "RayDeltaZ");

			nodeDataBlock->writeBool(rayCastAttrib->m_useLocalOrientation, "UseLocalOrientation");
			nodeDataBlock->writeInt(rayCastAttrib->m_upAxisIndex, "UpAxisIndex");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorFloatToIntNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_FLOAT_TO_INT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Float", nodeDef->getInputCPConnection(0), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorIntToFloatNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_INT_TO_FLOAT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Int", nodeDef->getInputCPConnection(0), true);

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorNoiseGenNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_NOISE_GEN);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataNoiseGenDef* noiseGenDef = static_cast<MR::AttribDataNoiseGenDef*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeFloat(noiseGenDef->m_noiseSawFrequency, "NoiseSawFrequency");
			nodeDataBlock->writeInt(noiseGenDef->m_flags, "NoiseFlags");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorSmoothFloatNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_SMOOTH_FLOAT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataSmoothFloatOperation* smoothFloatOperation = static_cast<MR::AttribDataSmoothFloatOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeBool(isSmoothFloatScalar(nodeDef), "IsScalar");
			nodeDataBlock->writeBool(smoothFloatOperation->m_smoothVel, "SmoothVelocity");

			nodeDataBlock->writeFloat(smoothFloatOperation->m_floatRate, "SmoothTime");
			nodeDataBlock->writeFloat(smoothFloatOperation->m_initialValueX, "InitValue_X");
			nodeDataBlock->writeFloat(smoothFloatOperation->m_initialValueY, "InitValue_Y");
			nodeDataBlock->writeFloat(smoothFloatOperation->m_initialValueZ, "InitValue_Z");
			nodeDataBlock->writeBool(smoothFloatOperation->m_useInitValOnInit, "UseInitValueOnInit");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorRampFloatNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_RAMP_FLOAT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "RateMultiplier", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataFloatArray* valuesAttrib = static_cast<MR::AttribDataFloatArray*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeFloat(valuesAttrib->m_values[0], "InitialValue");
			nodeDataBlock->writeFloat(valuesAttrib->m_values[1], "RateOfChange");
			nodeDataBlock->writeFloat(valuesAttrib->m_values[2], "MinimumValue");
			nodeDataBlock->writeFloat(valuesAttrib->m_values[3], "MaximumValue");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorRandomFloatNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_RANDOM_FLOAT);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			MR::AttribDataRandomFloatDef* randomFloatDef = static_cast<MR::AttribDataRandomFloatDef*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeFloat(randomFloatDef->m_min, "Min");
			nodeDataBlock->writeFloat(randomFloatDef->m_max, "Max");
			nodeDataBlock->writeFloat(randomFloatDef->m_duration, "Interval");
			nodeDataBlock->writeUInt(randomFloatDef->m_seed, "Seed");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorRateOfChangeNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_RATE_OF_CHANGE);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataRateOfChangeState* rateOfChangeAttrib = static_cast<MR::AttribDataRateOfChangeState*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeBool(isRateOfChangeScalar(nodeDef), "IsScalar");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorOneInputArithmeticNode(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_ONE_INPUT_ARITHMETIC);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataArithmeticOperation* functionOpCode = static_cast<MR::AttribDataArithmeticOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeInt(functionOpCode->m_operation, "OperationCode");
			nodeDataBlock->writeFloat(functionOpCode->m_constValue, "ConstantValue");
			nodeDataBlock->writeFloat(functionOpCode->m_constVector.x, "ConstantValueX");

			return nodeExportXML;
		}

		ME::NodeExportXML* exportOperatorOneInputArithmeticVector3Node(ME::NetworkDefExportXML* netDefExport, MR::NetworkDef* netDef, MR::NodeDef* nodeDef, std::string nodeName)
		{
			THROW_NODE_TYPE_MISMATCH(nodeDef, NODE_TYPE_CP_OP_ONE_INPUT_ARITHMETIC_VECTOR3);

			ME::NodeExportXML* nodeExportXML = exportNodeCore(netDefExport, netDef, nodeDef, nodeName);
			ME::DataBlockExportXML* nodeDataBlock = static_cast<ME::DataBlockExportXML*>(nodeExportXML->getDataBlock());

			NodeUtils::writeInputCPConnection(nodeDataBlock, "Input", nodeDef->getInputCPConnection(0), true);

			MR::AttribDataArithmeticOperation* functionOpCode = static_cast<MR::AttribDataArithmeticOperation*>(nodeDef->getAttribData(MR::ATTRIB_SEMANTIC_NODE_SPECIFIC_DEF));

			nodeDataBlock->writeInt(functionOpCode->m_operation, "OperationCode");
			nodeDataBlock->writeFloat(functionOpCode->m_constVector.x, "ConstantValueX");
			nodeDataBlock->writeFloat(functionOpCode->m_constVector.y, "ConstantValueY");
			nodeDataBlock->writeFloat(functionOpCode->m_constVector.z, "ConstantValueZ");

			return nodeExportXML;
		}
	}
}