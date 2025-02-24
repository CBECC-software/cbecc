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

#ifndef MODEL_LIGHTS_HPP
#define MODEL_LIGHTS_HPP

#include "ModelAPI.hpp"
#include "SpaceLoadInstance.hpp"

namespace openstudio {
namespace model {

  class Schedule;
  class LightsDefinition;

  namespace detail {

    class Lights_Impl;

  }  // namespace detail

  /** Lights is a SpaceLoadInstance that wraps the OpenStudio IDD object 'OS:Lights'.
 *  \sa LightsDefinition */
  class MODEL_API Lights : public SpaceLoadInstance
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit Lights(const LightsDefinition& lightsDefinition);

    virtual ~Lights() {}

    //@}

    static IddObjectType iddObjectType();

    /** @name Getters */
    //@{

    /** Gets the LightsDefinition object. */
    LightsDefinition lightsDefinition() const;

    /** Returns the (fractional) lighting schedule.  If this object does not
   *  specify a schedule this function will search the hierarchy. */
    boost::optional<Schedule> schedule() const;

    /** Returns true if this object does not specify a schedule directly. */
    bool isScheduleDefaulted() const;

    double fractionReplaceable() const;

    bool isFractionReplaceableDefaulted() const;

    std::string endUseSubcategory() const;

    bool isEndUseSubcategoryDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    /** Sets the LightsDefinition object. */
    bool setLightsDefinition(const LightsDefinition& definition);

    /** Sets the (fractional) Schedule. */
    bool setSchedule(Schedule& schedule);

    /** Resets the (fractional) Schedule. */
    void resetSchedule();

    bool setFractionReplaceable(double fractionReplaceable);

    void resetFractionReplaceable();

    bool setMultiplier(double multiplier);

    void resetMultiplier();

    bool setEndUseSubcategory(std::string endUseSubcategory);

    void resetEndUseSubcategory();

    //@}
    /** @name Other */
    //@{

    /** Returns the lightingLevel if possible based on the underlying data of
   *  lightsDefinition(). */
    boost::optional<double> lightingLevel() const;

    /** Returns the powerPerFloorArea if possible based on the underlying data of
   *  lightsDefinition(). */
    boost::optional<double> powerPerFloorArea() const;

    /** Returns the powerPerPerson if possible based on the underlying data of
   *  lightsDefinition(). */
    boost::optional<double> powerPerPerson() const;

    /** Returns the lighting level represented by this instance, assuming floorArea (m^2) and
   *  numPeople. */
    double getLightingPower(double floorArea, double numPeople) const;

    /** Returns the watts/m^2 represented by this instance, assuming floorArea (m^2) and
   *  numPeople. */
    double getPowerPerFloorArea(double floorArea, double numPeople) const;

    /** Returns the watts/person represented by this instance, assuming floorArea (m^2) and
   *  numPeople. */
    double getPowerPerPerson(double floorArea, double numPeople) const;

    //@}
   protected:
    /// @cond
    typedef detail::Lights_Impl ImplType;

    friend class Model;
    friend class openstudio::IdfObject;

    explicit Lights(std::shared_ptr<detail::Lights_Impl> impl);

    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.Lights");
  };

  /** \relates Lights*/
  typedef boost::optional<Lights> OptionalLights;

  /** \relates Lights*/
  typedef std::vector<Lights> LightsVector;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_LIGHTS_HPP
