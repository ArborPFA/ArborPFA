/*
 *
 * ArborApiImpl.h header template automatically generated by a class generator
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


#ifndef ARBORAPIIMPL_H
#define ARBORAPIIMPL_H

#include "Pandora/PandoraInputTypes.h"
#include "Pandora/PandoraInternal.h"

#include "arborpfa/arbor/ArborTypes.h"

namespace pandora
{
	class Pandora;
}

namespace arbor
{

class Arbor;
class ArborAlgorithmFactory;
class IEnergyFunction;

/** 
 * @brief ArborApiImpl class
 */ 
class ArborApiImpl 
{
 public:

		/**
		 *
		 */
		pandora::StatusCode PrepareEvent() const;

		/**
		 *
		 */
		pandora::StatusCode RegisterArborAlgorithms(Arbor &arbor) const;

		/**
		 *
		 */
		pandora::StatusCode RegisterArborPlugins(Arbor &arbor) const;

		/**
			*
			*/
		pandora::StatusCode RegisterAlgorithmFactory(Arbor &pArbor, const std::string &factoryName, ArborAlgorithmFactory *pFactory) const;

		/**
		 *  @brief  Register an energy function
		 *
		 *  @param  arbor the Arbor instance
		 *  @param  energyFunctionName the energy function name
		 *  @param  pEnergyFunction the energy function ptr to register
		 */
		pandora::StatusCode RegisterEnergyFunction(Arbor &arbor, const std::string &energyFunctionName, IEnergyFunction *pEnergyFunction) const;

	 /**
	  *
	  */
	 pandora::StatusCode ResetEvent() const;


 protected:

 /**
  * @brief Constructor
  */
  ArborApiImpl(Arbor *pArbor);

  Arbor      *m_pArbor;

  friend class Arbor;
}; 

} 

#endif  //  ARBORAPIIMPL_H
