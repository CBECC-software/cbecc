/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef MODEL_SPACELOADDEFINITION_HPP
#define MODEL_SPACELOADDEFINITION_HPP

#include "ModelAPI.hpp"
#include "ResourceObject.hpp"

namespace openstudio {
namespace model {

  class SpaceLoadInstance;

  namespace detail {
    class SpaceLoadDefinition_Impl;
  }

  /** SpaceLoadDefinition is an abstract class derived from ResourceObject. \link SpaceLoadDefinition
 *  SpaceLoadDefinitions \endlink describe internal loads in a generic way that can be used by
 *  multiple \link Space Spaces \endlink or \link SpaceType SpaceTypes \endlink. For instance, a
 *  LightsDefinition might define the appropriate amount of task lighting for a workstation in
 *  W/person, or an ElectricEquipmentDefinition might define a coffee maker in terms of its maximum
 *  power draw (W). Multipliers and schedules are defined by the corresponding SpaceLoadInstance
 *  objects. (Different usage patterns of the same amount of task lighting, or different numbers of
 *  coffee makers, can be defined on a space-by-space basis, for instance.)
 */
  class MODEL_API SpaceLoadDefinition : public ResourceObject
  {
   public:
    virtual ~SpaceLoadDefinition() {}

    /** Returns all instances of this definition. */
    std::vector<SpaceLoadInstance> instances() const;

    // ETH@20140113 - No units mark-up here. What is the pattern we are trying to move toward?
    // (Programmatically available, but string-based, right?)

    /** Returns the floor area associated with instances of this space load definition.
  If two instances are in the same space then that floor area will be double counted.
  If two instances used in the same space type then that floor area will be double counted.
  Space and SpaceLoadInstance multipliers are included in the result. **/
    double floorArea() const;

    /** Returns the number of instances of this space load.
  Space and SpaceLoadInstance multipliers are included in the result **/
    int quantity() const;

   protected:
    /** @name Constructors and Destructors */
    //@{

    /// Constructs a new SpaceLoadDefinition object in the model.
    SpaceLoadDefinition(IddObjectType type, const Model& model);

    //@}

    /// @cond

    typedef detail::SpaceLoadDefinition_Impl ImplType;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class detail::SpaceLoadDefinition_Impl;

    explicit SpaceLoadDefinition(std::shared_ptr<detail::SpaceLoadDefinition_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.model.SpaceLoadDefinition");

    /// @endcond
  };

  /** \relates SpaceLoadDefinition */
  typedef boost::optional<SpaceLoadDefinition> OptionalSpaceLoadDefinition;

  /** \relates SpaceLoadDefinition */
  typedef std::vector<SpaceLoadDefinition> SpaceLoadDefinitionVector;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_SPACELOADDEFINITION_HPP
