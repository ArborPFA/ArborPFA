/*
 *
 * ArborObject.h header template automatically generated by a class generator
 * Creation date : lun. f�vr. 10 2014
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


#ifndef ARBOROBJECT_H
#define ARBOROBJECT_H

#include "arborpfa/arbor/ArborTypes.h"

#include "Pandora/StatusCodes.h"
#include "Pandora/PandoraInputTypes.h"
#include "Objects/CartesianVector.h"

namespace pandora
{
 class CartesianVector;
 class Cluster;
 class Algorithm;
}

namespace arborpfa {

class ArborManager;
class Connector;

/** 
 * @brief ArborObject class. </br>
 * Base class for all arbor object to be connected.
 */
class ArborObject
{
 public:

		/**
			* @brief  Check if this object is connected with a given one
			*
			* @param  pObject the object to check connection with
			* @return boolean
			*/
		virtual bool IsConnectedWith(ArborObject *pObject) const = 0;

		/**
		 * @brief  Get the connectors to other arbor objects
		 *
		 * @return The connector list
		 */
		virtual const ConnectorList &GetConnectors() const = 0;

		/**
		 * @brief Return the list of backward connectors
		 */
		virtual const ConnectorList &GetBackwardConnectorList() const = 0;

		/**
		 * @brief Return the list of forward connectors
		 */
		virtual const ConnectorList &GetForwardConnectorList() const = 0;

		/**
		 * @brief Whether the connector is a backward one for this object. </br>
		 * Return also false if the connector is neither backward nor forward
		 *
		 * @param pConnector the connector to test
		 */
		virtual bool IsBackwardConnector(const Connector *pConnector) const = 0;

		/**
		 * @brief Whether the connector is a forward one for this object. </br>
		 * Return also false if the connector is neither backward nor forward
		 *
		 * @param pConnector the connector to test
		 */
		virtual bool IsForwardConnector(const Connector *pConnector) const = 0;

		/**
		 * @brief Find a specific connection with an other arbor object
		 *
		 * @param pObject the arbor object to check the connection with
		 * @param pConnector the connector address to receive
		 */
		virtual pandora::StatusCode FindConnector(ArborObject *pObject, Connector *&pConnector) const = 0;

		/**
		 * @brief Get the tag on this object
		 *
		 * @return the tag string
		 */
		virtual ArborObjectType GetType() const = 0;

		/**
		 * @brief Get the position of the object
		 *
		 * @param position the position to retrieve
		 */
		virtual const pandora::CartesianVector &GetPosition() const = 0;

		/**
		 * @brief Whether the object is connected with other objects
		 *
		 * @return boolean
		 */
		virtual bool IsConnected() const = 0;

		/**
		 * @brief Connect this object with the given one and put a weight on this connection
		 *
		 * @param pObject the arbor object to connect with
		 * @param direction BACKWARD or FORWARD
		 * @param weight the weight for this new connection
		 */
		virtual pandora::StatusCode ConnectWith(ArborObject *pObject, ConnectorDirection direction, float weight = 1.0) = 0;

		/**
		 * @brief Connect this object with the given one, put a weight on this connection and retrieve the connector
		 *
		 * @param pObject the arbor object to connect with
		 * @param direction BACKWARD or FORWARD
		 * @param pConnector the connector address to receive
		 * @param weight the weight for this new connection
		 */
		virtual pandora::StatusCode ConnectWith(ArborObject *pObject, ConnectorDirection direction, Connector *&pConnector, float weight = 1.0) = 0;

		/**
		 * @brief Remove a connection with this object
		 *
		 * @param pObject the object to remove the connection with
		 */
		virtual pandora::StatusCode RemoveConnectionWith(ArborObject *pObject) = 0;

		/**
		 * @brief Return the connector list
		 */
		virtual ConnectorList &GetConnectors() = 0;

		/**
		 * @brief Return the list of backward connectors
		 */
		virtual ConnectorList &GetBackwardConnectorList() = 0;

		/**
		 * @brief Return the list of forward connectors
		 */
		virtual ConnectorList &GetForwardConnectorList() = 0;

		/**
		 * @brief Whether the object is isolated
		 */
		virtual bool IsIsolated() const = 0;

		/**
		 * @brief Set the object as isolated.
		 *
		 * @param boolean the isolation flag
		 */
		virtual void SetIsIsolated(bool boolean) = 0;

		/**
		 * @brief Return the granularity of the object
		 */
		virtual pandora::Granularity GetGranularity() const = 0;

		/**
		 * @brief Return the pseudo-layer associated to this object
		 */
		virtual pandora::PseudoLayer GetPseudoLayer() const = 0;

		/**
		 * @brief Set the current backward connector. This connector should </br>
		 * be unique in the arbor algorithm in order to build a tree.
		 *
		 * @param pConnector the current backward connector to set
		 */
		virtual pandora::StatusCode SetCurrentBackwardConnector(Connector *pConnector) = 0;

		/**
		 * @brief Return the current backward connector
		 */
		virtual pandora::StatusCode GetCurrentBackwardConnector(Connector *&pConnector) const = 0;

		/**
		 * @brief Sort the object by increasing position. Used for std::sort
		 */
		static bool SortByFromInnermostPosition(ArborObject *pObj1, ArborObject *pObj2);

		// friendship
		friend class ArborManager;
		friend class ArborObjectImpl;
};

//--------------------------------------------------------------------------------------------------------------------

inline static bool SortByFromInnermostPosition(ArborObject *pObj1, ArborObject *pObj2)
{
	const pandora::CartesianVector differenceVector = pObj2->GetPosition() - pObj1->GetPosition();
	float openingAngle = pObj1->GetPosition().GetOpeningAngle(differenceVector);
	return openingAngle < M_PI_2;
}

} 

#endif  //  ARBOROBJECT_H
