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

#ifndef UTILITIES_IDD_BOILER_STEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_BOILER_STEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Boiler_SteamFields
 *  \brief Enumeration of Boiler:Steam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Boiler_SteamFields, )
#else
class Boiler_SteamFields: public ::EnumBase<Boiler_SteamFields> {
 public: 
  enum domain 
  {
Name, FuelType, MaximumOperatingPressure, TheoreticalEfficiency, DesignOutletSteamTemperature, NominalCapacity, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, Coefficient1ofFuelUseFunctionofPartLoadRatioCurve, Coefficient2ofFuelUseFunctionofPartLoadRatioCurve, Coefficient3ofFuelUseFunctionofPartLoadRatioCurve, WaterInletNodeName, SteamOutletNodeName, SizingFactor,   };
  Boiler_SteamFields()
   : EnumBase<Boiler_SteamFields>(Name) {} 
  Boiler_SteamFields(const std::string &t_name) 
   : EnumBase<Boiler_SteamFields>(t_name) {} 
  Boiler_SteamFields(int t_value) 
   : EnumBase<Boiler_SteamFields>(t_value) {} 
  static std::string enumName() 
  { return "Boiler_SteamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Boiler_SteamFields>::value()); }
   private:
    friend class EnumBase<Boiler_SteamFields>;
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
{ Boiler_SteamFields::Name, "Name", "Name"},
{ Boiler_SteamFields::FuelType, "FuelType", "Fuel Type"},
{ Boiler_SteamFields::MaximumOperatingPressure, "MaximumOperatingPressure", "Maximum Operating Pressure"},
{ Boiler_SteamFields::TheoreticalEfficiency, "TheoreticalEfficiency", "Theoretical Efficiency"},
{ Boiler_SteamFields::DesignOutletSteamTemperature, "DesignOutletSteamTemperature", "Design Outlet Steam Temperature"},
{ Boiler_SteamFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Boiler_SteamFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Boiler_SteamFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Boiler_SteamFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Boiler_SteamFields::Coefficient1ofFuelUseFunctionofPartLoadRatioCurve, "Coefficient1ofFuelUseFunctionofPartLoadRatioCurve", "Coefficient 1 of Fuel Use Function of Part Load Ratio Curve"},
{ Boiler_SteamFields::Coefficient2ofFuelUseFunctionofPartLoadRatioCurve, "Coefficient2ofFuelUseFunctionofPartLoadRatioCurve", "Coefficient 2 of Fuel Use Function of Part Load Ratio Curve"},
{ Boiler_SteamFields::Coefficient3ofFuelUseFunctionofPartLoadRatioCurve, "Coefficient3ofFuelUseFunctionofPartLoadRatioCurve", "Coefficient 3 of Fuel Use Function of Part Load Ratio Curve"},
{ Boiler_SteamFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Boiler_SteamFields::SteamOutletNodeName, "SteamOutletNodeName", "Steam Outlet Node Name"},
{ Boiler_SteamFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const Boiler_SteamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Boiler_SteamFields> OptionalBoiler_SteamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_BOILER_STEAM_FIELDENUMS_HXX
