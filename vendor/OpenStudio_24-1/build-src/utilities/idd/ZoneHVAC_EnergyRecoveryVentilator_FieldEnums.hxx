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

#ifndef UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_EnergyRecoveryVentilatorFields
 *  \brief Enumeration of ZoneHVAC:EnergyRecoveryVentilator's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_EnergyRecoveryVentilatorFields, )
#else
class ZoneHVAC_EnergyRecoveryVentilatorFields: public ::EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, HeatExchangerName, SupplyAirFlowRate, ExhaustAirFlowRate, SupplyAirFanName, ExhaustAirFanName, ControllerName, VentilationRateperUnitFloorArea, VentilationRateperOccupant, AvailabilityManagerListName,   };
  ZoneHVAC_EnergyRecoveryVentilatorFields()
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(Name) {} 
  ZoneHVAC_EnergyRecoveryVentilatorFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(t_name) {} 
  ZoneHVAC_EnergyRecoveryVentilatorFields(int t_value) 
   : EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_EnergyRecoveryVentilatorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_EnergyRecoveryVentilatorFields>;
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
{ ZoneHVAC_EnergyRecoveryVentilatorFields::Name, "Name", "Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName, "HeatExchangerName", "Heat Exchanger Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, "SupplyAirFlowRate", "Supply Air Flow Rate"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, "ExhaustAirFlowRate", "Exhaust Air Flow Rate"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName, "ExhaustAirFanName", "Exhaust Air Fan Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName, "ControllerName", "Controller Name"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, "VentilationRateperUnitFloorArea", "Ventilation Rate per Unit Floor Area"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, "VentilationRateperOccupant", "Ventilation Rate per Occupant"},
{ ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_EnergyRecoveryVentilatorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_EnergyRecoveryVentilatorFields> OptionalZoneHVAC_EnergyRecoveryVentilatorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_ENERGYRECOVERYVENTILATOR_FIELDENUMS_HXX
