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

#ifndef UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_FINITEDIFFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_FINITEDIFFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundTemperature_Undisturbed_FiniteDifferenceFields
 *  \brief Enumeration of Site:GroundTemperature:Undisturbed:FiniteDifference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundTemperature_Undisturbed_FiniteDifferenceFields, )
#else
class Site_GroundTemperature_Undisturbed_FiniteDifferenceFields: public ::EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields> {
 public: 
  enum domain 
  {
Name, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, SoilMoistureContentVolumeFraction, SoilMoistureContentVolumeFractionatSaturation, EvapotranspirationGroundCoverParameter,   };
  Site_GroundTemperature_Undisturbed_FiniteDifferenceFields()
   : EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields>(Name) {} 
  Site_GroundTemperature_Undisturbed_FiniteDifferenceFields(const std::string &t_name) 
   : EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields>(t_name) {} 
  Site_GroundTemperature_Undisturbed_FiniteDifferenceFields(int t_value) 
   : EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundTemperature_Undisturbed_FiniteDifferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields>::value()); }
   private:
    friend class EnumBase<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields>;
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
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::Name, "Name", "Name"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilDensity, "SoilDensity", "Soil Density"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFraction, "SoilMoistureContentVolumeFraction", "Soil Moisture Content Volume Fraction"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::SoilMoistureContentVolumeFractionatSaturation, "SoilMoistureContentVolumeFractionatSaturation", "Soil Moisture Content Volume Fraction at Saturation"},
{ Site_GroundTemperature_Undisturbed_FiniteDifferenceFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundTemperature_Undisturbed_FiniteDifferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundTemperature_Undisturbed_FiniteDifferenceFields> OptionalSite_GroundTemperature_Undisturbed_FiniteDifferenceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_FINITEDIFFERENCE_FIELDENUMS_HXX
