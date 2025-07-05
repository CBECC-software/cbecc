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

#ifndef UTILITIES_IDD_COIL_HEATING_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_GasFields
 *  \brief Enumeration of Coil:Heating:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_GasFields, )
#else
class Coil_Heating_GasFields: public ::EnumBase<Coil_Heating_GasFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, GasBurnerEfficiency, NominalCapacity, AirInletNodeName, AirOutletNodeName, TemperatureSetpointNodeName, ParasiticElectricLoad, PartLoadFractionCorrelationCurveName, ParasiticGasLoad,   };
  Coil_Heating_GasFields()
   : EnumBase<Coil_Heating_GasFields>(Name) {} 
  Coil_Heating_GasFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_GasFields>(t_name) {} 
  Coil_Heating_GasFields(int t_value) 
   : EnumBase<Coil_Heating_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_GasFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_GasFields>;
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
{ Coil_Heating_GasFields::Name, "Name", "Name"},
{ Coil_Heating_GasFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_GasFields::GasBurnerEfficiency, "GasBurnerEfficiency", "Gas Burner Efficiency"},
{ Coil_Heating_GasFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Coil_Heating_GasFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_GasFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_GasFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
{ Coil_Heating_GasFields::ParasiticElectricLoad, "ParasiticElectricLoad", "Parasitic Electric Load"},
{ Coil_Heating_GasFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Heating_GasFields::ParasiticGasLoad, "ParasiticGasLoad", "Parasitic Gas Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_GasFields> OptionalCoil_Heating_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_GAS_FIELDENUMS_HXX
