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

#ifndef UTILITIES_IDD_REFRIGERATION_CONDENSER_CASCADE_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_CONDENSER_CASCADE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_Condenser_CascadeFields
 *  \brief Enumeration of Refrigeration:Condenser:Cascade's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_Condenser_CascadeFields, )
#else
class Refrigeration_Condenser_CascadeFields: public ::EnumBase<Refrigeration_Condenser_CascadeFields> {
 public: 
  enum domain 
  {
Name, RatedCondensingTemperature, RatedApproachTemperatureDifference, RatedEffectiveTotalHeatRejectionRate, CondensingTemperatureControlType, CondenserRefrigerantOperatingChargeInventory, CondensateReceiverRefrigerantInventory, CondensatePipingRefrigerantInventory,   };
  Refrigeration_Condenser_CascadeFields()
   : EnumBase<Refrigeration_Condenser_CascadeFields>(Name) {} 
  Refrigeration_Condenser_CascadeFields(const std::string &t_name) 
   : EnumBase<Refrigeration_Condenser_CascadeFields>(t_name) {} 
  Refrigeration_Condenser_CascadeFields(int t_value) 
   : EnumBase<Refrigeration_Condenser_CascadeFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_Condenser_CascadeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_Condenser_CascadeFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_Condenser_CascadeFields>;
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
{ Refrigeration_Condenser_CascadeFields::Name, "Name", "Name"},
{ Refrigeration_Condenser_CascadeFields::RatedCondensingTemperature, "RatedCondensingTemperature", "Rated Condensing Temperature"},
{ Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference, "RatedApproachTemperatureDifference", "Rated Approach Temperature Difference"},
{ Refrigeration_Condenser_CascadeFields::RatedEffectiveTotalHeatRejectionRate, "RatedEffectiveTotalHeatRejectionRate", "Rated Effective Total Heat Rejection Rate"},
{ Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType, "CondensingTemperatureControlType", "Condensing Temperature Control Type"},
{ Refrigeration_Condenser_CascadeFields::CondenserRefrigerantOperatingChargeInventory, "CondenserRefrigerantOperatingChargeInventory", "Condenser Refrigerant Operating Charge Inventory"},
{ Refrigeration_Condenser_CascadeFields::CondensateReceiverRefrigerantInventory, "CondensateReceiverRefrigerantInventory", "Condensate Receiver Refrigerant Inventory"},
{ Refrigeration_Condenser_CascadeFields::CondensatePipingRefrigerantInventory, "CondensatePipingRefrigerantInventory", "Condensate Piping Refrigerant Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_Condenser_CascadeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_Condenser_CascadeFields> OptionalRefrigeration_Condenser_CascadeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_CONDENSER_CASCADE_FIELDENUMS_HXX
