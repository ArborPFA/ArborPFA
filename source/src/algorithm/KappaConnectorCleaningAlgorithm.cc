  /// \file KappaConnectorCleaningAlgorithm.cc
/*
 *
 * KappaConnectorCleaningAlgorithm.cc source template automatically generated by a class generator
 * Creation date : ven. sept. 19 2014
 *
 * This file is part of ArborPFA libraries.
 * 
 * ArborPFA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * ArborPFA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ArborPFA.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#include "arborpfa/algorithm/KappaConnectorCleaningAlgorithm.h"

// pandora
#include "Api/PandoraContentApi.h"

// arborpfa
#include "arborpfa/api/ArborContentApi.h"
#include "arborpfa/arbor/AlgorithmHeaders.h"

namespace arbor
{

//--------------------------------------------------------------------------------------------------------------------

pandora::StatusCode KappaConnectorCleaningAlgorithm::RunArborAlgorithm()
{
	unsigned int count = 0;

	const ObjectList *pObjectList = NULL;
	PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ArborContentApi::GetCurrentObjectList(*this, pObjectList));

	if(pObjectList->empty())
		return pandora::STATUS_CODE_SUCCESS;

	ObjectCleaningInfoList objectInfoList;

	// loop over objects
	for(ObjectList::const_iterator iter = pObjectList->begin() , endIter = pObjectList->end() ; endIter != iter ; ++iter)
	{
		Object *pObject = *iter;

		// initialization of final backward connector
		PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pObject->SetCurrentBackwardConnector(NULL));

		// if no backward connection no need to continue.
		if(pObject->GetBackwardConnectorList().empty())
			continue;

		pandora::CartesianVector meanBackwardDirection(0.f, 0.f, 0.f);

		PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ArborHelper::GetReferenceDirection(pObject,
				m_backwardConnectorWeight, m_forwardConnectorWeight, m_referenceDirectionDepth,
				m_referenceDirectionMaximumForwardLayer, meanBackwardDirection));

		const ConnectorList &connectorList = pObject->GetBackwardConnectorList();
		const pandora::CartesianVector &objectPosition = pObject->GetPosition();

		Object *pBestObject = NULL;
		Connector *pBestConnector = NULL;
		float bestOrderParameter = std::numeric_limits<float>::max();
		ObjectList deleteConnectionObjects;

		// loop over connectors and find the one with the best order parameter
		for(ConnectorList::const_iterator connectorIter = connectorList.begin() , connectorEndIter = connectorList.end() ; connectorEndIter != connectorIter ; ++connectorIter)
		{
			Connector *pConnector = *connectorIter;

			Object *pOtherObject = NULL;

			if(pObject == pConnector->GetFirst())
				pOtherObject = pConnector->GetSecond();
			else
				pOtherObject = pConnector->GetFirst();

			float orderParameter = 0.f;

			// compute the order parameter wrt the mean backward direction (unit vector)
			PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ArborHelper::GetKappaParameter(pObject, pOtherObject,
					meanBackwardDirection.GetUnitVector(), m_orderParameterAnglePower, m_orderParameterDistancePower, orderParameter));

			if(bestOrderParameter > orderParameter)
			{
				if(NULL != pBestObject)
					deleteConnectionObjects.insert(pBestObject);

				bestOrderParameter = orderParameter;
				pBestConnector = pConnector;
				pBestObject = pOtherObject;
		 }
			else
			{
				deleteConnectionObjects.insert(pOtherObject);
			}

		} // end of connector loop

		PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pObject->SetCurrentBackwardConnector(NULL));

		if(NULL != pBestObject)
		{
			ObjectCleaningInfo *objectInfo = new ObjectCleaningInfo();
			objectInfo->m_pObject = pObject;
			objectInfo->m_pBestConnector = pBestConnector;
			objectInfo->m_deleteConnectionList = deleteConnectionObjects;

			objectInfoList.insert(objectInfo);
		}
	}

	// delete all the connectors that are no longer needed and
	// set the best connector as the current backward one
	for(ObjectCleaningInfoList::iterator iter = objectInfoList.begin() , endIter = objectInfoList.end() ; endIter != iter ; ++iter)
	{
		ObjectCleaningInfo *pObjectCleaningInfo = *iter;
		Object *pObject = pObjectCleaningInfo->m_pObject;

		for(ObjectList::iterator objectIter = pObjectCleaningInfo->m_deleteConnectionList.begin() , objectEndIter = pObjectCleaningInfo->m_deleteConnectionList.end() ; objectEndIter != objectIter ; ++objectIter)
		{
			Object *pOtherObject = *objectIter;
			PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pObject->RemoveConnectionWith(pOtherObject));
			pOtherObject = NULL;
		}

		PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pObject->SetCurrentBackwardConnector(pObjectCleaningInfo->m_pBestConnector));

			// Set it as final decision
			PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pObjectCleaningInfo->m_pBestConnector->SetType(FINAL_DECISION));

		delete pObjectCleaningInfo;
	}

	objectInfoList.clear();

	return pandora::STATUS_CODE_SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------

pandora::StatusCode KappaConnectorCleaningAlgorithm::ReadSettings(const pandora::TiXmlHandle xmlHandle)
{
	m_backwardConnectorWeight = 1;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "BackwardConnectorWeight", m_backwardConnectorWeight));

 m_forwardConnectorWeight = 1;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "ForwardConnectorWeight", m_forwardConnectorWeight));

 m_orderParameterAnglePower = 0.5;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "OrderParameterAnglePower", m_orderParameterAnglePower));

 m_orderParameterDistancePower = 1;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "OrderParameterDistancePower", m_orderParameterDistancePower));

 m_referenceDirectionDepth = 1;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "ReferenceDirectionDepth", m_referenceDirectionDepth));

 m_referenceDirectionMaximumForwardLayer = 3;
 PANDORA_RETURN_RESULT_IF_AND_IF(pandora::STATUS_CODE_SUCCESS, pandora::STATUS_CODE_NOT_FOUND, !=, pandora::XmlHelper::ReadValue(xmlHandle,
     "ReferenceDirectionMaximumForwardLayer", m_referenceDirectionMaximumForwardLayer));

	return pandora::STATUS_CODE_SUCCESS;
}


} 

