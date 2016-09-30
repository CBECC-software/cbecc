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

#ifndef UTILITIES_IDD_SETPOINTMANAGER_CONDENSERENTERINGRESET_IDEAL_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_CONDENSERENTERINGRESET_IDEAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_CondenserEnteringReset_IdealFields
 *  \brief Enumeration of SetpointManager:CondenserEnteringReset:Ideal's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_CondenserEnteringReset_IdealFields, )
#else
class SetpointManager_CondenserEnteringReset_IdealFields: public ::EnumBase<SetpointManager_CondenserEnteringReset_IdealFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, MinimumLift, MaximumCondenserEnteringWaterTemperature, SetpointNodeorNodeListName,   };
  SetpointManager_CondenserEnteringReset_IdealFields()
   : EnumBase<SetpointManager_CondenserEnteringReset_IdealFields>(Name) {} 
  SetpointManager_CondenserEnteringReset_IdealFields(const std::string &t_name) 
   : EnumBase<SetpointManager_CondenserEnteringReset_IdealFields>(t_name) {} 
  SetpointManager_CondenserEnteringReset_IdealFields(int t_value) 
   : EnumBase<SetpointManager_CondenserEnteringReset_IdealFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_CondenserEnteringReset_IdealFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_CondenserEnteringReset_IdealFields>::value()); }
   private:
    friend class EnumBase<SetpointManager_CondenserEnteringReset_IdealFields>;
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
{ SetpointManager_CondenserEnteringReset_IdealFields::Name, "Name", "Name"},
{ SetpointManager_CondenserEnteringReset_IdealFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_CondenserEnteringReset_IdealFields::MinimumLift, "MinimumLift", "Minimum Lift"},
{ SetpointManager_CondenserEnteringReset_IdealFields::MaximumCondenserEnteringWaterTemperature, "MaximumCondenserEnteringWaterTemperature", "Maximum Condenser Entering Water Temperature"},
{ SetpointManager_CondenserEnteringReset_IdealFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_CondenserEnteringReset_IdealFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_CondenserEnteringReset_IdealFields> OptionalSetpointManager_CondenserEnteringReset_IdealFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_CONDENSERENTERINGRESET_IDEAL_FIELDENUMS_HXX
