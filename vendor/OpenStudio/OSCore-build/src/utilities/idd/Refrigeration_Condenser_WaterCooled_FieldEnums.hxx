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

#ifndef UTILITIES_IDD_REFRIGERATION_CONDENSER_WATERCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_CONDENSER_WATERCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_Condenser_WaterCooledFields
 *  \brief Enumeration of Refrigeration:Condenser:WaterCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_Condenser_WaterCooledFields, )
#else
class Refrigeration_Condenser_WaterCooledFields: public ::EnumBase<Refrigeration_Condenser_WaterCooledFields> {
 public: 
  enum domain 
  {
Name, RatedEffectiveTotalHeatRejectionRate, RatedCondensingTemperature, RatedSubcoolingTemperatureDifference, RatedWaterInletTemperature, WaterInletNodeName, WaterOutletNodeName, WaterCooledLoopFlowType, WaterOutletTemperatureScheduleName, WaterDesignFlowRate, WaterMaximumFlowRate, WaterMaximumWaterOutletTemperature, WaterMinimumWaterInletTemperature, EndUseSubcategory, CondenserRefrigerantOperatingChargeInventory, CondensateReceiverRefrigerantInventory, CondensatePipingRefrigerantInventory,   };
  Refrigeration_Condenser_WaterCooledFields()
   : EnumBase<Refrigeration_Condenser_WaterCooledFields>(Name) {} 
  Refrigeration_Condenser_WaterCooledFields(const std::string &t_name) 
   : EnumBase<Refrigeration_Condenser_WaterCooledFields>(t_name) {} 
  Refrigeration_Condenser_WaterCooledFields(int t_value) 
   : EnumBase<Refrigeration_Condenser_WaterCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_Condenser_WaterCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_Condenser_WaterCooledFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_Condenser_WaterCooledFields>;
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
{ Refrigeration_Condenser_WaterCooledFields::Name, "Name", "Name"},
{ Refrigeration_Condenser_WaterCooledFields::RatedEffectiveTotalHeatRejectionRate, "RatedEffectiveTotalHeatRejectionRate", "Rated Effective Total Heat Rejection Rate"},
{ Refrigeration_Condenser_WaterCooledFields::RatedCondensingTemperature, "RatedCondensingTemperature", "Rated Condensing Temperature"},
{ Refrigeration_Condenser_WaterCooledFields::RatedSubcoolingTemperatureDifference, "RatedSubcoolingTemperatureDifference", "Rated Subcooling Temperature Difference"},
{ Refrigeration_Condenser_WaterCooledFields::RatedWaterInletTemperature, "RatedWaterInletTemperature", "Rated Water Inlet Temperature"},
{ Refrigeration_Condenser_WaterCooledFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Refrigeration_Condenser_WaterCooledFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType, "WaterCooledLoopFlowType", "Water-Cooled Loop Flow Type"},
{ Refrigeration_Condenser_WaterCooledFields::WaterOutletTemperatureScheduleName, "WaterOutletTemperatureScheduleName", "Water Outlet Temperature Schedule Name"},
{ Refrigeration_Condenser_WaterCooledFields::WaterDesignFlowRate, "WaterDesignFlowRate", "Water Design Flow Rate"},
{ Refrigeration_Condenser_WaterCooledFields::WaterMaximumFlowRate, "WaterMaximumFlowRate", "Water Maximum Flow Rate"},
{ Refrigeration_Condenser_WaterCooledFields::WaterMaximumWaterOutletTemperature, "WaterMaximumWaterOutletTemperature", "Water Maximum Water Outlet Temperature"},
{ Refrigeration_Condenser_WaterCooledFields::WaterMinimumWaterInletTemperature, "WaterMinimumWaterInletTemperature", "Water Minimum Water Inlet Temperature"},
{ Refrigeration_Condenser_WaterCooledFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_Condenser_WaterCooledFields::CondenserRefrigerantOperatingChargeInventory, "CondenserRefrigerantOperatingChargeInventory", "Condenser Refrigerant Operating Charge Inventory"},
{ Refrigeration_Condenser_WaterCooledFields::CondensateReceiverRefrigerantInventory, "CondensateReceiverRefrigerantInventory", "Condensate Receiver Refrigerant Inventory"},
{ Refrigeration_Condenser_WaterCooledFields::CondensatePipingRefrigerantInventory, "CondensatePipingRefrigerantInventory", "Condensate Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_Condenser_WaterCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_Condenser_WaterCooledFields> OptionalRefrigeration_Condenser_WaterCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_CONDENSER_WATERCOOLED_FIELDENUMS_HXX
