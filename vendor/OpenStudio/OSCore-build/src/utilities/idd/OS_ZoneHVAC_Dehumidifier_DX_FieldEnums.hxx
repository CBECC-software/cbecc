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

#ifndef UTILITIES_IDD_OS_ZONEHVAC_DEHUMIDIFIER_DX_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_DEHUMIDIFIER_DX_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_Dehumidifier_DXFields
 *  \brief Enumeration of OS:ZoneHVAC:Dehumidifier:DX's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_Dehumidifier_DXFields, )
#else
class OS_ZoneHVAC_Dehumidifier_DXFields: public ::EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, RatedWaterRemoval, RatedEnergyFactor, RatedAirFlowRate, WaterRemovalCurveName, EnergyFactorCurveName, PartLoadFractionCorrelationCurveName, MinimumDryBulbTemperatureforDehumidifierOperation, MaximumDryBulbTemperatureforDehumidifierOperation, OffCycleParasiticElectricLoad, CondensateCollectionWaterStorageTankName,   };
  OS_ZoneHVAC_Dehumidifier_DXFields()
   : EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields>(Handle) {} 
  OS_ZoneHVAC_Dehumidifier_DXFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields>(t_name) {} 
  OS_ZoneHVAC_Dehumidifier_DXFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_Dehumidifier_DXFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_Dehumidifier_DXFields>;
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
{ OS_ZoneHVAC_Dehumidifier_DXFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::RatedWaterRemoval, "RatedWaterRemoval", "Rated Water Removal"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::RatedEnergyFactor, "RatedEnergyFactor", "Rated Energy Factor"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName, "WaterRemovalCurveName", "Water Removal Curve Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName, "EnergyFactorCurveName", "Energy Factor Curve Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::MinimumDryBulbTemperatureforDehumidifierOperation, "MinimumDryBulbTemperatureforDehumidifierOperation", "Minimum Dry-Bulb Temperature for Dehumidifier Operation"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::MaximumDryBulbTemperatureforDehumidifierOperation, "MaximumDryBulbTemperatureforDehumidifierOperation", "Maximum Dry-Bulb Temperature for Dehumidifier Operation"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off-Cycle Parasitic Electric Load"},
{ OS_ZoneHVAC_Dehumidifier_DXFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_Dehumidifier_DXFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_Dehumidifier_DXFields> OptionalOS_ZoneHVAC_Dehumidifier_DXFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_DEHUMIDIFIER_DX_FIELDENUMS_HXX
