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

#ifndef MODEL_MODELOBJECT_HPP
#define MODEL_MODELOBJECT_HPP

#include "ModelAPI.hpp"

#include "../utilities/idf/WorkspaceObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include "../utilities/core/Logger.hpp"

#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <set>

namespace openstudio {

class Attribute;
class TimeSeries;

class ModelObjectSelectorView;

namespace model {

  class Model;
  class Component;
  class LifeCycleCost;

  class ModelExtensibleGroup;

  class ParentObject;
  class ResourceObject;

  class Schedule;

  class OutputVariable;
  class OutputMeterMeter;
  class Connection;

  class AdditionalProperties;

  namespace detail {
    class Model_Impl;
    class ModelObject_Impl;
  }  // namespace detail

  // Defined later in this file
  class EMSActuatorNames;
  class ScheduleTypeKey;

  /** Base class for the OpenStudio %Building %Model hierarchy. Derives from
 *  %WorkspaceObject, just as Model derives from Workspace. Each concrete class in the hierarchy
 *  wraps a specific IddObject. (See the OpenStudio Utilities and Utilities Idd documentation for
 *  information on Workspace, %WorkspaceObject, and IddObject.) */
  class MODEL_API ModelObject : public openstudio::WorkspaceObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{
    virtual ~ModelObject() {}

    /** Creates a deep copy of this object, placing it in this object's model(). Virtual
   *  implementation. */
    ModelObject clone() const;

    /** Creates a deep copy of this object, placing it in model. Virtual implementation. */
    ModelObject clone(Model model) const;

    //@}
    /** @name Components
   *
   *  Once a Component has been created, it can be saved to local and online %Building %Component
   *  Libraries (BCLs) for web-enabled storing and sharing. (At this time, only select BCL users
   *  have permissions to upload, but this capability is to be extended to all users in time.)
   *  Components are the preferred method for specifying and swapping out
   *  groups of related ModelObjects (e.g. constructions, schedules, etc.) in higher-level
   *  libraries such as standardsinterface and analysis. */
    //@{

    /** Method for creating sharable Model snippets. Creates a Component with this ModelObject as
   *  the primary object. Uses the clone(Model&) method to select Component contents. */
    Component createComponent() const;

    //@}
    /** @name Getters */
    //@{

    /** Returns the Model that contains this object. */
    Model model() const;

    /** Return this object's parent in the hierarchy, if it has one */
    boost::optional<ParentObject> parent() const;

    /** Get the resources directly used by this ModelObject. */
    std::vector<ResourceObject> resources() const;

    /** Get all objects of type T that point to this object. This method is preferred over the
   *  WorkspaceObject equivalent, as its use does not require knowledge of the IddObjectType. */
    template <typename T>
    std::vector<T> getModelObjectSources() const {
      std::vector<T> result;
      std::vector<WorkspaceObject> wos = sources();
      for (const WorkspaceObject& wo : wos) {
        boost::optional<T> oSource = wo.optionalCast<T>();
        if (oSource) {
          result.push_back(*oSource);
        }
      }
      return result;
    }

    /** Get all objects of type T that point to this object. Preferred usage (do not use with
   *  abstract classes):
   *
   *  \code
   *  PeopleVector myZonesPeople = zone.getModelObjectSources<People>(People::iddObjectType());

   *  \endcode */
    template <typename T>
    std::vector<T> getModelObjectSources(IddObjectType iddObjectType) const {
      std::vector<T> result;
      std::vector<WorkspaceObject> wos = getSources(iddObjectType);
      for (const WorkspaceObject& wo : wos) {
        // assume iddObjectType is valid for T
        result.push_back(wo.cast<T>());
      }
      return result;
    }

    /** Get the object of type T pointed to by this object from field index. */
    template <typename T>
    boost::optional<T> getModelObjectTarget(unsigned index) const {
      boost::optional<T> result;
      boost::optional<WorkspaceObject> oCandidate = getTarget(index);
      if (oCandidate) {
        result = oCandidate->optionalCast<T>();
      }
      return result;
    }

    /** Get all objects of type T to which this object points. This method is preferred over the
   *  WorkspaceObject equivalent, as its use does not require knowledge of the IddObjectType. */
    template <typename T>
    std::vector<T> getModelObjectTargets() const {
      std::vector<T> result;
      std::vector<WorkspaceObject> wos = targets();
      for (const WorkspaceObject& wo : wos) {
        boost::optional<T> oTarget = wo.optionalCast<T>();
        if (oTarget) {
          result.push_back(*oTarget);
        }
      }
      return result;
    }

    /** Get all output variables names that could be associated with this object. These variables
   *   may or may not be available for each simulation, need to check report variable dictionary
   *   to see if the variable is available. Each concrete class should override this method.*/
    const std::vector<std::string>& outputVariableNames() const;

    /** Get all output variables associated with this object, must run simulation to generate data. */
    std::vector<OutputVariable> outputVariables() const;

    /** Get data associated with this output variable and this object. */
    boost::optional<openstudio::TimeSeries> getData(const OutputVariable& variable, const std::string& envPeriod) const;

    /** Returns the list of all LifeCycleCosts that refer to this object.
   */
    std::vector<LifeCycleCost> lifeCycleCosts() const;

    /** Removes all LifeCycleCosts that refer to this object. Returns removed objects.
   */
    std::vector<IdfObject> removeLifeCycleCosts();

    /** This is a virtual function that will tell you the type of iddObject you
   * are dealing with. While not labeled virtual here, it IS virtual in the
   * impl.
   */
    IddObjectType iddObjectType() const;

    /** Returns this object's additional properties, constructing a new object if necessary.
  *   This method will throw if called on an AddditionalProperties object. */
    AdditionalProperties additionalProperties() const;

    /** Returns true if this object has additional properties. */
    bool hasAdditionalProperties() const;

    /** Removes all additional properties that refer to this object. Returns removed objects. */
    std::vector<IdfObject> removeAdditionalProperties();

    //@}
    /** @name Setters */
    //@{

    /// set the parent, child may have to call non-const methods on the parent
    bool setParent(ParentObject& newParent);

    //@}
    /** @name Queries */
    //@{

    bool operator<(const ModelObject& right) const;

    /// equality test
    bool operator==(const ModelObject& other) const;

    /// inequality test
    bool operator!=(const ModelObject& other) const;

    /** Return the ScheduleTypeKeys indicating how schedule is used in this object. If schedule is not directly
   *  used by this object, return value will be .empty(). Used to maintain compatibility between schedule's
   *  ScheduleTypeLimits and how schedule is used by other objects. */
    std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const;

    /** Gets the autosized component value from the sql file **/
    boost::optional<double> getAutosizedValue(std::string valueName, std::string unitString) const;

    /** Return the names of the available ems actuators.
  */
    virtual std::vector<EMSActuatorNames> emsActuatorNames() const;

    /** Return the names of the available ems internal variables.
  */
    virtual std::vector<std::string> emsInternalVariableNames() const;

    //@}
    /** @name HVAC System Connections */
    //@{

    // DLM@20100716: should this stay in ModelObject
    boost::optional<ModelObject> connectedObject(unsigned port) const;

    // DLM@20100716: should this stay in ModelObject
    boost::optional<unsigned> connectedObjectPort(unsigned port) const;

    //@}
   protected:
    typedef detail::ModelObject_Impl ImplType;

    friend class openstudio::IdfObject;
    friend class openstudio::IdfExtensibleGroup;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::ModelObject_Impl;
    friend class openstudio::ModelObjectSelectorView;

    friend class Model;
    friend class ModelExtensibleGroup;

    friend class Attribute;

    // constructor
    explicit ModelObject(IddObjectType type, const Model& model, bool fastName = false);

    // constructor
    explicit ModelObject(std::shared_ptr<detail::ModelObject_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.model.ModelObject");
  };

  class MODEL_API EMSActuatorNames
  {
   public:
    EMSActuatorNames(const std::string& componentTypeName, const std::string& controlTypeName);

    std::string controlTypeName() const;
    std::string componentTypeName() const;

   private:
    std::string m_componentTypeName;
    std::string m_controlTypeName;
  };

  /** Simple class for ScheduleTypeRegistry key. \relates ModelObject */
  class MODEL_API ScheduleTypeKey
  {
   public:
    ScheduleTypeKey(const std::string& className, const std::string& scheduleDisplayName);

    std::string className() const;
    std::string scheduleDisplayName() const;

   private:
    std::string m_className;
    std::string m_scheduleDisplayName;
  };

  /// optional ModelObject
  typedef boost::optional<ModelObject> OptionalModelObject;

  /// vector of ModelObject
  typedef std::vector<ModelObject> ModelObjectVector;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_MODELOBJECT_HPP
