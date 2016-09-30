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

#include "AvailabilityManagerNightCycle.hpp"
#include "AvailabilityManagerNightCycle_Impl.hpp"
#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"
#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"
#include <utilities/idd/IddFactory.hxx>

#include <utilities/idd/OS_AvailabilityManager_NightCycle_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include "../utilities/units/Unit.hpp"
#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

namespace detail {

  AvailabilityManagerNightCycle_Impl::AvailabilityManagerNightCycle_Impl(const IdfObject& idfObject,
                                                                         Model_Impl* model,
                                                                         bool keepHandle)
    : AvailabilityManager_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == AvailabilityManagerNightCycle::iddObjectType());
  }

  AvailabilityManagerNightCycle_Impl::AvailabilityManagerNightCycle_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                         Model_Impl* model,
                                                                         bool keepHandle)
    : AvailabilityManager_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == AvailabilityManagerNightCycle::iddObjectType());
  }

  AvailabilityManagerNightCycle_Impl::AvailabilityManagerNightCycle_Impl(const AvailabilityManagerNightCycle_Impl& other,
                                                                         Model_Impl* model,
                                                                         bool keepHandle)
    : AvailabilityManager_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& AvailabilityManagerNightCycle_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType AvailabilityManagerNightCycle_Impl::iddObjectType() const {
    return AvailabilityManagerNightCycle::iddObjectType();
  }

  std::vector<ScheduleTypeKey> AvailabilityManagerNightCycle_Impl::getScheduleTypeKeys(const Schedule& schedule) const
  {
    std::vector<ScheduleTypeKey> result;
    return result;
  }

  std::string AvailabilityManagerNightCycle_Impl::controlType() const {
    boost::optional<std::string> value = getString(OS_AvailabilityManager_NightCycleFields::ControlType,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool AvailabilityManagerNightCycle_Impl::isControlTypeDefaulted() const {
    return isEmpty(OS_AvailabilityManager_NightCycleFields::ControlType);
  }

  double AvailabilityManagerNightCycle_Impl::thermostatTolerance() const {
    boost::optional<double> value = getDouble(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance,true);
    OS_ASSERT(value);
    return value.get();
  }

  Quantity AvailabilityManagerNightCycle_Impl::getThermostatTolerance(bool returnIP) const {
    OptionalDouble value = thermostatTolerance();
    OSOptionalQuantity result = getQuantityFromDouble(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance, value, returnIP);
    OS_ASSERT(result.isSet());
    return result.get();
  }

  bool AvailabilityManagerNightCycle_Impl::isThermostatToleranceDefaulted() const {
    return isEmpty(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance);
  }

  double AvailabilityManagerNightCycle_Impl::cyclingRunTime() const {
    boost::optional<double> value = getDouble(OS_AvailabilityManager_NightCycleFields::CyclingRunTime,true);
    OS_ASSERT(value);
    return value.get();
  }

  Quantity AvailabilityManagerNightCycle_Impl::getCyclingRunTime(bool returnIP) const {
    OptionalDouble value = cyclingRunTime();
    OSOptionalQuantity result = getQuantityFromDouble(OS_AvailabilityManager_NightCycleFields::CyclingRunTime, value, returnIP);
    OS_ASSERT(result.isSet());
    return result.get();
  }

  bool AvailabilityManagerNightCycle_Impl::isCyclingRunTimeDefaulted() const {
    return isEmpty(OS_AvailabilityManager_NightCycleFields::CyclingRunTime);
  }

  boost::optional<ThermalZone> AvailabilityManagerNightCycle_Impl::controlThermalZone() const {
    return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(OS_AvailabilityManager_NightCycleFields::ControlThermalZone);
  }

  bool AvailabilityManagerNightCycle_Impl::setControlType(std::string controlType) {
    bool result = setString(OS_AvailabilityManager_NightCycleFields::ControlType, controlType);
    return result;
  }

  void AvailabilityManagerNightCycle_Impl::resetControlType() {
    bool result = setString(OS_AvailabilityManager_NightCycleFields::ControlType, "");
    OS_ASSERT(result);
  }

  void AvailabilityManagerNightCycle_Impl::setThermostatTolerance(double thermostatTolerance) {
    bool result = setDouble(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance, thermostatTolerance);
    OS_ASSERT(result);
  }

  bool AvailabilityManagerNightCycle_Impl::setThermostatTolerance(const Quantity& thermostatTolerance) {
    OptionalDouble value = getDoubleFromQuantity(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance,thermostatTolerance);
    if (!value) {
      return false;
    }
    setThermostatTolerance(value.get());
    return true;
  }

  void AvailabilityManagerNightCycle_Impl::resetThermostatTolerance() {
    bool result = setString(OS_AvailabilityManager_NightCycleFields::ThermostatTolerance, "");
    OS_ASSERT(result);
  }

  void AvailabilityManagerNightCycle_Impl::setCyclingRunTime(double cyclingRunTime) {
    bool result = setDouble(OS_AvailabilityManager_NightCycleFields::CyclingRunTime, cyclingRunTime);
    OS_ASSERT(result);
  }

  bool AvailabilityManagerNightCycle_Impl::setCyclingRunTime(const Quantity& cyclingRunTime) {
    OptionalDouble value = getDoubleFromQuantity(OS_AvailabilityManager_NightCycleFields::CyclingRunTime,cyclingRunTime);
    if (!value) {
      return false;
    }
    setCyclingRunTime(value.get());
    return true;
  }

  void AvailabilityManagerNightCycle_Impl::resetCyclingRunTime() {
    bool result = setString(OS_AvailabilityManager_NightCycleFields::CyclingRunTime, "");
    OS_ASSERT(result);
  }

  bool AvailabilityManagerNightCycle_Impl::setControlThermalZone(const boost::optional<ThermalZone>& thermalZone) {
    bool result(false);
    if (thermalZone) {
      result = setPointer(OS_AvailabilityManager_NightCycleFields::ControlThermalZone, thermalZone.get().handle());
    }
    else {
      resetControlThermalZone();
      result = true;
    }
    return result;
  }

  void AvailabilityManagerNightCycle_Impl::resetControlThermalZone() {
    bool result = setString(OS_AvailabilityManager_NightCycleFields::ControlThermalZone, "");
    OS_ASSERT(result);
  }

  std::vector<std::string> AvailabilityManagerNightCycle_Impl::controlTypeValues() const {
    return AvailabilityManagerNightCycle::controlTypeValues();
  }

  openstudio::Quantity AvailabilityManagerNightCycle_Impl::thermostatTolerance_SI() const {
    return getThermostatTolerance(false);
  }

  openstudio::Quantity AvailabilityManagerNightCycle_Impl::thermostatTolerance_IP() const {
    return getThermostatTolerance(true);
  }

  openstudio::Quantity AvailabilityManagerNightCycle_Impl::cyclingRunTime_SI() const {
    return getCyclingRunTime(false);
  }

  openstudio::Quantity AvailabilityManagerNightCycle_Impl::cyclingRunTime_IP() const {
    return getCyclingRunTime(true);
  }

  boost::optional<ModelObject> AvailabilityManagerNightCycle_Impl::controlThermalZoneAsModelObject() const {
    OptionalModelObject result;
    OptionalThermalZone intermediate = controlThermalZone();
    if (intermediate) {
      result = *intermediate;
    }
    return result;
  }

  bool AvailabilityManagerNightCycle_Impl::setControlThermalZoneAsModelObject(const boost::optional<ModelObject>& modelObject) {
    if (modelObject) {
      OptionalThermalZone intermediate = modelObject->optionalCast<ThermalZone>();
      if (intermediate) {
        ThermalZone thermalZone(*intermediate);
        return setControlThermalZone(thermalZone);
      }
      else {
        return false;
      }
    }
    else {
      resetControlThermalZone();
    }
    return true;
  }

} // detail

AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(const Model& model)
  : AvailabilityManager(AvailabilityManagerNightCycle::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::AvailabilityManagerNightCycle_Impl>());
  setThermostatTolerance(1.0);
  setCyclingRunTime(3600);
}

IddObjectType AvailabilityManagerNightCycle::iddObjectType() {
  return IddObjectType(IddObjectType::OS_AvailabilityManager_NightCycle);
}

std::vector<std::string> AvailabilityManagerNightCycle::controlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_AvailabilityManager_NightCycleFields::ControlType);
}

std::string AvailabilityManagerNightCycle::controlType() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->controlType();
}

bool AvailabilityManagerNightCycle::isControlTypeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isControlTypeDefaulted();
}

double AvailabilityManagerNightCycle::thermostatTolerance() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->thermostatTolerance();
}

Quantity AvailabilityManagerNightCycle::getThermostatTolerance(bool returnIP) const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->getThermostatTolerance(returnIP);
}

bool AvailabilityManagerNightCycle::isThermostatToleranceDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isThermostatToleranceDefaulted();
}

double AvailabilityManagerNightCycle::cyclingRunTime() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->cyclingRunTime();
}

Quantity AvailabilityManagerNightCycle::getCyclingRunTime(bool returnIP) const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->getCyclingRunTime(returnIP);
}

bool AvailabilityManagerNightCycle::isCyclingRunTimeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isCyclingRunTimeDefaulted();
}

boost::optional<ThermalZone> AvailabilityManagerNightCycle::controlThermalZone() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->controlThermalZone();
}

bool AvailabilityManagerNightCycle::setControlType(std::string controlType) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setControlType(controlType);
}

void AvailabilityManagerNightCycle::resetControlType() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetControlType();
}

void AvailabilityManagerNightCycle::setThermostatTolerance(double thermostatTolerance) {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setThermostatTolerance(thermostatTolerance);
}

bool AvailabilityManagerNightCycle::setThermostatTolerance(const Quantity& thermostatTolerance) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setThermostatTolerance(thermostatTolerance);
}

void AvailabilityManagerNightCycle::resetThermostatTolerance() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetThermostatTolerance();
}

void AvailabilityManagerNightCycle::setCyclingRunTime(double cyclingRunTime) {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setCyclingRunTime(cyclingRunTime);
}

bool AvailabilityManagerNightCycle::setCyclingRunTime(const Quantity& cyclingRunTime) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setCyclingRunTime(cyclingRunTime);
}

void AvailabilityManagerNightCycle::resetCyclingRunTime() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetCyclingRunTime();
}

bool AvailabilityManagerNightCycle::setControlThermalZone(const ThermalZone& thermalZone) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setControlThermalZone(thermalZone);
}

void AvailabilityManagerNightCycle::resetControlThermalZone() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetControlThermalZone();
}

/// @cond
AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl)
  : AvailabilityManager(impl)
{}
/// @endcond

} // model
} // openstudio

