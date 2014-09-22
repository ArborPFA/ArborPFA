  /// \file ConnectorParentAlgorithm.h
/*
 *
 * ConnectorParentAlgorithm.h header template automatically generated by a class generator
 * Creation date : lun. sept. 22 2014
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


#ifndef CONNECTORPARENTALGORITHM_H
#define CONNECTORPARENTALGORITHM_H

#include "arborpfa/algorithm/ArborAlgorithm.h"
#include "arborpfa/algorithm/ArborAlgorithmFactory.h"

namespace arbor
{

/** 
 * @brief ConnectorAlgorithmParent class
 */ 
class ConnectorParentAlgorithm : public ArborAlgorithm
{
public:

	/**
		* @brief Factory class for instantiating algorithm
		*/
	class Factory : public ArborAlgorithmFactory
	{
		public:
			ArborAlgorithm *CreateArborAlgorithm() const;
	};

	/**
		* @brief Run the algorithm
		*/
	pandora::StatusCode RunArborAlgorithm();

	/**
		* @brief Read settings from Xml handler
		*/
	pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

protected:

	pandora::StringVector         m_connectorAlgorithmList;
};

//--------------------------------------------------------------------------------------------------------------------

inline ArborAlgorithm *ConnectorParentAlgorithm::Factory::CreateArborAlgorithm() const
{
	return new ConnectorParentAlgorithm();
}

} 

#endif  //  CONNECTORPARENTALGORITHM_H
