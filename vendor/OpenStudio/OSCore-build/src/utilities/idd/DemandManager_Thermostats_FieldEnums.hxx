/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_ThermostatsFields
 *  \brief Enumeration of DemandManager:Thermostats's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_ThermostatsFields, )
#else
class DemandManager_ThermostatsFields: public ::EnumBase<DemandManager_ThermostatsFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ResetControl, MinimumResetDuration, MaximumHeatingSetpointReset, MaximumCoolingSetpointReset, ResetStepChange, SelectionControl, RotationDuration,   };
  DemandManager_ThermostatsFields()
   : EnumBase<DemandManager_ThermostatsFields>(Name) {} 
  DemandManager_ThermostatsFields(const std::string &t_name) 
   : EnumBase<DemandManager_ThermostatsFields>(t_name) {} 
  DemandManager_ThermostatsFields(int t_value) 
   : EnumBase<DemandManager_ThermostatsFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ThermostatsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ThermostatsFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ThermostatsFields>;
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
{ DemandManager_ThermostatsFields::Name, "Name", "Name"},
{ DemandManager_ThermostatsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_ThermostatsFields::ResetControl, "ResetControl", "Reset Control"},
{ DemandManager_ThermostatsFields::MinimumResetDuration, "MinimumResetDuration", "Minimum Reset Duration"},
{ DemandManager_ThermostatsFields::MaximumHeatingSetpointReset, "MaximumHeatingSetpointReset", "Maximum Heating Setpoint Reset"},
{ DemandManager_ThermostatsFields::MaximumCoolingSetpointReset, "MaximumCoolingSetpointReset", "Maximum Cooling Setpoint Reset"},
{ DemandManager_ThermostatsFields::ResetStepChange, "ResetStepChange", "Reset Step Change"},
{ DemandManager_ThermostatsFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_ThermostatsFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ThermostatsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ThermostatsFields> OptionalDemandManager_ThermostatsFields ;
#endif

/** \class DemandManager_ThermostatsExtensibleFields
 *  \brief Enumeration of DemandManager:Thermostats's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_ThermostatsExtensibleFields, )
#else
class DemandManager_ThermostatsExtensibleFields: public ::EnumBase<DemandManager_ThermostatsExtensibleFields> {
 public: 
  enum domain 
  {
ThermostatName,   };
  DemandManager_ThermostatsExtensibleFields()
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(ThermostatName) {} 
  DemandManager_ThermostatsExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(t_name) {} 
  DemandManager_ThermostatsExtensibleFields(int t_value) 
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ThermostatsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ThermostatsExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ThermostatsExtensibleFields>;
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
{ DemandManager_ThermostatsExtensibleFields::ThermostatName, "ThermostatName", "Thermostat Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ThermostatsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ThermostatsExtensibleFields> OptionalDemandManager_ThermostatsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX
