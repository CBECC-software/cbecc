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

#ifndef UTILITIES_IDD_CONTROLLER_WATERCOIL_FIELDENUMS_HXX
#define UTILITIES_IDD_CONTROLLER_WATERCOIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Controller_WaterCoilFields
 *  \brief Enumeration of Controller:WaterCoil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Controller_WaterCoilFields, )
#else
class Controller_WaterCoilFields: public ::EnumBase<Controller_WaterCoilFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, Action, ActuatorVariable, SensorNodeName, ActuatorNodeName, ControllerConvergenceTolerance, MaximumActuatedFlow, MinimumActuatedFlow,   };
  Controller_WaterCoilFields()
   : EnumBase<Controller_WaterCoilFields>(Name) {} 
  Controller_WaterCoilFields(const std::string &t_name) 
   : EnumBase<Controller_WaterCoilFields>(t_name) {} 
  Controller_WaterCoilFields(int t_value) 
   : EnumBase<Controller_WaterCoilFields>(t_value) {} 
  static std::string enumName() 
  { return "Controller_WaterCoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Controller_WaterCoilFields>::value()); }
   private:
    friend class EnumBase<Controller_WaterCoilFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ Controller_WaterCoilFields::Name, "Name", "Name"},
{ Controller_WaterCoilFields::ControlVariable, "ControlVariable", "Control Variable"},
{ Controller_WaterCoilFields::Action, "Action", "Action"},
{ Controller_WaterCoilFields::ActuatorVariable, "ActuatorVariable", "Actuator Variable"},
{ Controller_WaterCoilFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ Controller_WaterCoilFields::ActuatorNodeName, "ActuatorNodeName", "Actuator Node Name"},
{ Controller_WaterCoilFields::ControllerConvergenceTolerance, "ControllerConvergenceTolerance", "Controller Convergence Tolerance"},
{ Controller_WaterCoilFields::MaximumActuatedFlow, "MaximumActuatedFlow", "Maximum Actuated Flow"},
{ Controller_WaterCoilFields::MinimumActuatedFlow, "MinimumActuatedFlow", "Minimum Actuated Flow"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const Controller_WaterCoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Controller_WaterCoilFields> OptionalController_WaterCoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONTROLLER_WATERCOIL_FIELDENUMS_HXX
