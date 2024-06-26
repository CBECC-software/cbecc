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

#ifndef UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneMixingFields
 *  \brief Enumeration of OS:ZoneMixing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneMixingFields, )
#else
class OS_ZoneMixingFields: public ::EnumBase<OS_ZoneMixingFields> {
 public: 
  enum domain 
  {
Handle, Name, ZoneName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperZoneFloorArea, FlowRateperPerson, AirChangesperHour, SourceZoneName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumZoneTemperatureScheduleName, MaximumZoneTemperatureScheduleName, MinimumSourceZoneTemperatureScheduleName, MaximumSourceZoneTemperatureScheduleName, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperatureScheduleName,   };
  OS_ZoneMixingFields()
   : EnumBase<OS_ZoneMixingFields>(Handle) {} 
  OS_ZoneMixingFields(const std::string &t_name) 
   : EnumBase<OS_ZoneMixingFields>(t_name) {} 
  OS_ZoneMixingFields(int t_value) 
   : EnumBase<OS_ZoneMixingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneMixingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneMixingFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneMixingFields>;
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
{ OS_ZoneMixingFields::Handle, "Handle", "Handle"},
{ OS_ZoneMixingFields::Name, "Name", "Name"},
{ OS_ZoneMixingFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_ZoneMixingFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ZoneMixingFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ OS_ZoneMixingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_ZoneMixingFields::FlowRateperZoneFloorArea, "FlowRateperZoneFloorArea", "Flow Rate per Zone Floor Area"},
{ OS_ZoneMixingFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ OS_ZoneMixingFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ OS_ZoneMixingFields::SourceZoneName, "SourceZoneName", "Source Zone Name"},
{ OS_ZoneMixingFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ OS_ZoneMixingFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumZoneTemperatureScheduleName, "MinimumZoneTemperatureScheduleName", "Minimum Zone Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumZoneTemperatureScheduleName, "MaximumZoneTemperatureScheduleName", "Maximum Zone Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumSourceZoneTemperatureScheduleName, "MinimumSourceZoneTemperatureScheduleName", "Minimum Source Zone Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumSourceZoneTemperatureScheduleName, "MaximumSourceZoneTemperatureScheduleName", "Maximum Source Zone Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneMixingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneMixingFields> OptionalOS_ZoneMixingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX
