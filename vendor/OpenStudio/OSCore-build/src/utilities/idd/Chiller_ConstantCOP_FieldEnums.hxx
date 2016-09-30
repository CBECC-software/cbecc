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

#ifndef UTILITIES_IDD_CHILLER_CONSTANTCOP_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_CONSTANTCOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_ConstantCOPFields
 *  \brief Enumeration of Chiller:ConstantCOP's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_ConstantCOPFields, )
#else
class Chiller_ConstantCOPFields: public ::EnumBase<Chiller_ConstantCOPFields> {
 public: 
  enum domain 
  {
Name, NominalCapacity, NominalCOP, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, CondenserType, ChillerFlowMode, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  Chiller_ConstantCOPFields()
   : EnumBase<Chiller_ConstantCOPFields>(Name) {} 
  Chiller_ConstantCOPFields(const std::string &t_name) 
   : EnumBase<Chiller_ConstantCOPFields>(t_name) {} 
  Chiller_ConstantCOPFields(int t_value) 
   : EnumBase<Chiller_ConstantCOPFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_ConstantCOPFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_ConstantCOPFields>::value()); }
   private:
    friend class EnumBase<Chiller_ConstantCOPFields>;
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
{ Chiller_ConstantCOPFields::Name, "Name", "Name"},
{ Chiller_ConstantCOPFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_ConstantCOPFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_ConstantCOPFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_ConstantCOPFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_ConstantCOPFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_ConstantCOPFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_ConstantCOPFields::CondenserType, "CondenserType", "Condenser Type"},
{ Chiller_ConstantCOPFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_ConstantCOPFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_ConstantCOPFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Chiller_ConstantCOPFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Chiller_ConstantCOPFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_ConstantCOPFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_ConstantCOPFields> OptionalChiller_ConstantCOPFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_CONSTANTCOP_FIELDENUMS_HXX
