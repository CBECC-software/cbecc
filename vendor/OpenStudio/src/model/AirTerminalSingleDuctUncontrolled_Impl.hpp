/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_AIRTERMINALSINGLEDUCTUNCONTROLLED_IMPL_HPP
#define MODEL_AIRTERMINALSINGLEDUCTUNCONTROLLED_IMPL_HPP

#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {

namespace detail {

  class MODEL_API AirTerminalSingleDuctUncontrolled_Impl : public StraightComponent_Impl {
    Q_OBJECT;

    Q_PROPERTY(boost::optional<openstudio::model::ModelObject> availabilitySchedule READ availabilityScheduleAsModelObject WRITE setAvailabilityScheduleAsModelObject);
   public:
    /** @name Constructors and Destructors */
    //@{

    // constructor
    AirTerminalSingleDuctUncontrolled_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    // construct from workspace
    AirTerminalSingleDuctUncontrolled_Impl(const openstudio::detail::WorkspaceObject_Impl& other, 
                                           Model_Impl* model, 
                                           bool keepHandle);

    // copy constructor
    AirTerminalSingleDuctUncontrolled_Impl(const AirTerminalSingleDuctUncontrolled_Impl& other, 
                                           Model_Impl* model, 
                                           bool keepHandle);

    // virtual destructor
    virtual ~AirTerminalSingleDuctUncontrolled_Impl(){}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual std::vector<openstudio::IdfObject> remove() override;

    virtual bool isRemovable() const override;

    // Get all output variable names that could be associated with this object.
    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

    virtual unsigned inletPort() override;

    virtual unsigned outletPort() override;

    virtual bool addToNode(Node & node) override;

    //@}
    
    /** Returns the Schedule referred to by the AvailabilityScheduleName field. **/
    Schedule availabilitySchedule() const;

    /** Sets the Schedule referred to by the AvailabilityScheduleName field. **/
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumAirFlowRate() const;

    OSOptionalQuantity getMaximumAirFlowRate(bool returnIP=false) const;

    bool isMaximumAirFlowRateAutosized() const;

    bool setMaximumAirFlowRate(boost::optional<double> maximumAirFlowRate);

    bool setMaximumAirFlowRate(const OSOptionalQuantity& maximumAirFlowRate);

    void autosizeMaximumAirFlowRate();

   private:

    REGISTER_LOGGER("openstudio.model.AirTerminalSingleDuctUncontrolled");

    // Optional getters for use by methods like children() so can remove() if the constructor fails.
    // There are other ways for the public versions of these getters to fail--perhaps all required
    // objects should be returned as boost::optionals
    boost::optional<Schedule> optionalAvailabilitySchedule() const;

    boost::optional<ModelObject> availabilityScheduleAsModelObject() const;

    bool setAvailabilityScheduleAsModelObject(const boost::optional<ModelObject>& modelObject);
  };

} // detail

} // model
} // openstudio

#endif // MODEL_AIRTERMINALSINGLEDUCTUNCONTROLLED_IMPL_HPP
