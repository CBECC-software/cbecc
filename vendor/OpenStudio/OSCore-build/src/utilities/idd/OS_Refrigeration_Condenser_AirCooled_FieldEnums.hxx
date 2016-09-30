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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_Condenser_AirCooledFields
 *  \brief Enumeration of OS:Refrigeration:Condenser:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_Condenser_AirCooledFields, )
#else
class OS_Refrigeration_Condenser_AirCooledFields: public ::EnumBase<OS_Refrigeration_Condenser_AirCooledFields> {
 public: 
  enum domain 
  {
Handle, Name, RatedEffectiveTotalHeatRejectionRateCurveName, RatedSubcoolingTemperatureDifference, CondenserFanSpeedControlType, RatedFanPower, MinimumFanAirFlowRatio, AirInletZoneName, EndUseSubcategory, CondenserRefrigerantOperatingChargeInventory, CondensateReceiverRefrigerantInventory, CondensatePipingRefrigerantInventory,   };
  OS_Refrigeration_Condenser_AirCooledFields()
   : EnumBase<OS_Refrigeration_Condenser_AirCooledFields>(Handle) {} 
  OS_Refrigeration_Condenser_AirCooledFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_Condenser_AirCooledFields>(t_name) {} 
  OS_Refrigeration_Condenser_AirCooledFields(int t_value) 
   : EnumBase<OS_Refrigeration_Condenser_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_Condenser_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_Condenser_AirCooledFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_Condenser_AirCooledFields>;
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
{ OS_Refrigeration_Condenser_AirCooledFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_Condenser_AirCooledFields::Name, "Name", "Name"},
{ OS_Refrigeration_Condenser_AirCooledFields::RatedEffectiveTotalHeatRejectionRateCurveName, "RatedEffectiveTotalHeatRejectionRateCurveName", "Rated Effective Total Heat Rejection Rate Curve Name"},
{ OS_Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference, "RatedSubcoolingTemperatureDifference", "Rated Subcooling Temperature Difference"},
{ OS_Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType, "CondenserFanSpeedControlType", "Condenser Fan Speed Control Type"},
{ OS_Refrigeration_Condenser_AirCooledFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ OS_Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ OS_Refrigeration_Condenser_AirCooledFields::AirInletZoneName, "AirInletZoneName", "Air Inlet Zone Name"},
{ OS_Refrigeration_Condenser_AirCooledFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory, "CondenserRefrigerantOperatingChargeInventory", "Condenser Refrigerant Operating Charge Inventory"},
{ OS_Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory, "CondensateReceiverRefrigerantInventory", "Condensate Receiver Refrigerant Inventory"},
{ OS_Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory, "CondensatePipingRefrigerantInventory", "Condensate Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_Condenser_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_Condenser_AirCooledFields> OptionalOS_Refrigeration_Condenser_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX
