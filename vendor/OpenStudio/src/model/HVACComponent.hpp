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

#ifndef MODEL_HVACCOMPONENT_HPP
#define MODEL_HVACCOMPONENT_HPP

#include "ModelAPI.hpp"
#include "ParentObject.hpp"

namespace openstudio {

namespace model {

  class AirLoopHVAC;

  class AirLoopHVACOutdoorAirSystem;

  class PlantLoop;

  class Node;

  class Splitter;

  class Loop;

  class ZoneHVACComponent;

  class StraightComponent;

  namespace detail {
    class HVACComponent_Impl;
  };

  /** HVACComponent is the base class for objects related to HVAC systems.
 *
 *  HVACComponent provides the ability to connect multiple HVACComponents together through ports.
 *  Connections are directional and they are created by identifying a source HVACComponent and port
 *  as well as a target HVACComponent object and port.  Once a connection is made, it is easy to access the HVACComponent
 *  connected to a particular port using the member functions of HVACComponent.
 *
 *  New Connections are made using the openstudio::model::Model::connect function.
 *
 *  Connections and ports together form similar functionality as EnergyPlus nodes, however a connection between ports is more general
 *  then a node connection in Energyplus.  Indeed, in the OpenStudio model connections are used to describe what is a node connection
 *  in EnergyPlus, but connections can be applied to other contexts then just EnergyPlus nodes.  OpenStudio's connections and ports
 *  can be used anytime one "component" can be arbitrarily connected to another "component".  For example EnergyPlus EMS sensors and
 *  actuaters could be thought of as source and target ports, where a connection can be made between the two.
 *
 */

  class MODEL_API HVACComponent : public ParentObject
  {
   public:
    virtual ~HVACComponent() {}

    /** Returns the optional Loop object that the HVAC component is attached to.
   *  If the component is part of an outdoor air system, the containing AirLoopHVAC will be returned.
   *  If the component is attached to multiple loops, the optional will be false.
   */
    boost::optional<Loop> loop() const;

    /** Returns the optional AirLoopHVAC object that the HVAC component is attached to.
   *  If the component is part of an outdoor air system, the containing AirLoopHVAC will be returned.
   *  If the HVAC component is not associated with an air loop then the optional will be false.
   */
    boost::optional<AirLoopHVAC> airLoopHVAC() const;

    /** Returns the optional PlantLoop object that the HVAC component is attached to.
   *
   *  If the HVAC component is not associated with a plant loop then the optional will be false.
   */
    boost::optional<PlantLoop> plantLoop() const;

    /** Returns the optional AirLoopHVACOutdoorAirSystem that the HVAC component is attached to.
   *
   *  If the HVAC component is not associated with an outdoor air system then the optional will be false.
   */
    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

    /** EnergyPlus unitary equipment and air terminals are typically composed of other HVAC components.
   *  This method returns any such component containing this component.  In OpenStudio, AirLoopHVAC,
   *  PlantLoop, and AirLoopHVACOutdoorAirSystem are treated as systems, not unitary equipment, thus
   *  they are not returned by this method.  See plantLoop(), airLoop(), and airLoopHVACOutdoorAirSystem()
   *  to access those systems.
   */
    boost::optional<HVACComponent> containingHVACComponent() const;

    /** Returns any ZoneHVACComponent that contains this HVACComponent.
   */
    boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;
    boost::optional<StraightComponent> containingStraightComponent() const;

    /** Adds this object to a new system node and returns a boolean indicating if the addition was successful.
   *
   *  This method is reimplemented in many of the derived classes to do the right thing based on the
   *  context of the node a particular object is added to.  For example if a specific HVACComoponent is not allowed
   *  on an air loop and this interface is used to attempt to add the HVAC component to a node on an
   *  air loop the method will return false and the object will not be added.
   *
   *  Normally, this method will add this HVAC component immediatly after the node specified.  There are exceptions,
   *  such as when a component is dropped on an outlet node such as the supply outlet node of an air loop.  In
   *  this case the method will do the only thing possible and add this component before the outlet node.
   */
    bool addToNode(Node& node);

    /** Adds this object to a splitter by creating a new branch.
   *  Returns true if the operation was succesfull.
   *
   *  This method is reimplemented in many of the derived class to do the right thing based on the
   *  context of the splitter a particular object is added to.
   */
    bool addToSplitter(Splitter& splitter);

    /** Removes all connections to other HVACComponent objects
   */
    void disconnect();

    /** Indicates if the HVACComponent can be removed from the model.
   *  One reason a component could not be removed is because it is attached to a loop and
   *  removing it would destroy the integrity of the loop.  Zone splitters and mixers are
   *  examples of this, since they are required components of an air loop.  In such a case,
   *  the HVACComponent must be disconnected before it can be removed.
   */
    bool isRemovable() const;

    /** Removes the HVACComponent from the model only if isRemovable() return true.
   */
    std::vector<IdfObject> remove();

    ///** Returns the optional ModelObject connected to this object's port.  **/
    //virtual boost::optional<ModelObject> connectedObject(unsigned port);

    ///** Returns the optional Port on the connected object through which the
    // *  connection to this object's port is made.
    // */
    //virtual boost::optional<unsigned> connectedObjectPort(unsigned port);

    void autosize();

    void applySizingValues();

   protected:
    HVACComponent(IddObjectType type, const Model& model);

    typedef detail::HVACComponent_Impl ImplType;

    friend class Model;

    friend class openstudio::IdfObject;

    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACComponent(std::shared_ptr<ImplType> impl);

    virtual std::vector<ModelObject> children() const;

   private:
    REGISTER_LOGGER("openstudio.model.HVACComponent");
  };

  typedef boost::optional<HVACComponent> OptionalHVACComponent;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HVACCOMPONENT_HPP
