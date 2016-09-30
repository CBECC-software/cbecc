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

#ifndef UTILITIES_IDD_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_GasCooler_AirCooledFields
 *  \brief Enumeration of Refrigeration:GasCooler:AirCooled's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_GasCooler_AirCooledFields, )
#else
class Refrigeration_GasCooler_AirCooledFields: public ::EnumBase<Refrigeration_GasCooler_AirCooledFields> {
 public: 
  enum domain 
  {
Name, RatedTotalHeatRejectionRateCurveName, GasCoolerFanSpeedControlType, RatedFanPower, MinimumFanAirFlowRatio, TransitionTemperature, TranscriticalApproachTemperature, SubcriticalTemperatureDifference, MinimumCondensingTemperature, AirInletNodeName, EndUseSubcategory, GasCoolerRefrigerantOperatingChargeInventory, GasCoolerReceiverRefrigerantInventory, GasCoolerOutletPipingRefrigerantInventory,   };
  Refrigeration_GasCooler_AirCooledFields()
   : EnumBase<Refrigeration_GasCooler_AirCooledFields>(Name) {} 
  Refrigeration_GasCooler_AirCooledFields(const std::string &t_name) 
   : EnumBase<Refrigeration_GasCooler_AirCooledFields>(t_name) {} 
  Refrigeration_GasCooler_AirCooledFields(int t_value) 
   : EnumBase<Refrigeration_GasCooler_AirCooledFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_GasCooler_AirCooledFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_GasCooler_AirCooledFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_GasCooler_AirCooledFields>;
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
{ Refrigeration_GasCooler_AirCooledFields::Name, "Name", "Name"},
{ Refrigeration_GasCooler_AirCooledFields::RatedTotalHeatRejectionRateCurveName, "RatedTotalHeatRejectionRateCurveName", "Rated Total Heat Rejection Rate Curve Name"},
{ Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType, "GasCoolerFanSpeedControlType", "Gas Cooler Fan Speed Control Type"},
{ Refrigeration_GasCooler_AirCooledFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ Refrigeration_GasCooler_AirCooledFields::TransitionTemperature, "TransitionTemperature", "Transition Temperature"},
{ Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature, "TranscriticalApproachTemperature", "Transcritical Approach Temperature"},
{ Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference, "SubcriticalTemperatureDifference", "Subcritical Temperature Difference"},
{ Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature, "MinimumCondensingTemperature", "Minimum Condensing Temperature"},
{ Refrigeration_GasCooler_AirCooledFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory, "GasCoolerRefrigerantOperatingChargeInventory", "Gas Cooler Refrigerant Operating Charge Inventory"},
{ Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory, "GasCoolerReceiverRefrigerantInventory", "Gas Cooler Receiver Refrigerant Inventory"},
{ Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory, "GasCoolerOutletPipingRefrigerantInventory", "Gas Cooler Outlet Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_GasCooler_AirCooledFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_GasCooler_AirCooledFields> OptionalRefrigeration_GasCooler_AirCooledFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_GASCOOLER_AIRCOOLED_FIELDENUMS_HXX
