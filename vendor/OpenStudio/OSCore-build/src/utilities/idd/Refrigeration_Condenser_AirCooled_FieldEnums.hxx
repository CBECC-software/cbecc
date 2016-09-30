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

#ifndef UTILITIES_IDD_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_Condenser_AirCooledFields
 *  \brief Enumeration of Refrigeration:Condenser:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_Condenser_AirCooledFields, )
#else
class Refrigeration_Condenser_AirCooledFields: public ::EnumBase<Refrigeration_Condenser_AirCooledFields> {
 public: 
  enum domain 
  {
Name, RatedEffectiveTotalHeatRejectionRateCurveName, RatedSubcoolingTemperatureDifference, CondenserFanSpeedControlType, RatedFanPower, MinimumFanAirFlowRatio, AirInletNodeNameorZoneName, EndUseSubcategory, CondenserRefrigerantOperatingChargeInventory, CondensateReceiverRefrigerantInventory, CondensatePipingRefrigerantInventory,   };
  Refrigeration_Condenser_AirCooledFields()
   : EnumBase<Refrigeration_Condenser_AirCooledFields>(Name) {} 
  Refrigeration_Condenser_AirCooledFields(const std::string &t_name) 
   : EnumBase<Refrigeration_Condenser_AirCooledFields>(t_name) {} 
  Refrigeration_Condenser_AirCooledFields(int t_value) 
   : EnumBase<Refrigeration_Condenser_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_Condenser_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_Condenser_AirCooledFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_Condenser_AirCooledFields>;
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
{ Refrigeration_Condenser_AirCooledFields::Name, "Name", "Name"},
{ Refrigeration_Condenser_AirCooledFields::RatedEffectiveTotalHeatRejectionRateCurveName, "RatedEffectiveTotalHeatRejectionRateCurveName", "Rated Effective Total Heat Rejection Rate Curve Name"},
{ Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference, "RatedSubcoolingTemperatureDifference", "Rated Subcooling Temperature Difference"},
{ Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType, "CondenserFanSpeedControlType", "Condenser Fan Speed Control Type"},
{ Refrigeration_Condenser_AirCooledFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ Refrigeration_Condenser_AirCooledFields::AirInletNodeNameorZoneName, "AirInletNodeNameorZoneName", "Air Inlet Node Name or Zone Name"},
{ Refrigeration_Condenser_AirCooledFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory, "CondenserRefrigerantOperatingChargeInventory", "Condenser Refrigerant Operating Charge Inventory"},
{ Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory, "CondensateReceiverRefrigerantInventory", "Condensate Receiver Refrigerant Inventory"},
{ Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory, "CondensatePipingRefrigerantInventory", "Condensate Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_Condenser_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_Condenser_AirCooledFields> OptionalRefrigeration_Condenser_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_CONDENSER_AIRCOOLED_FIELDENUMS_HXX
