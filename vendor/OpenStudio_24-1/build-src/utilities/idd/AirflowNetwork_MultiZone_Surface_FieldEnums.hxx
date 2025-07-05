/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_SurfaceFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:Surface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_SurfaceFields, )
#else
class AirflowNetwork_MultiZone_SurfaceFields: public ::EnumBase<AirflowNetwork_MultiZone_SurfaceFields> {
 public: 
  enum domain 
  {
SurfaceName, LeakageComponentName, ExternalNodeName, Window_DoorOpeningFactororCrackFactor, VentilationControlMode, VentilationControlZoneTemperatureSetpointScheduleName, MinimumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, VentingAvailabilityScheduleName, OccupantVentilationControlName, EquivalentRectangleMethod, EquivalentRectangleAspectRatio,   };
  AirflowNetwork_MultiZone_SurfaceFields()
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(SurfaceName) {} 
  AirflowNetwork_MultiZone_SurfaceFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(t_name) {} 
  AirflowNetwork_MultiZone_SurfaceFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_SurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_SurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_SurfaceFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_SurfaceFields>;
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
{ AirflowNetwork_MultiZone_SurfaceFields::SurfaceName, "SurfaceName", "Surface Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::LeakageComponentName, "LeakageComponentName", "Leakage Component Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::ExternalNodeName, "ExternalNodeName", "External Node Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor, "Window_DoorOpeningFactororCrackFactor", "Window/Door Opening Factor or Crack Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode, "VentilationControlMode", "Ventilation Control Mode"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentilationControlZoneTemperatureSetpointScheduleName, "VentilationControlZoneTemperatureSetpointScheduleName", "Ventilation Control Zone Temperature Setpoint Schedule Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor, "MinimumVentingOpenFactor", "Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Lower Limit For Maximum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Temperature Difference Upper Limit for Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Lower Limit For Maximum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, "IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor", "Indoor and Outdoor Enthalpy Difference Upper Limit for Minimum Venting Open Factor"},
{ AirflowNetwork_MultiZone_SurfaceFields::VentingAvailabilityScheduleName, "VentingAvailabilityScheduleName", "Venting Availability Schedule Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::OccupantVentilationControlName, "OccupantVentilationControlName", "Occupant Ventilation Control Name"},
{ AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleMethod, "EquivalentRectangleMethod", "Equivalent Rectangle Method"},
{ AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleAspectRatio, "EquivalentRectangleAspectRatio", "Equivalent Rectangle Aspect Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_SurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_SurfaceFields> OptionalAirflowNetwork_MultiZone_SurfaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SURFACE_FIELDENUMS_HXX
